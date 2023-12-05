#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char* argv[])
{
    HANDLE hMutex;
    char filename[100];

    strcpy(filename, argv[1]);

    hMutex = OpenMutex(SYNCHRONIZE, FALSE, "ConsoleMutex");
    if (hMutex == NULL)
    {
        printf("Mutex opening failed!");

        return (int)GetLastError();

    }
    return 0;
}