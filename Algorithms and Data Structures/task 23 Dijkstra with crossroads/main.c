#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    unsigned weight;
    int number;
} City;

typedef struct
{
    short x, y, visits_left, previous_visit, roads_incoming;
} CityData;

City*cityTree;
short**roadTable;
CityData*dataBase;

const unsigned FULLYVISITED = UINT_MAX;
const unsigned NOTVISITED = UINT_MAX - 1;
const unsigned NOTFULLYVISITED = UINT_MAX - 2;

unsigned answer = UINT_MAX - 1;
char endVisited = 0;

int cityAmount, treeSize, roadAmount, CITYSHIFT, startCity, endCity;
unsigned penalty;

void cityTree_create()
{
    int i, k;
    CITYSHIFT = (treeSize>>1) - 1;
    i = CITYSHIFT;

    for(i = treeSize >> 1, k = 1; i < (treeSize >> 1) + cityAmount; i++, k++)
    {
        cityTree[i].number = k;
    }
    for(i = 0; i < treeSize; i++)
    {
        cityTree[i].weight = NOTVISITED;
    }
}
void cityTree_set(int i, unsigned weight)
{
    int j = i + CITYSHIFT; 
    City temp = cityTree[j];
    
    temp.weight = weight;

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
unsigned cityTree_getWeight(int i)
{
    return cityTree[i + CITYSHIFT].weight;
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

void readInputs()
{
    FILE *in;
    short i, j, temp1, temp2, temp3;

    in = fopen("input.txt", "r");
    fscanf(in, "%d %d %u", &cityAmount, &roadAmount, &penalty);

    cityAmount++;

    treeSize = step2(cityAmount) << 1;

    cityTree = (City*)malloc((unsigned)treeSize * sizeof(City));
    dataBase = (CityData*)calloc((unsigned)cityAmount, sizeof(CityData));
    roadTable = (short**)malloc((unsigned)cityAmount * sizeof(short*));
    for(i = 0; i < cityAmount; i++)
    {
        roadTable[i] = (short*)malloc((unsigned)cityAmount * sizeof(short));
    }

    for(i = 0; i < cityAmount; i++)
        for(j = 0; j < cityAmount; j++)
        {
            roadTable[i][j] = -1;
        }

    for(i = 1; i < cityAmount; i++)
    {
        fscanf(in, "%hd %hd", &temp1, &temp2);

        dataBase[i].x = temp1;
        dataBase[i].y = temp2;
    }
    
    for(i = 0; i < roadAmount; i++)
    {
        fscanf(in, "%hd %hd %hd", &temp1, &temp2, &temp3);

        roadTable[temp1][temp2] = temp3;
        roadTable[temp2][temp1] = temp3;

        dataBase[temp1].roads_incoming++;
        dataBase[temp2].roads_incoming++;
        dataBase[temp1].visits_left++;
        dataBase[temp2].visits_left++;
    }

    fscanf(in, "%d %d", &startCity, &endCity);
    
    fclose(in);
}

void init()
{
    dataBase[0].x = dataBase[startCity].x;
    dataBase[0].y = dataBase[startCity].y;
    dataBase[0].y--;
    dataBase[startCity].previous_visit = 0;


    /*roadTable[0][startCity] = 0;*/

    cityTree_create();
    cityTree_set(startCity, 0);
    cityTree_set(0, FULLYVISITED);
}

void writeOutputs()
{
    FILE*out = fopen("output.txt", "w");
    if(answer == NOTVISITED)
        fprintf(out, "No\n");
    else
        fprintf(out, "Yes\n%u\n", answer);
    fclose(out);
}

unsigned needPenalty(int A, int B)
{
    int x1, y1, x2, y2, x3, y3, result;

    x1 = dataBase[dataBase[A].previous_visit].x;
    y1 = dataBase[dataBase[A].previous_visit].y;
    x2 = dataBase[A].x;
    y2 = dataBase[A].y;
    x3 = dataBase[B].x;
    y3 = dataBase[B].y;

    /*calcutates for left turn*/
    result = (x1-x2)*(y3-y2)-(y1-y2)*(x3-x2);

    if(result < 0) return 1;
    if(result > 0) return 0;

    /*calculates for same direction*/
    result = (x1-x2)*(x3-x2)+(y1-y2)*(y3-y2);

    if(result < 0) return 0;
    return 1;
}

void visit(int A)
{
    int B;
    unsigned temp;

    if(A == endCity)
    {
        endVisited = 1;
        answer = cityTree[0].weight;
        return;
    }

    for(B = 1; B < cityAmount; B++)
    {
        if(roadTable[A][B] != -1)
        {
            temp = cityTree_getWeight(A) + (unsigned)roadTable[A][B] + (unsigned)dataBase[A].roads_incoming * needPenalty(A, B) * penalty;

            if(cityTree_getWeight(B) > temp)
            {
                cityTree_set(B, temp);
                dataBase[B].previous_visit = (short)A;
            }
        }
    }

    roadTable[dataBase[A].previous_visit][A] = -1;
    dataBase[A].visits_left--;

    if(dataBase[A].visits_left == 0)
    {
        cityTree_set(A, FULLYVISITED);
        for(B = 1; B < cityAmount; B++)
            roadTable[B][A] = -1;
    }
    else
        cityTree_set(A, NOTFULLYVISITED);

}

void dijkstra()
{
    int i = 0;
    while(cityTree[0].weight != NOTVISITED && endVisited == 0)
    {
        visit(cityTree[0].number);
        i++;
        /*
        for(i = 1; i < cityAmount; i++) printf("%u ", cityTree_getWeight(i));
        printf("\n");
        printf("vidit %d, roads left %d hi\n", cityTree[0].number, dataBase[cityTree[0].number].visits_left);
        printf("top element %u definetely is not %u\n", cityTree[0].weight, NOTVISITED);
        */
    }
}

int main()
{
    int i;
    readInputs();
    init();
    dijkstra();
    writeOutputs();

    free(cityTree);
    free(dataBase);
/*
    for(i = 0; i < cityAmount; i++)
    {
        free(roadTable[i]);
    }
    free(roadTable);
*/
    return 0;
}