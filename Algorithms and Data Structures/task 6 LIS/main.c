#include <stdio.h>
#include <stdlib.h>

int length, lisLength = 0;
int* arrN, * arrI;

void readInputs() {
    FILE *in;

    in = fopen("input.txt", "r");
    if (in == NULL) {
        printf("Could not open input.txt");
        return;
    }

    fscanf(in, "%d", &length);

    arrN = (int *) malloc(length * sizeof(int));
    arrI = (int *) calloc(length, sizeof(int));

    int i;
    for(i = 0; i < length; i++)
    {
        fscanf(in, "%d", &arrN[i]);
    }

    fclose(in);
}

void writeOutputs() {
    FILE *out;

    out = fopen("output.txt", "w");
    if (out == NULL) {
        printf("Could not open output.txt");
        return;
    }

    fprintf(out, "%d\n", lisLength);

    fclose(out);
}

int upperBound(int target, int size)
{
    int left = 0;
    int right = size;

    int middle;

    while(left < right)
    {
        middle = (left + right) >> 1;

        if (arrI[middle] > target)
        {
            right = middle;
        }
        else
        {
            left = middle + 1;
        }
    }

    return left;
}

void lis()
{
    int i;
    for(i = 0; i < length; i++)
    {
        int pos = upperBound(arrN[i], lisLength);

        if(pos > 0)
        {
            if(arrI[pos - 1] == arrN[i])
            {
                continue;
            }
        }

        if(pos == lisLength)
        {
            lisLength++;
        }

        arrI[pos] = arrN[i];
    }
}

int main()
{
    readInputs();

    lis();

    writeOutputs();

    free(arrN);
    free(arrI);

    return 0;
}