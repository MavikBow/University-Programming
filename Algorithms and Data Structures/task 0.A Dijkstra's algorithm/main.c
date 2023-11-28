#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int B;
    short weight;
    int next;
} Road;

typedef struct
{
    unsigned long weight;
    int number;
} City;

City*cityTree;
Road*roadList;
int*roadHead;
const unsigned long VISITED = ULONG_MAX;
const unsigned long NOTVISITED = ULONG_MAX - 1;
unsigned long answer;

int cityAmount, treeSize, roadAmount, roadWriter, CITYSHIFT;

void cityTree_create()
{
    int i, j, k;
    CITYSHIFT = (treeSize>>1) - 1;
    i = CITYSHIFT;
    j = CITYSHIFT;

    for(i = treeSize >> 1, k = 1; i < (treeSize >> 1) + cityAmount; i++, k++)
    {
        cityTree[i].number = k;
    }
    for(i = 0; i < treeSize; i++)
    {
        cityTree[i].weight = NOTVISITED;
    }

    cityTree[j].weight = 0;
    cityTree[j].number = 0;

    for(i = j; i > 0; i = (i-1)>>1)
    {
        cityTree[i] = cityTree[j];
    }
    cityTree[0] = cityTree[j];
}
void cityTree_set(int i, unsigned long weight)
{
    cityTree[i + CITYSHIFT].weight = weight;
}
void cityTree_update(int i)
{
    int j = i + CITYSHIFT; 
    City temp = cityTree[j];

    for(; j > 0; j = (j-1)>>1)
    {
        cityTree[j] = temp;

        if((j&1) == 0)
            temp = cityTree[j-1];
        else
            temp = cityTree[j+1];
    
        if(temp.weight > cityTree[j].weight)
        {
            temp = cityTree[j];
        }
    }

    cityTree[0] = temp;
}
void cityTree_unmark(int i)
{
    cityTree_set(i, VISITED);
    cityTree_update(i);
}
unsigned long cityTree_getWeight(int i)
{
    return cityTree[i + CITYSHIFT].weight;
}

void roadList_addRoad(int A, int B, short weight)
{
    Road temp;
    temp.B = B;
    temp.weight = weight;
    temp.next = roadHead[A];

    roadList[roadWriter] = temp;
    roadHead[A] = roadWriter;
    roadWriter++;
}

int step2(int x)
{
    int res = 1;
    while(res < x)
    {
        res <<= 1;
    }
    return res;
}

void visit(int A)
{
    int j;
    unsigned long temp;
    for(j = roadHead[A]; j; j = roadList[j].next)
    {
        if(cityTree_getWeight(roadList[j].B) != VISITED)
        {
            temp = cityTree_getWeight(A) + (unsigned long)roadList[j].weight;

            if(cityTree_getWeight(roadList[j].B) > temp)
            {
                cityTree_set(roadList[j].B, temp);
                cityTree_update(roadList[j].B);
            }
        }
    }
    
    answer = cityTree_getWeight(A);
    cityTree_unmark(A);
}

void dijkstra()
{
    while(cityTree_getWeight(cityAmount - 1) != VISITED)
    {
        visit(cityTree[0].number);
    }
}

void readInputs()
{
    FILE *in;
    int i, temp1, temp2;
    short temp3;

    in = fopen("input.txt", "r");
    fscanf(in, "%d %d", &cityAmount, &roadAmount);

    treeSize = step2(cityAmount) << 1;

    cityTree = (City*)malloc((unsigned)treeSize * sizeof(City));
    roadList = (Road*)malloc((unsigned)((roadAmount << 1) + 1) * sizeof(Road));
    roadHead = (int*)calloc((unsigned)cityAmount, sizeof(int));
    
    roadWriter = 1;
    
    for(i = 0; i < roadAmount; i++)
    {
        fscanf(in, "%d %d %hd", &temp1, &temp2, &temp3);

        temp1--;
        temp2--;

        roadList_addRoad(temp1, temp2, temp3);
        roadList_addRoad(temp2, temp1, temp3);
    }

    fclose(in);
}

void writeOutputs()
{
    FILE *out;
    out = fopen("output.txt", "w");
    fprintf(out, "%lu\n", answer);
    fclose(out);
}

int main()
{
    readInputs();
    cityTree_create();
    dijkstra();
    writeOutputs();

    free(cityTree);
    free(roadList);
    free(roadHead);

    return 0;
}