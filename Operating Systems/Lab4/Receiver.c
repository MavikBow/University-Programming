#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Message.h"

STARTUPINFO*si;
PROCESS_INFORMATION*pi;
int message_amount;
int sender_amount;

int main()
{
    FILE* file;
    char binary_name[100];
    char sender_launcher[200] = "sender.exe ";
    char sender_launcher_num[255];
    int i;

    HANDLE hMutex;
    hMutex = CreateMutex(NULL, TRUE, "ConsoleMutex");
    if (hMutex == NULL)
    {
        printf("Mutex creation failure!\n");
        return (int)GetLastError();
    }

    /* 1 */
    printf("Enter the name the binary file: ");
    scanf("%s", binary_name);
    printf("Enter the amount of messages in the file: ");
    scanf("%d", &message_amount);

    /* 2 */
    file = fopen(binary_name, "wb");
    fclose(file);

    /* 3 */
    printf("Enter the amount of Senders: ");
    scanf("%d", &sender_amount);

    /* 4 */
    strcat(sender_launcher, binary_name);

    si = (STARTUPINFO*)malloc((unsigned)sender_amount * sizeof(STARTUPINFO));
    for(i = 0; i < sender_amount; i++)
    {
        ZeroMemory(&si[i], sizeof(STARTUPINFO));
        si[i].cb = sizeof(STARTUPINFO);
    }
    pi = (PROCESS_INFORMATION*)malloc((unsigned)sender_amount * sizeof(STARTUPINFO));

    for(i = 0; i < sender_amount; i++)
    {
        char str[15];
        sprintf(str, "%d", i);
        strcpy(sender_launcher_num, sender_launcher);
        strcat(sender_launcher_num, " ");
        strcat(sender_launcher_num, str);

        printf("%s\n", sender_launcher_num);

        if (!CreateProcess(NULL, sender_launcher, NULL, NULL, TRUE, 0, NULL, NULL, &si[i], &pi[i])) {
            printf("The %d process is not running.\n", i);
            return (int)GetLastError();
        }
    }



    return 0;
}
