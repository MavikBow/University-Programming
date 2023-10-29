#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

CRITICAL_SECTION cs;

int exitIndex;
HANDLE hExit_Event, hOver_Event;

int *arr;
int arrLength;
int threadNumber;

HANDLE* hThreadArray;
DWORD* dwThreadArray;
HANDLE* hRequest_EventArray;
HANDLE* hPermission_EventArray;

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
    int i = (int)iNum;
    srand(i);

    int markedCounter = 0;
    int r;
    while(1)
    {
        r = rand() % arrLength;

        if(arr[r] == 0)
        {
            Sleep(5);
            arr[r] = i + 1;
            markedCounter++;
            Sleep(5);
        }
        else
        {
            EnterCriticalSection(&cs);

            printf("Thread number: %d\tThe amount of marked elements: %d\tThe element that can't be marked is number: %d;\n", i + 1, markedCounter, r);

            LeaveCriticalSection(&cs); 

    
            SetEvent(hRequest_EventArray[i]);

            // 3.4.3            
            WaitForSingleObject(hExit_Event, INFINITE);

            if(exitIndex == i)
            {
                Sleep(500);
                unmarkArray(i + 1);
                SetEvent(hOver_Event);
                return 0;
            }
            
            WaitForSingleObject(hPermission_EventArray[i], INFINITE);
            Sleep(500);
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
    hPermission_EventArray = (HANDLE *) malloc((threadNumber) * sizeof(HANDLE));

    int i;

    InitializeCriticalSection(&cs);

    for(i = 0; i < threadNumber; i++)
    {
        hRequest_EventArray[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        hPermission_EventArray[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    hExit_Event = CreateEvent(NULL, TRUE, FALSE, NULL);    
    hOver_Event = CreateEvent(NULL, TRUE, FALSE, NULL);    

    for (i = 0; i < threadNumber; i++)
    {
        hThreadArray[i] = CreateThread(NULL, 0, marker, (void*)i, 0, &dwThreadArray[i]);

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
        WaitForMultipleObjects(requestCounter, hRequest_EventArray, TRUE, INFINITE);

        EnterCriticalSection(&cs);

        printf("\nThe array:\n >>> ");
        for(i = 0; i < arrLength; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\nEnter the number of thread whom you'll permit exiting >>> ");
        scanf("%d", &permitIndex);
        
        exitIndex = permitIndex - 1; //because array indexation starts with 0

        // 6.4
        SetEvent(hExit_Event);

        // 6.5
        WaitForSingleObject(hOver_Event, INFINITE);
        requestCounter--;

        // 6.6
        printf("\nThe array after exit:\n >>> ");
        for(i = 0; i < arrLength; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n=====================================================\n");

        LeaveCriticalSection(&cs);

        //Sleep(1000);

        // 6.7
        for(i = 0; i < threadNumber; i++)
        {
            if(i == exitIndex) continue;

            SetEvent(hPermission_EventArray[i]);
            //Sleep(20);
        }
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