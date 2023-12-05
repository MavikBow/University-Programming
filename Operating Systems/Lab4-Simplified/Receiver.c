#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

STARTUPINFO si;
PROCESS_INFORMATION pi;
int message_amount;
int sender_amount;

int main()
{
    FILE* file;
    char binary_name[100];
    char sender_launcher[200] = "sender.exe ";

    LPCTSTR mutexName = "ConsoleMutex";

    HANDLE hReadyEvent;
    HANDLE hMutex;
    hMutex = CreateMutex(NULL, TRUE, mutexName);
    if (hMutex == NULL)
    {
        printf("Mutex creation failure!\n");
        return (int)GetLastError();
    }

    /* 1 */
    printf("Enter the name the binary file: ");
    scanf("%99s", binary_name);
    printf("Enter the amount of messages in the file: ");
    scanf("%d", &message_amount);

    /* 2 */
    file = fopen(binary_name, "wb");
    fclose(file);

    /* 3
    printf("Enter the amount of Senders: ");
    scanf("%d", &sender_amount);
    */

    /* 4 */
    strcat(sender_launcher, binary_name);

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, sender_launcher, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("The sender process is not running.\n");
        return (int)GetLastError();
    }


    return 0;
}