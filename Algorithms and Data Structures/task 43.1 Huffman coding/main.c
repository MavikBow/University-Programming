#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

#define ull unsigned long long

ull ptr1 = 0, ptr2 = 0, ptrPush = 0;
ull N, **arr;
ull result = 0, negResult = 0; 

void readInputs()
{
    FILE* in = fopen("huffman.in", "r");
    fscanf(in, "%llu", &N);
    arr = (ull**)calloc(2, sizeof(ull*));
    arr[0] = (ull*)calloc(N + 10, sizeof(ull));
    arr[1] = (ull*)calloc(N + 10, sizeof(ull));
    ull i;
    for(i = 0; i < N; i++)
    {
        fscanf(in, "%llu", &arr[0][i]);
    }
} 

void writeOutputs()
{
    FILE* out = fopen("huffman.out", "w");
    fprintf(out, "%llu\n", result - negResult);
} 

void printf_arr2()
{
    ull i;
    printf("\n======\n");
    for(i = 0; i < N; i++)
    {
        printf("%llu ", arr[1][i]);
    }
    printf("\n======");
}
void printf_arr()
{
    ull i;
    printf("\n====================\n");
    for(i = 0; i < N; i++)
    {
        printf("%llu ", arr[0][i]);
    }
    printf("\n");
    for(i = 0; i < N; i++)
    {
        printf("%llu ", arr[1][i]);
    }
    printf("\n====================");
}

void doHuffman()
{
    ull counter[2] = {N, N};

    ull i = 0;
    for(;counter[0] != 1 && counter[1] != 1; i++)
    {
        ull counterNew = 0;

        printf_arr();

        arr[(i&1)^1][0] = arr[i&1][0] + arr[i&1][1];
        result += arr[(i&1)^1][0];
        counterNew++;

        //ull size = N - i;
        ull j;
        ull k = 0;

        for(j = 2; j < counter[i&1];)
        {
        //printf_arr2();
            if(j == counter[i&1] - 1)
            {
                //printf("\n%llu\t%llu\n", j, arr[(i&1)^1][k]);

                arr[(i&1)^1][k] += arr[i&1][j];
                result += arr[(i&1)^1][k];
                j++;
                break;
            }
            else
            {
                if(arr[(i&1)^1][j] < arr[i&1][j+1]) 
                {
                    arr[(i&1)^1][k] += arr[i&1][j];
                    result += arr[(i&1)^1][k];
                    j++;
                }
                else
                {
                    arr[(i&1)^1][++k] = arr[i&1][j] + arr[i&1][j+1];
                    result += arr[(i&1)^1][k];
                    j+=2;
                    counterNew++;
                }
            }
        }

        counter[(i&1)^1] = counterNew;
    }
} 

void doHuffman1()
{
    while(ptr1 < N || arr[1][ptr2 + 1] != 0)
    {
        if(ptr1 >= N)
        {
            arr[1][ptrPush] = arr[1][ptr2] + arr[1][ptr2 + 1];
            result += arr[1][ptrPush];

            ptr2 += 2;
            ptrPush++;
            continue;
        }

        if(arr[1][ptr2] == 0)
        {
            ull temp = arr[0][ptr1] + arr[0][ptr1 + 1];
            arr[1][ptrPush] = temp;
            result += arr[1][ptr2];
            
            ptr1 += 2;
            ptrPush++;
            continue;
        }

        if(ptr1 == N - 1)
        {
            if(arr[1][ptr2 + 1] <= arr[0][ptr1])
            {
                arr[1][ptrPush] = arr[1][ptr2] + arr[1][ptr2 + 1];
                result += arr[1][ptrPush];

                ptr2 += 2;
            }
            else
            {
                arr[1][ptrPush] = arr[1][ptr2] + arr[0][ptr1];
                result += arr[1][ptrPush];

                ptr1++;
                ptr2++;
            }
            
            ptrPush++;
            continue;
        }

        if(arr[1][ptr2 + 1] == 0)
        {
            if(arr[0][ptr1 + 1] > arr[1][ptr2])
            {
                arr[1][ptrPush] = arr[1][ptr2] + arr[0][ptr1];
                result += arr[1][ptrPush];

                ptrPush++;
                ptr1++;
                ptr2++;
            }
            else
            {
                arr[1][ptrPush] = arr[0][ptr1] + arr[0][ptr1 + 1];
                result += arr[1][ptrPush];

                ptrPush++;
                ptr1 += 2;
            }
            continue;
        }

        if(arr[0][ptr1 + 1] < arr[1][ptr2])
        {
            arr[1][ptrPush] = arr[0][ptr1] + arr[0][ptr1 + 1];
            result += arr[1][ptrPush];

            ptrPush++;
            ptr1 += 2;
            continue;
        }
    
        if(arr[1][ptr2 + 1] < arr[0][ptr1])
        {
            arr[1][ptrPush] = arr[1][ptr2] + arr[1][ptr2 + 1];
            result += arr[1][ptrPush];

            ptrPush++;
            ptr2 += 2;
            continue;
        }

        if(arr[0][ptr1 + 1] >= arr[1][ptr2])
        {
            arr[1][ptrPush] = arr[0][ptr1] + arr[1][ptr2];
            result += arr[1][ptrPush];

            ptr1++;
            ptr2++;
            ptrPush++;
        }
        continue;
    }
}

void doHuffman2()
{
    while(ptr1 < N || arr[1][ptr2] != 0)
    {
        //printf_arr();
        //printf("%llu", result);
        ull temp = 0;

        if(ptr1 >= N) 
        {
            temp = arr[1][ptr2];
            ptr2++;
        }
        else if(arr[1][ptr2] == 0 || (arr[0][ptr1] < arr[1][ptr2]))
        {
            temp = arr[0][ptr1];
            ptr1++;
        }
        else
        {
            temp = arr[1][ptr2];
            ptr2++;
        }

        if(ptr1 >= N)
        {
            temp += arr[1][ptr2];
            ptr2++;
        }
        else if(arr[1][ptr2] == 0 || (arr[0][ptr1] < arr[1][ptr2]))
        {
            temp += arr[0][ptr1];
            ptr1++;
        }
        else
        {
            temp += arr[1][ptr2];
            ptr2++;
        }

        result += temp;
        negResult = temp;
        arr[1][ptrPush] = temp;
        ptrPush++;        
    }
}

int main()
{
    readInputs();
    doHuffman1();
    writeOutputs();
    return 0;
}