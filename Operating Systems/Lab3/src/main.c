#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

CRITICAL_SECTION cs;

HANDLE* hThreadArray;
DWORD* dwThreadArrayId;

int *arr;
int arrLength;
int threadNumber;
int exitIndex = 0;

HANDLE* hRequestArray;
HANDLE hContinueEvent;
HANDLE hExitEvent;

void printfLine()
{
    EnterCriticalSection(&cs);
    printf("\n================================================\n");
    LeaveCriticalSection(&cs);
}
void unmarkArray(int i)
{
    int j;
    for(j = 0;j < arrLength; j++)
    {
        arr[j] = (arr[j] == i) ? 0 : arr[j];
    }
}
void getArray()
{
    printf("\nInput the size of the array >>> ");
    scanf("%d", &arrLength);

    arr = (int*) calloc(arrLength, sizeof(int));
    
    printf("\n================================================\n");

    printf("Input the number of threads you want to run >>> ");
    scanf("%d", &threadNumber);

    printf("\n");
}
void printfArray()
{
    int i;
    EnterCriticalSection(&cs);
    printf("\nThe array:\n >>> ");
    for(i = 0; i < arrLength; i++)
    {
        printf("%d ", arr[i]);
    }
    LeaveCriticalSection(&cs);
}
void requestExitIndex()
{
    EnterCriticalSection(&cs);
    printf("Enter the number of the thread whom you'll permit exiting >>> ");
    scanf("%d", &exitIndex);
    printf("\n");
    LeaveCriticalSection(&cs);
}

DWORD WINAPI marker(LPVOID iNum)
{
    int index = (int)iNum;
    int publicIndex = index + 1;
    srand(publicIndex);

    WaitForSingleObject(hContinueEvent, INFINITE);

    int markedCounter = 0, r;
    while(1)
    {
        r = rand() % arrLength;

        if(arr[r] == 0)
        {
            arr[r] = publicIndex;
            markedCounter++;
        }
        else
        {
            EnterCriticalSection(&cs);
            printf("Thread number: %d\tThe amount of marked elements: %d\tThe element that can't be marked is number: %d;\n", publicIndex, markedCounter, r);
            SetEvent(hRequestArray[index]);
            //printf(" i set it guys %d\n\n", publicIndex);
            LeaveCriticalSection(&cs); 


            // 3.4.3            
            WaitForSingleObject(hExitEvent, INFINITE);

            if(exitIndex == publicIndex)
            {
                unmarkArray(publicIndex);
                return 0;
            }

            EnterCriticalSection(&cs);
            ResetEvent(hRequestArray[index]);
            LeaveCriticalSection(&cs); 
            
            WaitForSingleObject(hContinueEvent, INFINITE);
            markedCounter = 0;
        }
    }

    return 0;
}

void init()
{
    getArray();

    hThreadArray = (HANDLE *) malloc(threadNumber * sizeof(HANDLE));
    dwThreadArrayId = (DWORD *) malloc(threadNumber * sizeof(DWORD));
    hRequestArray = (HANDLE *) malloc(threadNumber * sizeof(HANDLE));

    InitializeCriticalSection(&cs);

    // Setting up the signals 
    int i;
    for(i = 0; i < threadNumber; i++)
    {
        hRequestArray[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }
    hContinueEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    // Setting up threads
    for(i = 0; i < threadNumber; i++)
    {
        hThreadArray[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)marker, (void*) i, 0, &dwThreadArrayId[i]);

        if(hThreadArray[i] == NULL)
        {
            EnterCriticalSection(&cs);
            printf("Error creating thread number %d \n", i + 1);
            LeaveCriticalSection(&cs);
        }
    }
}
void threadLoop(int exitsLeft)
{
    while(exitsLeft > 0)
    {   
        Sleep(10); 
        SetEvent(hContinueEvent);
        WaitForMultipleObjects(exitsLeft, hRequestArray, TRUE, INFINITE);
        ResetEvent(hContinueEvent);
        
        printfArray();
        printfLine();
        requestExitIndex();

        SetEvent(hExitEvent);
        DWORD waitResult = WaitForSingleObject(hThreadArray[exitIndex-1], INFINITE);
        if(waitResult != WAIT_FAILED)
        {
            CloseHandle(hThreadArray[exitIndex-1]);
            exitsLeft--;
        }
        ResetEvent(hExitEvent);
    }
} 
void fin()
{
    int i;
    for(i = 0; i < threadNumber; i++)
    {
        CloseHandle(hRequestArray[i]);
    }
    CloseHandle(hContinueEvent);
    CloseHandle(hExitEvent);

    DeleteCriticalSection(&cs);
}
void memFree()
{
    free(hThreadArray);
    free(dwThreadArrayId);
    free(hRequestArray);
    free(arr);
}

int main()
{
    init();
    int exitsLeft = threadNumber;
    threadLoop(exitsLeft);
    printfArray();
    fin();
    memFree();
    return 0;
}