#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *in, *out;
    int size, x, y, amount;
    char** arr;
    int i, j;

    in = fopen("input.txt", "r");
    fscanf(in, "%d", &size);

    arr = (char**)calloc((long long)size * (long long)size, sizeof(char*));
    for(j = 0; j < size; j++)
    {
       arr[j] = (char *)calloc(size, sizeof(char)); 
    }

    fscanf(in, "%d", &amount);

    for(i = 0; i < amount; i++)
    {
        fscanf(in, "%d %d", &x, &y);
        arr[x - 1][y - 1] = 1;
        arr[y - 1][x - 1] = 1;
    }

    fclose(in);

    out = fopen("output.txt", "w");

    for(i = 0; i < size; i++)
    {
        int counter = 0;
        for(j = 0; j < size; j++)
        {
            if(arr[i][j]) counter++;
        }

        fprintf(out, "%d ", counter);

        for(j = 0; j < size; j++)
        {
            if(arr[i][j]) fprintf(out, "%d ", j + 1);
        }

        fprintf(out, "\n");
    }

    for(j = 0; j < size; j++)
    {
        free(arr[j]);
    }
    free(arr);
    fclose(out);

    return 0;
}