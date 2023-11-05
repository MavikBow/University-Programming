#include <stdio.h>
#include <stdlib.h>

short size, x, y;
short** arr;
short amount;

int main()
{
    FILE *in, *out;
    short i;
    short j, k;

    in = fopen("input.txt", "r");
    fscanf(in, "%hd", &size);

    arr = (short**)calloc((short)size * (short)size, sizeof(short *));
    for(j = 0; j < size; j++)
    {
       arr[j] = (short *)calloc(size, sizeof(short)); 
    }

    fscanf(in, "%hd", &amount);

    for(i = 0; i < amount; i++)
    {
        fscanf(in, "%hd %hd", &x, &y);
        arr[x - 1][y - 1] = 1;
        arr[y - 1][x - 1] = 1;
    }

    fclose(in);

    out = fopen("output.txt", "w");

    for(j = 0; j < size; j++)
    {
        for(k = 0; k < size; k++)
        {
            fprintf(out, "%hd ", arr[j][k]);
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