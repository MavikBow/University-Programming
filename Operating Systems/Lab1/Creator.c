#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"


int main(int argc, char* argv[])
{
    FILE *input_file, *output_file;
    employee e;

    char* file_name = argv[1];
    int amount_of_notes = atoi(argv[2]);

    output_file = fopen(file_name, "wb");
    if (output_file == NULL)
    {
        perror("Creator >>> Error opening output file");
        exit(0);
    }

    printf("Creator >>> Read files from a .txt file or manual input? [(0).txt/(1)manual]\nCreator >>> ");
    int question;
    scanf("%d", &question);

    if (question != 1)
    {
        input_file = fopen("database.txt", "r");
        if (input_file == NULL) 
        {   
            perror("Creator >>> Error opening employee.txt. Proceeding with manual instead\n");
            question = 1;
        }
    }

    if(question == 1)
    {
        for(int i = 0; i < amount_of_notes; i++)
        {
            printf("Creator >>> Enter employee number, name and work hours %d:\n", i + 1);

            scanf("%d", &e.num);
            scanf("%s", e.name);
            scanf("%d", &e.hours);

            printf("Creator >>> %d %s %d\n", e.num, e.name, e.hours);

            fwrite(&e, sizeof(employee), 1, output_file);
        }
    }
    else
    {
        for(int i = 0; i < amount_of_notes; i++)
        {
            fscanf(input_file, "%d", &e.num);
            fscanf(input_file, "%s", e.name);
            fscanf(input_file, "%d", &e.hours);

            printf("Creator >>> %d %s %d\n", e.num, e.name, e.hours);

            fwrite(&e, sizeof(employee), 1, output_file);
        }
    }

    //if(input_file != NULL)
    //{
        fclose(input_file);
    //}

    fclose(output_file);

    return 0;
}