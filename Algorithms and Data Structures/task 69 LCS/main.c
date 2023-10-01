#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int length;
int* arrA, * arrB;

int subLen = 0;
int* subA, * subB;

//int** dp;

void readInputs()
{
    scanf("%d", &length);

    arrA = (int *) malloc(length * sizeof(int));
    arrB = (int *) malloc(length * sizeof(int));

    int i;
    for(i = 0; i < length; i++)
    {
        scanf("%d", &arrA[i]);
    }

    for(i = 0; i < length; i++)
    {
        scanf("%d", &arrB[i]);
    }
}

void writeOutputs()
{
    int i;

    printf("%d\n", subLen);

    for(i = 0; i < subLen; i++)
    {
        printf("%d ", subA[i]);
    }

    printf("\n");

    for(i = 0; i < subLen; i++)
    {
        printf("%d ", subB[i]);
    }

    printf("\n");
}

void memAlloc()
{
    subA = (int *) malloc(length * sizeof(int));
    subB = (int *) malloc(length * sizeof(int));

    int i;
    //for (i = 0; i < length; i++)
    //{
     //   arrA[i] = INT_MAX;
       // arrB[i] = INT_MAX;
    //}

    /*int i, j;

    dp = (int **)calloc(length + 1, sizeof(int *));

    for(i = 0; i < length; i++)
    {
        dp[i] = (int *)calloc(length + 1, sizeof(int));
    }*/
}

void memFree()
{
    free(arrA);
    free(arrB);
    free(subA);
    free(subB);

    /*int i;
    for (i = 0; i < length; i++)
    {
        free(dp[i]);
    }

    free(dp);*/
}

void deposit(int i, int j, int N)
{
    int good = 0;

    if (N == 1)
    {
        good = 1;
    }
    else if (N > 1)
    {
        if (i > subA[N - 2] && j > subB[N - 2])
        {
            good = 1;
        }
    }

    if (good == 1)
    {
        if (N > subLen)
        {
            subA[N - 1] = i;
            subB[N - 1] = j;
            subLen = N;
            return;
        }

        if (subA[N-1] + subB[N-1] > i + j)
        {
            subA[N - 1] = i;
            subB[N - 1] = j;
        }
        else if (subA[N-1] + subB[N-1] == i + j)
        {
            if (subA[N-1] * subB[N-1] < i * j)
            {
                subA[N - 1] = i;
                subB[N - 1] = j;
            }
        }

    }
    /*if (N = subLen)
    {
        if (i < subA[N - 1] || j < subB[j - 1])
        {
            subA[N - 1] = i;
            subB[N - 1] = j;
            subLen = N;
        }
    }*/
}

int main()
{
    readInputs();

    memAlloc();

    int dp[length + 1][length + 1];

    int i, j;

    for (i = 0; i <= length; i++)
    {
        for (j = 0; j <= length; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (arrA[i - 1] == arrB[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                deposit(i - 1, j - 1, dp[i][j]);

                //printf("%d\t%d\t%d\n", i -1,j-1,dp[i][j]);
            }
            else
            {
                int A = dp[i - 1][j];
                int B = dp[i][j - 1];

                dp[i][j] = (A > B) ? A : B;
            }
        }
    }

    writeOutputs();

    memFree();

    return 0;
}