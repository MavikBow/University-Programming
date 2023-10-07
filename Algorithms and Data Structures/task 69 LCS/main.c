#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int length;
int* arrA, * arrB;

int subLen = 0;
int* subA, * subB, *subIndex;

int *finalA, *finalB;

int depLength = 0;

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

    printf("%d\n", subLen);

    if (subLen != 0)
    {
        int i;
        for(i = 0; i < subLen; i++)
        {
            printf("%d ", finalA[i]);
        }

        printf("\n");

        for(i = 0; i < subLen; i++)
        {
            printf("%d ", finalB[i]);
        }

        printf("\n");
    }
}

void analyze(int MAX)
{
    subLen = MAX;

    finalA = (int *) malloc(subLen * sizeof(int));
    finalB = (int *) malloc(subLen * sizeof(int));

    int N, k, edgeX = INT_MAX, edgeY = INT_MAX, chosenA, chosenB;
    for (N = subLen; N > 0; N--)
    {
        chosenA = INT_MIN;
        chosenB = INT_MIN;

        for (k = 0; k < depLength; k++)
        {
            if (subIndex[k] == N)
            {
                if (subA[k] >= chosenA && subB[k] >= chosenB)
                {
                    if (subA[k] < edgeX && subB[k] < edgeY)
                    {
                        finalA[N - 1] = subA[k];
                        finalB[N - 1] = subB[k];
                        edgeX = subA[k];
                        edgeY = subB[k];
                    }
                }
            }
        }
    }
}

void memAlloc()
{
    subA = (int *) malloc(length * length * sizeof(int));
    subB = (int *) malloc(length * length * sizeof(int));
    subIndex = (int *) malloc(length * length * sizeof(int));

    int i;
}

void memFree()
{
    free(arrA);
    free(arrB);
    free(subA);
    free(subB);
    free(subIndex);
    free(finalA);
    free(finalB);
}

void deposit(int i, int j, int N)
{
    int good = 0;

    subA[depLength] = i;
    subB[depLength] = j;
    subIndex[depLength] = N;

    depLength++;


    /*

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

    analyze(dp[length][length]);

    writeOutputs();

    memFree();

    return 0;
}