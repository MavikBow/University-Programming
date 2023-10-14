#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct
{
    int index;
    long value;
} Element;

int aLength, bLength, cLength = 0, dLength = 0, lsc_length = 0;

Element* arrA;
long* arrA_lookup, * arrB;
int* arrC, * arrD;

int subLen = 0;

void inputA(FILE* in, int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
        fscanf(in, "%ld", &arrA[i].value);
        arrA[i].index = i;

        arrA_lookup[i] = arrA[i].value;
    }
}

void inputB(FILE* in, int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
        fscanf(in, "%ld", &arrB[i]);
    }
}

void readInputs()
{
    FILE *in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("error opening input.txt\n");
        exit(1);
    }

    int first, second;

    fscanf(in, "%d %d", &first, &second);

    if (first <= second)
    {
        aLength = first;
        bLength = second;
    }
    else
    {
        bLength = first;
        aLength = second;
    }

    arrA = (Element *) malloc(aLength * sizeof(Element));
    arrA_lookup = (long *) malloc(aLength * sizeof(long));
    arrB = (long *) malloc(bLength * sizeof(long));
    arrC = (int *) malloc(bLength * sizeof(int));
    arrD = (int *) calloc(bLength, sizeof(int));

    if(first <= second)
    {
        inputA(in, aLength);
        inputB(in, bLength);
    }
    else
    {
        inputB(in, bLength);
        inputA(in, aLength);
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

    fprintf(out, "%d\n", lsc_length);

    fclose(out);
}

void merge(Element* arr, int left, int mid, int right)
{
    Element* tmp = (Element *) malloc((right - left + 1) * sizeof(Element));

    int pos = 0, p1 = left, p2 = mid + 1;

    while(p1 <= mid && p2 <= right)
    {
        if(arr[p1].value < arr[p2].value)
        {
            tmp[pos].index = arr[p1].index;
            tmp[pos].value = arr[p1].value;

            pos++;
            p1++;
        }
        else
        {
            tmp[pos].index = arr[p2].index;
            tmp[pos].value = arr[p2].value;

            pos++;
            p2++;
        }
    }

    while(p1 <= mid)
    {
        tmp[pos].index = arr[p1].index;
        tmp[pos].value = arr[p1].value;

        pos++;
        p1++;
    }

    while(p2 <= right)
    {
        tmp[pos].index = arr[p2].index;
        tmp[pos].value = arr[p2].value;

        pos++;
        p2++;
    }

    int i;
    for(i = 0; i < pos; i++)
    {
        arr[i+ left].index = tmp[i].index;
        arr[i+ left].value = tmp[i].value;
    }

    free(tmp);
}

void mergeSort(Element* arr, int left, int right)
{
    int mid = (right + left) / 2;

    if(left < right)
    {
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int binary_search(long target)
{
    int left = 0;
    int right = aLength;

    int middle;

    while(left < right)
    {
        middle = (left + right) >> 1;

        if (arrA[middle].value == target)
        {
            return arrA[middle].index;
        }
        if (arrA[middle].value > target)
        {
            right = middle;
        }
        else
        {
            left = middle + 1;
        }
    }

    return -1;
}

int upperBound(int target, int size)
{
    int left = 0;
    int right = size;

    int middle;

    while(left < right)
    {
        middle = (left + right) >> 1;

        if (arrD[middle] > target)
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

void elementSearch()
{
    int i, k = 0;
    for(i = 0; i < bLength; i++)
    {
        int pos = binary_search(arrB[i]);

        if(pos >= 0)
        {
            arrC[k++] = pos;
        }
    }

    cLength = k;
}

void lis()
{
    int i;
    for(i = 0; i < cLength; i++)
    {
        int pos = upperBound(arrC[i], dLength);

        if(pos > 0)
        {
            if(arrD[pos - 1] == arrC[i])
            {
                continue;
            }
        }

        if(pos == dLength)
        {
            dLength++;
        }

        arrD[pos] = arrC[i];
    }
}

int main()
{
    readInputs();

    mergeSort(arrA, 0, aLength - 1);

    elementSearch();

    lis();

    lsc_length = dLength;

    writeOutputs();

    free(arrA);
    free(arrA_lookup);
    free(arrB);
    free(arrC);
    free(arrD);

    return 0;
}