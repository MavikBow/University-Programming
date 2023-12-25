#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Command.h"
#include "Employee.h"

int main(int argc, char** argv)
{
    int id;
    char WritePipe[100];
    char ReadPipe[100];
    char connectionCheck = 1;

    char comm;
    DWORD bytes;
    employee st;
    command cm;

    HANDLE hWriteHandle, hReadHandle;

    printf("Enter server ID: ");
    scanf("%d", &id);

	sprintf(WritePipe, "\\\\.\\pipe\\Pipe_%d_%d", 1, id);
    printf("%s\n", WritePipe);
    if(!WaitNamedPipe(WritePipe, NMPWAIT_USE_DEFAULT_WAIT)) connectionCheck = 0;

	sprintf(ReadPipe, "\\\\.\\pipe\\Pipe_%d_%d", 2, id);
    printf("%s\n", ReadPipe);
    if(!WaitNamedPipe(ReadPipe, NMPWAIT_USE_DEFAULT_WAIT)) connectionCheck = 0;

    if(connectionCheck == 0)
    {
        printf("Connection failed\n");
        return 1;
    }

	hWriteHandle = CreateFile(WritePipe, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	hReadHandle = CreateFile(ReadPipe, GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    printf("\nWhat would you like to do? modify/read/quit [m/r/q]: ");
    do
    {
        scanf("%1c", &comm);
        switch(comm)
        {
            case 'q':
                cm.type = 3;
			    WriteFile(hWriteHandle, &cm, sizeof(command), &bytes, 0);
            break;
            case 'r':
                cm.type = 0;
                printf("Enter employee's number: ");
                scanf("%d", &cm.num);
				WriteFile(hWriteHandle, &cm, sizeof(cm), &bytes, 0);
				ReadFile(hReadHandle, &cm, sizeof(cm), &bytes, 0);
				if (cm.result == 1)
                {
                    system("pause");
					ReadFile(hReadHandle, (char*)&st, sizeof(st), &bytes, 0);
                    printf("\nEmployee's number: %d\n Name: %s\nHours: %lf\n", st.num, st.name, st.hours);
                }
                else printf("No such record: %d\n", cm.num);
            break;
            case 'm':
                cm.type = 1;
                printf("Enter employee's number number: ");
                scanf("%d", &cm.num);
				WriteFile(hWriteHandle, &cm, sizeof(cm), &bytes, 0);
				ReadFile(hReadHandle, &cm, sizeof(cm), &bytes, 0);
				if (cm.result == 1)
                {
					ReadFile(hReadHandle, (char*)&st, sizeof(employee), &bytes, 0);
                    printf("\nEmployee's number: %d\n Name: %s\nHours: %lf\n", st.num, st.name, st.hours);
                    printf("Enter new employee's number: ");
                    scanf("%d", &st.num);
                    printf("New Name: ");
                    scanf("%9s", st.name);
                    printf("New Hours: ");
                    scanf("%lf", &st.hours);
                    system("pause");
					WriteFile(hWriteHandle, &st, sizeof(st), &bytes, 0);
                }
                else printf("No such record: %d\n", cm.num);
            break;
            default:
                printf("No such command.\n");
            break;
        }
    } while(comm != 'q');

    return 0;
}