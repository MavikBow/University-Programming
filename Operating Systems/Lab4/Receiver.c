#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Message.h"

int main()
{
    FILE* file;
    char binary_name[100];
    int message_amount;
    int sender_amount;
    char sender_launcher[200] = "sender.exe ";

    // 1
    printf("Enter the name the binary file: ");
    scanf("%s", binary_name);
    printf("Enter the amount of messages in the file: ");
    scanf("%d", &message_amount);

    // 2
    file = fopen(binary_name, "rb");
    fclose(file);

    // 3
    printf("Enter the amount of Senders: ");
    scanf("%d", &sender_amount);

    // 4
    strcat(sender_launcher, binary_name);

    return 0;
}
