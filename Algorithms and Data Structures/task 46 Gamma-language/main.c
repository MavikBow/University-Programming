#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int nLength, mLength;
long* arrA, * arrB;

int subLen = 0;

void readInputs()
{
    FILE *in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("error opening input.txt\n");
        exit(1);
    }

    fscanf(in, "%d %d", &nLength, &mLength);

    arrA = (long *) malloc(nLength * sizeof(long));
    arrB = (long *) malloc(mLength * sizeof(long));

    int i;
    for(i = 0; i < nLength; i++)
    {
        fscanf(in, "%ld", &arrA[i]);
    }

    for(i = 0; i < mLength; i++)
    {
        fscanf(in, "%ld", &arrB[i]);
    }
}

void writeOutputs()
{
    FILE* out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("error opening output.txt\n");
        exit(1);
    }

    fprintf(out, "%d\n", subLen);

    fclose(out);
}

int main()
{
    readInputs();

    int dp[nLength + 1][mLength + 1];



    int i, j;

    for (i = 0; i <= nLength; i++)
    {
        for (j = 0; j <= mLength; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else
            {
                if (arrA[i - 1] == arrB[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    

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
    }

    subLen = dp[nLength][mLength];

    writeOutputs();

    free(arrA);
    free(arrB);

    return 0;
}