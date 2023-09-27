#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Employee.h"

int main()
{
    char binary_name[100];
    char amount_of_notes[5];
    employee e;

    printf("Enter the name of the binary file: ");
    scanf("%s", binary_name);
    printf("Enter the amount of notes: ");
    scanf("%s", amount_of_notes);

    char creator_launcher[200] = "creator.exe ";
    strcat(creator_launcher, binary_name);
    strcat(creator_launcher, " ");
    strcat(creator_launcher, amount_of_notes);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, creator_launcher, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("The Creator process is not running.\n");
        return GetLastError();
    }
    WaitForSingleObject(pi.hProcess, INFINITE);


    FILE *input_file;
    input_file = fopen(binary_name, "rb");
    if(input_file == NULL)
    {
        printf("Couldn't open the binary file");
    }

    printf("Reading the .bin file to the console\n");
    while (fread(&e, sizeof(employee), 1, input_file))
    {
        e.name[strcspn(e.name, "\n")] = '\0';

        printf("%d\t%s\t%d\n", e.num, e.name, e.hours);
    }

    fclose(input_file);


    char report_name[100];
    char pay_per_hour[5];

    printf("Enter the name of the report file: ");
    scanf("%s", report_name);
    printf("Enter the pay per hour: ");
    scanf("%s", pay_per_hour);

    char reporter_launcher[200] = "reporter.exe ";
    strcat(reporter_launcher, binary_name);
    strcat(reporter_launcher, " ");
    strcat(reporter_launcher, report_name);
    strcat(reporter_launcher, " ");
    strcat(reporter_launcher, pay_per_hour);

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, reporter_launcher, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("The Creator process is not running.\n");
        return GetLastError();
    }
    WaitForSingleObject(pi.hProcess, INFINITE);

    input_file = fopen(report_name, "r");
    if(input_file == NULL)
    {
        printf("Couldn't open the report file");
    }

    printf("\nReading the %s to the console\n", report_name);

    char worker[100];
    while (fgets(worker, sizeof(worker), input_file) != NULL)
    {
        printf("%s", worker);
    }

    fclose(input_file);

    return 0;
}