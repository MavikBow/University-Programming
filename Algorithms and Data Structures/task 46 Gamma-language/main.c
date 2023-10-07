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

    fclose(in);
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

void swap(long** a, long** b)
{
    long* temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    readInputs();

    if(mLength > nLength)
    {
        swap(&arrA, &arrB);
        
        nLength = nLength ^ mLength;
        mLength = nLength ^ mLength;
        nLength = nLength ^ mLength;
    }

    int dp[2][mLength + 1];

    int i, j;

    dp[0][0] = 0;
    dp[1][0] = 0;

    for(j = 1; j <= mLength; j++)
    {
        dp[0][j] = 0;
    }

    for (i = 1; i <= nLength; i++)
    {
        for (j = 1; j <= mLength; j++)
        {
            if (arrA[i - 1] == arrB[j - 1])
            {
                dp[i&1][j] = dp[(i&1)^1][j - 1] + 1;
            }
            else
            {
                int A = dp[(i&1)^1][j];
                int B = dp[i&1][j - 1];

                dp[i&1][j] = (A > B) ? A : B;
            }
        }
    }

    subLen = dp[nLength&1][mLength];

    writeOutputs();

    free(arrA);
    free(arrB);

    return 0;
}