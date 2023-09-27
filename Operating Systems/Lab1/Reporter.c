#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"

int main(int argc, char* argv[])
{
    FILE *input_file, *output_file;
    employee e;

    char* input_file_name = argv[1];
    char* output_file_name = argv[2];
    int pay_per_hour = atoi(argv[3]);

    input_file = fopen(input_file_name, "rb");
    if (input_file == NULL)
    {
        perror("Reporter >>> Error opening input file");
        exit(1);
    }

    output_file = fopen(output_file_name, "w");
    if (output_file == NULL)
    {
        perror("Reporter >>> Error opening output file");
    }

    fprintf(output_file, "REPORT ON %s\n", input_file_name);
    fprintf(output_file, "NUMBER\tNAME\tHOURS\tSALARY\n");

    while (fread(&e, sizeof(employee), 1, input_file)) 
    {
        e.name[strcspn(e.name, "\n")] = '\0';

        fprintf(output_file, "%d\t%s\t%d\t%d\n", e.num, e.name, e.hours, e.hours * pay_per_hour);
    }

    if (input_file != NULL)
    {
        fclose(input_file);
    }
    fclose(output_file);

    return 0;
}