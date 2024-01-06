#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <windows.h>

CRITICAL_SECTION cs;

float *arr;
int arrLength;

int maxI = 0, minI = 0;
float mid = 0;

void getArray()
{
    printf("\nInput the size of the array >>> ");
    scanf("%d", &arrLength);

    arr = (float *) malloc(arrLength * sizeof(float));

    printf("\nInput the array >>> ");

    int i;
    for(i = 0; i < arrLength; i++)
    {
        scanf("%f", &arr[i]);
    }
}

DWORD WINAPI min_max(LPVOID iNum)
{
    float max = FLT_MIN;
    float min = FLT_MAX;
    int mi, Mi;

    int i;
    for(i = 0; i < arrLength; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            Mi = i;
        }
        
        Sleep(7);

        if(arr[i] < min)
        {
            min = arr[i];
            mi = i;
        }

        Sleep(7);
    }

    EnterCriticalSection(&cs);

    minI = mi;
    maxI = Mi;

    printf("\nThe biggest element found is %.1f\n", max);
    printf("\nThe smallest element found is %.1f\n", min);

    LeaveCriticalSection(&cs);

    return 0;
}

DWORD WINAPI average(LPVOID iNum)
{
    float AV = 0;

    int i;
    for(i = 0; i < arrLength; i++)
    {
        AV += arr[i];

        Sleep(12);
    }

    EnterCriticalSection(&cs);

    mid = AV / arrLength;

    printf("\nThe average element found is %.1f\n", mid);

    LeaveCriticalSection(&cs);

    return 0;
}

int main()
{
    InitializeCriticalSection(&cs);


    HANDLE min_max_hThread;
    DWORD min_max_IDThread;

    HANDLE average_hThread;
    DWORD average_IDThread;


    getArray();

    min_max_hThread = CreateThread(NULL, 0, min_max, NULL, 0, &min_max_IDThread);
    average_hThread = CreateThread(NULL, 0, average, NULL, 0, &average_IDThread);

	if (min_max_hThread == NULL || average_hThread == NULL)
	{
		return GetLastError();
	}

	WaitForSingleObject(min_max_hThread, INFINITE);
    WaitForSingleObject(average_hThread, INFINITE);

    arr[maxI] = mid;
    arr[minI] = mid;

    printf("\nNew array: >>> ");

    int i;
    for(i = 0; i < arrLength; i++)
    {
        printf("%.1f ", arr[i]);
    }

    DeleteCriticalSection(&cs);

    CloseHandle(min_max_hThread);
	CloseHandle(average_hThread);

    free(arr);

    return 0;
}