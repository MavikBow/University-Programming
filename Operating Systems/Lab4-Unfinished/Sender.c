#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Message.h"

int main(int argc, char* argv[])
{
    HANDLE consoleMutex;
    int id;
    char filename[100];

    strcpy(filename, argv[1]);
    id = atoi(argv[2]);

    consoleMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "ConsoleMutex");
    if (consoleMutex == NULL)
    {
        printf("Mutex Fail!");

        return (int)GetLastError();

    }
    return 0;
}