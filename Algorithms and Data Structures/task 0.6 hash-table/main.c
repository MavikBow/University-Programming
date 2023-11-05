#include <stdio.h>
#include <stdlib.h>

short m, c, n;
int* arr, key;

short address(int x, short i)
{
    return (((short)(x % (int)m) + c * i) % m);
}

void insert(int value)
{
    short i = 0;
    short ad;
    do
    {
        ad = address(value, i);
        i++;
    } while (arr[ad] != -1 && arr[ad] != value);

    arr[ad] = value;
}

int main()
{
    FILE *in, *out;
    short i;

    in = fopen("input.txt", "r");
    fscanf(in, "%hd%hd%hd", &m, &c, &n);

    arr = (int*)malloc(m * sizeof(int));

    for(i = 0; i < m; i++)
    {
        arr[i] = -1;
    }

    for(i = 0; i < n; i++)
    {
        fscanf(in, "%d", &key);
        insert(key);
    }

    fclose(in);

    out = fopen("output.txt", "w");

    for(i = 0; i < m; i++)
    {
        fprintf(out, "%d ", arr[i]);
    }
    fprintf(out, "\n");

    free(arr);
    fclose(out);

    return 0;
}