#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Command.h"
#include "Employee.h"

typedef struct
{
    HANDLE hReadHandle;
    HANDLE hWriteHandle;
    int num;
} PipeInfo;

const int MAXFILENAMELENGTH = 20;
FILE* file;
char filename[20];
CRITICAL_SECTION cs;
HANDLE* hWriteAccess, *hReadAccess;
HANDLE*hThread;
DWORD*ThreadID;
PipeInfo* pipes;
int* countOfReaders;

void init()
{
    unsigned N, i;
    employee st;

    printf("Enter filename: ");
    scanf("%19s", filename);
    file = fopen(filename, "w+b");
    printf("Enter record count: ");
    scanf("%u", &N);

    hWriteAccess = (HANDLE*)malloc(N * sizeof(HANDLE));
    hReadAccess = (HANDLE*)malloc(N * sizeof(HANDLE));
    countOfReaders = (int*)calloc(N, sizeof(int));

    fwrite(&N, sizeof(int), 1, file);

    for(i = 0; i < N; i++)
    {
        hWriteAccess[i] = CreateEvent(0, TRUE, TRUE, NULL);
        hReadAccess[i] = CreateEvent(0, TRUE, TRUE, NULL);

        printf("\t\nRecord number %u:\n", i + 1);
        printf("Enter employee's number: ");
        scanf("%d", &st.num);
        printf("Enter employee's name: ");
        scanf("%9s", st.name);
        printf("Enter employee's working hours: ");
        scanf("%lf", &st.hours);

        fwrite(&st, sizeof(employee), 1, file);
    }
}

void print()
{
    unsigned N, i;
    employee st;
    rewind(file);

    fread(&N, sizeof(int), 1, file);
    for(i = 0; i < N; i++)
    {
        fread(&st, sizeof(employee), 1, file);

        printf("\t\nRecord number %u:\nNumber: %d\nName: %s\nHours: %lf\n", i + 1, st.num, st.name, st.hours);
    }
}

void final()
{
    free(hThread);
    free(ThreadID);
    free(hWriteAccess);
    free(hReadAccess);
    free(countOfReaders);
    fclose(file);
}

char lookUp(int num, employee* st, DWORD* pos)
{
    unsigned long N;
    EnterCriticalSection(&cs);
    rewind(file);

    fread(&N, sizeof(int), 1, file);

    for(*pos = 0; *pos < N; (*pos)++)
    {
        fread(&(*st), sizeof(employee), 1, file);
        if(st->num == num) break;
    }
    
    LeaveCriticalSection(&cs);

    if(*pos == N) return 0;
    return 1;
}

void read(employee*st, DWORD pos)
{
    EnterCriticalSection(&cs);
    fseek(file, (long)(sizeof(int) + pos * sizeof(employee)), SEEK_SET);
    fread(&(*st), sizeof(employee), 1, file);
    LeaveCriticalSection(&cs);
}

void write(employee st, DWORD pos)
{
    EnterCriticalSection(&cs);
    fseek(file, (long)(sizeof(int) + pos * sizeof(employee)), SEEK_SET);
    fwrite(&st, sizeof(employee), 1, file);
    LeaveCriticalSection(&cs);
}

DWORD WINAPI serverThread(LPVOID pr_)
{
    PipeInfo pr = *(PipeInfo*)pr_;
    command c;
    DWORD bytes, pos;
    employee st;

    ConnectNamedPipe(pr.hReadHandle, (LPOVERLAPPED)NULL);
    ConnectNamedPipe(pr.hWriteHandle, (LPOVERLAPPED)NULL);

    do
    {
        ReadFile(pr.hReadHandle, &c, sizeof(command), &bytes, 0);
        if(c.type == 0)
        {
            c.result = lookUp(c.num, &st, &pos);
            WriteFile(pr.hWriteHandle, &c, sizeof(command), &bytes, 0);
            if(c.result)
            {
                countOfReaders[pos]++;
                WaitForSingleObject(hWriteAccess[pos], INFINITE);
                ResetEvent(hReadAccess[pos]);
                read(&st, pos);
                WriteFile(pr.hWriteHandle, &st, sizeof(employee), &bytes, 0);
                countOfReaders[pos]--;
                if(!countOfReaders[pos]) SetEvent(hReadAccess[pos]);
            }
        }
        else if(c.type == 1)
        {
            c.result = lookUp(c.num, &st, &pos);
            WriteFile(pr.hWriteHandle, &c, sizeof(command), &bytes, 0);
            if(c.result)
            {
                WaitForSingleObject(hReadAccess[pos], INFINITE);
                WaitForSingleObject(hWriteAccess[pos], INFINITE);
                ResetEvent(hWriteAccess[pos]);
                read(&st, pos);
                WriteFile(pr.hWriteHandle, &st, sizeof(employee), &bytes, 0);
                ReadFile(pr.hReadHandle, &st, sizeof(employee), &bytes, 0);
                write(st, pos);
                SetEvent(hWriteAccess[pos]);
            }
        }
    } while (c.type != 3);
    
    DisconnectNamedPipe(pr.hReadHandle);
    DisconnectNamedPipe(pr.hWriteHandle);

    return 0;   
}

int main()
{
    unsigned C, i;
    char pipeName[40];

    init();
    print();

    printf("Enter the amount of clients: ");
    scanf("%u", &C);
    InitializeCriticalSection(&cs);

    hThread = (HANDLE*)malloc(C * sizeof(HANDLE));
    ThreadID = (DWORD*)malloc(C * sizeof(DWORD));
    pipes = (PipeInfo*)malloc(C * sizeof(PipeInfo));

    for(i = 0; i < C; i++)
    {
		sprintf(pipeName, "\\\\.\\pipe\\Pipe_%d_%d", 1, i);
        printf("%s\n", pipeName);
        pipes[i].hReadHandle = CreateNamedPipe(pipeName, PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_WAIT, 2, 0, 0, INFINITE, NULL);

		sprintf(pipeName, "\\\\.\\pipe\\Pipe_%d_%d", 2, i);
        printf("%s\n", pipeName);
        pipes[i].hWriteHandle = CreateNamedPipe(pipeName, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE | PIPE_WAIT, 2, 0, 0, INFINITE, NULL);

        hThread = CreateThread(NULL, 0, serverThread, &pipes[i], 0, &ThreadID[i]);
        printf("Client ID: %u\n", i);
    }

    WaitForMultipleObjects(C, hThread, TRUE, INFINITE);

    printf("Final result:\n");
    print();

    final();

    return 0;
}