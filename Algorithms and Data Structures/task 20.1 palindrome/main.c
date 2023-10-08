#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[7001];
char pal[7001];

void readInputs(char *S) {
    FILE *in;

    in = fopen("input.txt", "r");
    if (in == NULL) {
        printf("Could not open input.txt");
        return;
    }

    fscanf(in, "%s", S);

    fclose(in);
}

void writeOutputs(int L, char *P) {
    FILE *out;

    out = fopen("output.txt", "w");
    if (out == NULL) {
        printf("Could not open output.txt");
        return;
    }

    fprintf(out, "%d\n%s\n", L, P);

    fclose(out);
}

int palidrome(char *S, char *P)
{
    int length = strlen(P);
    length = strlen(S);

    //int dp[length][length];

    int k;
    int **dp = malloc((length + 1) * sizeof(int *));
    for (k = 0; k < (length + 1); k++) {
        dp[k] = malloc((length + 1) * sizeof(int));
    }


    int i, j;

    // making the dp matrix

    for(i = 1; i < length; i++)
    {
        dp[i][i - 1] = 0;
    }

    for(i = length - 1; i > -1; i--)
    {
        dp[i][i] = 1;
        for(j = i + 1; j < length; j++)
        {
            if(S[i] == S[j])
            {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            }
            else
            {
                int A = dp[i + 1][j];
                int B = dp[i][j - 1];
                
                dp[i][j] = (A > B) ? A : B;
            }
        }
    }

    // Backtracking the dp matrix

    i = 0;
    j = length - 1;

    int pLength = dp[0][length - 1];
    int pivot1 = 0;
    int pivot2 = pLength - 1;

    P[pLength] = '\0';

    while(pLength > 0)
    {
        if(S[i] == S[j])
        {
            P[pivot1] = S[i];
            P[pivot2] = S[i];
            pivot1++;
            pivot2--;
            pLength -= 2;

            i++;
            j--;
        }
        else
        {
            (dp[i + 1][j] > dp[i][j - 1]) ? i++ : j--;
        }
    }

    pLength = dp[0][length - 1];

    for (k = 0; k < (length + 1); k++) {
        free(dp[k]);
    }
    free(dp);


    return pLength;
}

int main()
{
    readInputs(str);

    int length = palidrome(str, pal);

    writeOutputs(length, pal);

    return 0;
}