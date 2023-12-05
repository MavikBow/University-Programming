#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Message.h"

int main(int argc, char* argv[])
{
    HANDLE consoleMutex;
    consoleMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "ConsoleMutex");
if (consoleMutex == NULL)
    {
        printf("Mutex Fail!");

        return (int)GetLastError();

    }
    int id = atoi(argv[2]);
    return 0;
}