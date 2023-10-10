#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *in, *out;
    long long n;

    in = fopen("input.txt", "r");
    fscanf(in, "%lld", &n);
    fclose(in);

    out = fopen("output.txt", "w");

    short i;
    for(i = 0; i < 61; i++)
    {
        if(n&1)
        {
            fprintf(out, "%u\n", i);
        }

        n >>= 1;
    }

    fclose(out);

    return 0;
}