#include <stdio.h>
#include <stdlib.h>

int* arr, size;
int value;

int main()
{
    FILE *in, *out;
    int i, j;

    in = fopen("input.txt", "r");
    fscanf(in, "%d", &size);

    arr = (int*)calloc(size, sizeof(int));

    for(i = 1; i <= size; i++)
    {
        for(j = 1; j <= size; j++)
        {
            fscanf(in, "%d", &value);
            if(value) arr[j - 1] = i; 
        }
    }

    fclose(in);

    out = fopen("output.txt", "w");

    for(i = 0; i < size; i++)
    {
        fprintf(out, "%d ", arr[i]);
    }
    fprintf(out, "\n");

    free(arr);
    fclose(out);

    return 0;
}