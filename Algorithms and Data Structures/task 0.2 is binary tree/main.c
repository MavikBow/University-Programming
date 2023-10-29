#include <stdio.h>
#include <stdlib.h>

int*arr, size, success = 1;

void bin_check(int target, int i)
{
    if(i > size) return;

    if(target > arr[i])
    {
        success = 0;
        return;
    }

    bin_check(arr[i], i<<1);
    bin_check(arr[i], (i<<1) + 1);
}
int main()
{
    FILE *in, *out;

    in = fopen("input.txt", "r");
    fscanf(in, "%d", &size);

    arr = (int*)malloc((size + 1) * sizeof(int));

    int i;
    for(i = 1; i <= size; i++)
    {
        fscanf(in, "%d", &arr[i]);
    }

    fclose(in);

    out = fopen("output.txt", "w");

    bin_check(0, 1);

    if(success != 0)
    {
        fprintf(out, "Yes\n");
    }
    else
    {
        fprintf(out, "No\n");
    }

    free(arr);
    fclose(out);

    return 0;
}