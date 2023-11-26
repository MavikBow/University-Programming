#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int A, B;
    short weight;
} Road;

typedef struct
{
    unsigned long weight;
    char isMarked;
} City;

struct destination
{
    short weight;
    int city;
};

int cityAmount, roadAmount;
Road*roadArr;
City*cityArr;
struct destination bestRoad;

void parr()
{
    int i;
    for(i = 0; i < cityAmount; i++)
    {
        printf("%lu ", cityArr[i].weight);
    }
    printf("\t b = %d\n", bestRoad.city + 1);
}

int lowerBound(int target)
{
    int left = 0;
    int right = roadAmount;

    int middle;

    while(left < right)
    {
        middle = (left + right) >> 1;

        if (roadArr[middle].A >= target)
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

void merge(Road* arr, int left, int mid, int right)
{
    Road* tmp = (Road *) malloc((unsigned)(right - left + 1) * sizeof(Road));
    int i;

    int pos = 0, p1 = left, p2 = mid + 1;

    while(p1 <= mid && p2 <= right)
    {
        if(arr[p1].A < arr[p2].A)
        {
            tmp[pos].weight = arr[p1].weight;
            tmp[pos].B = arr[p1].B;
            tmp[pos].A = arr[p1].A;

            pos++;
            p1++;
        }
        else
        {
            tmp[pos].weight = arr[p2].weight;
            tmp[pos].B = arr[p2].B;
            tmp[pos].A = arr[p2].A;

            pos++;
            p2++;
        }
    }

    while(p1 <= mid)
    {
        tmp[pos].weight = arr[p1].weight;
        tmp[pos].B = arr[p1].B;
        tmp[pos].A = arr[p1].A;

        pos++;
        p1++;
    }

    while(p2 <= right)
    {
        tmp[pos].weight = arr[p2].weight;
        tmp[pos].B = arr[p2].B;
        tmp[pos].A = arr[p2].A;

        pos++;
        p2++;
    }

    for(i = 0; i < pos; i++)
    {
        arr[i+ left].weight = tmp[i].weight;
        arr[i+ left].B = tmp[i].B;
        arr[i+ left].A = tmp[i].A;
    }

    free(tmp);
}

void mergeSort(Road* arr, int left, int right)
{
    int mid = (right + left) >> 1;

    if(left < right)
    {
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void visit(int A)
{
    int i = lowerBound(A);
    for(; roadArr[i].A == A; i++)
    {
        if(cityArr[roadArr[i].B].isMarked == 0)
        {
            if(cityArr[roadArr[i].B].weight > cityArr[roadArr[i].A].weight + (unsigned long)roadArr[i].weight)
            {
                cityArr[roadArr[i].B].weight = cityArr[roadArr[i].A].weight + (unsigned long)roadArr[i].weight;
            }

            if(roadArr[i].weight < bestRoad.weight)
            {
                bestRoad.weight = roadArr[i].weight;
                bestRoad.city = roadArr[i].B;
            }
        }
    }
    cityArr[A].isMarked = 1;
}

void dijkstra()
{
    bestRoad.city = 0;
    bestRoad.weight = SHRT_MAX;
    
    while(cityArr[cityAmount - 1].isMarked == 0)
    {
        /*parr();*/
        visit(bestRoad.city);
        bestRoad.weight = SHRT_MAX;
    }
}

void readInputs()
{
    FILE *in;
    int i, temp1, temp2;
    short temp3;

    in = fopen("input.txt", "r");
    fscanf(in, "%d %d", &cityAmount, &roadAmount);

    roadAmount <<= 1;

    cityArr = (City*)malloc((unsigned)cityAmount * sizeof(City));
    roadArr = (Road*)malloc((unsigned)roadAmount * sizeof(Road));
    
    for(i = 0; i < cityAmount; i++)
    {
        cityArr[i].isMarked = 0;
        cityArr[i].weight = ULONG_MAX;
    }
    cityArr[0].weight = 0;

    for(i = 0; i < roadAmount; i++)
    {
        fscanf(in, "%d %d %hd", &temp1, &temp2, &temp3);

        roadArr[i].A = temp1 - 1;
        roadArr[i].B = temp2 - 1;
        roadArr[i].weight = temp3;

        i++;

        roadArr[i].B = temp1 - 1;
        roadArr[i].A = temp2 - 1;
        roadArr[i].weight = temp3;
    }

    fclose(in);
}

void writeOutputs()
{
    FILE *out;
    out = fopen("output.txt", "w");
    fprintf(out, "%lu\n", cityArr[cityAmount - 1].weight);
    fclose(out);
    
    free(cityArr);
    free(roadArr);
}

int main()
{
    readInputs();
    mergeSort(roadArr, 0, roadAmount - 1);
    dijkstra();
    writeOutputs();
    return 0;
}