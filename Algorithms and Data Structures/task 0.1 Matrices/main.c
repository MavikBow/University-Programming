#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int amount;

int* dimentions;

void readInputs()
{
    FILE *in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("error opening input.txt\n");
        exit(1);
    }

    fscanf(in, "%d", &amount);

    amount++;

    dimentions = (int*) calloc(amount, sizeof(int));

    fscanf(in, "%d", &dimentions[0]);
    fscanf(in, "%d", &dimentions[1]);
    int i = 0;
    for(i = 2; i < amount; i++)
    {
        int temp;
        fscanf(in, "%d %d", &temp, &dimentions[i]);
    }

    fclose(in);
}

int matrixChain()
{
    int n = amount - 1;
    int mem[n][n];

    int i, l, k;
    for (i = 0; i < n; i++)
    {
        mem[i][i] = 0;
    }

    for (l = 1; l < n; l++) {
        for (i = 0; i < n - l; i++) 
        {
            int j = i + l;
            mem[i][j] = INT_MAX;
            for (k = i; k < j; k++)
            {
                int newMem = mem[i][k] + mem[k + 1][j] + dimentions[i] * dimentions[k + 1] * dimentions[j + 1];
                mem[i][j] = mem[i][j] < newMem ? mem[i][j] : newMem;
            }
        }
    }

    return mem[0][n - 1];
}

void writeOutputs(int* x)
{
    FILE* out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("error opening output.txt\n");
        exit(1);
    }

    fprintf(out, "%d\n", *x);

    fclose(out);
}

int main()
{
    readInputs();    

    int result = matrixChain();

    free(dimentions);

    writeOutputs(&result);

    return 0;
}