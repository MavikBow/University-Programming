#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

CRITICAL_SECTION cs;

int *arr;
int arrLength;
int threadNumber;

HANDLE* hThreadArray;
DWORD* dwThreadArray;
HANDLE* hRequest_EventArray;
HANDLE* hPermission_EventArray;
HANDLE* hContinue_Event;

void unmarkArray(int i)
{
    int j = 0;
    for(;j < arrLength; j++)
    {
        arr[j] = (arr[j] == i) ? 0 : arr[j];
    }
}

void getArray()
{
    printf("\nInput the size of the array >>> ");
    scanf("%d", &arrLength);

    arr = (int*) calloc(arrLength, sizeof(int));

    printf("Input the number of threads you want to run >>> ");
    scanf("%d", &threadNumber);
}

DWORD WINAPI marker(LPVOID iNum)
{
    int i = *(int*)iNum;
    srand(i);

    int markedCounter = 0;
    while(1)
    {
        int r = rand() % arrLength;

        if(arr[r] == 0)
        {
            Sleep(5);
            arr[r] = i;
            markedCounter++;
            Sleep(5);
        }
        else
        {
            EnterCriticalSection(&cs);

            printf("Thread number: %d\tThe amount of marked elements: %d\tThe element that can't be marked is number: %d;\n", i, markedCounter, r);

            LeaveCriticalSection(&cs); 

            // TODO 3.4.2

            SetEvent(hRequest_EventArray[i]);

            // TODO 3.4.3
            
            
         WaitForSingleObject(hPermission_EventArray[threadNumber], INFINITE);

         //DWORD answer = WaitForMultipleObjects(2, hPermission_EventArray, FALSE, INFINITE);

            //DWORD answer = WaitForSingleObject(hPermission_EventArray, INFINITE);

            //if(answer == WAIT_OBJECT_0 + i)
            if(1)
            {
                unmarkArray(i);
                return 0;
            }
        }
    }

    return 0;
}

int main()
{
    srand(time(NULL));
    getArray();

    hThreadArray = (HANDLE *) malloc(threadNumber * sizeof(HANDLE));
    dwThreadArray = (DWORD *) malloc(threadNumber * sizeof(DWORD));
    hRequest_EventArray = (HANDLE *) malloc(threadNumber * sizeof(HANDLE));
    hPermission_EventArray = (HANDLE *) malloc((threadNumber + 1) * sizeof(HANDLE));

    int i;

    InitializeCriticalSection(&cs);

    for(i = 0; i < threadNumber; i++)
    {
        hRequest_EventArray[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        hPermission_EventArray[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    hPermission_EventArray[threadNumber] = CreateEvent(NULL, TRUE, FALSE, NULL);

    hContinue_Event = hPermission_EventArray[threadNumber];     

    for (i = 0; i < threadNumber; i++)
    {
        hThreadArray[i] = CreateThread(NULL, 0, marker, (LPVOID)&i, 0, &dwThreadArray[i]);

        if(hThreadArray[i] == NULL)
        {
            EnterCriticalSection(&cs);

            printf("Error creating thread %d \n", i);

            LeaveCriticalSection(&cs);
        }
    }


    // TODO 6

    int requestCounter = threadNumber;
    int permitIndex;

    while(requestCounter > 0)
    {
        WaitForMultipleObjects(threadNumber, hPermission_EventArray, TRUE, INFINITE);

        EnterCriticalSection(&cs);

        printf("\nThe array:\n >>> ");
        for(i = 0; i < arrLength; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\nEnter the number of thread whom you'll permit continuing 1 ... %d >>> ", threadNumber);
        scanf("%d", &permitIndex);

        SetEvent(hPermission_EventArray[permitIndex % threadNumber]);

        WaitForSingleObject(hThreadArray[permitIndex % threadNumber], INFINITE);

        printf("\nThe array:\n >>> ");
        for(i = 0; i < arrLength; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        SetEvent(hContinue_Event);

        LeaveCriticalSection(&cs);

        requestCounter--;
    }



    //
    
    for(i = 0; i < threadNumber; i++)
    {
        CloseHandle(hThreadArray[i]);   
    }
    
    DeleteCriticalSection(&cs);

    for(i = 0; i < threadNumber; i++)
    {
        CloseHandle(hRequest_EventArray[i]);
        CloseHandle(hPermission_EventArray[i]);
    }

    free(arr);
    free(hThreadArray);
    free(dwThreadArray);
    free(hRequest_EventArray);
    free(hPermission_EventArray);

    return 0;
}