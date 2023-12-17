/*executes the BFS algorithm to check if the road exists.
if positive, executes Dijkstra's algorithm, but instead of G graph it does it for L(G) graph;

The datastructes: 
    cityDataBase,
    roadTable,
    roadTree;
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    short x, y;
    unsigned short roads_incoming;
} CityData;

typedef struct
{
    unsigned int actual_weight;
    unsigned short A, B;
} RoadData;

typedef struct
{
    short weight;
    unsigned short number;
} roadTableData;


CityData*cityDataBase;
roadTableData**roadTable;
RoadData*roadTree;

unsigned int cityAmount, roadAmount, penalty, treeSize;
unsigned CITYSHIFT;
unsigned short startCity, endCity;

const unsigned VISITED = UINT_MAX;
const unsigned UNVISITED = UINT_MAX - 1;

unsigned answer;
char endVisited = 0;

void roadTree_create()
{
    unsigned short i, j, k;
    CITYSHIFT = (treeSize>>1) - 1;

    for(i = 0, k = 0; i < cityAmount; i++)
        for(j = 0; j < cityAmount; j++)
            if(roadTable[i][j].weight >= 0)
            {
                roadTable[i][j].number = k;

                roadTree[k + CITYSHIFT].A = i;
                roadTree[k + CITYSHIFT].B = j;

                k++;
            }

    for(i = 0; i < treeSize; i++)
        roadTree[i].actual_weight = UNVISITED;
}
void roadTree_set(int i, unsigned weight)
{
    int j = i + (int)CITYSHIFT; 
    RoadData temp = roadTree[j];
    
    temp.actual_weight = weight;

    for(; j > 0; j = (j-1)>>1)
    {
        roadTree[j] = temp;

        if((j&1) == 0)
            temp = roadTree[j-1];
        else
            temp = roadTree[j+1];
    
        if(temp.actual_weight > roadTree[j].actual_weight)
        {
            temp = roadTree[j];
        }
    }

    roadTree[0] = temp;
}
unsigned roadTree_getWeight(unsigned i)
{
    return roadTree[i + CITYSHIFT].actual_weight;
}

unsigned step2(unsigned x)
{
    unsigned res = 1;
    while(res < x)
    {
        res <<= 1;
    }
    return res;
}

void readInputs()
{
    FILE *in;
    short temp1, temp2, temp3;
    unsigned i, j, tempRoad;

    in = fopen("input.txt", "r");
    fscanf(in, "%u %u %u", &cityAmount, &roadAmount, &penalty);

    cityAmount++;
    tempRoad = roadAmount;
    roadAmount <<= 1;
    roadAmount++;

    treeSize = step2(roadAmount) << 1;

    cityDataBase = (CityData*)calloc(cityAmount, sizeof(CityData));
    roadTree = (RoadData*)malloc(treeSize * sizeof(RoadData));
    roadTable = (roadTableData**)malloc(cityAmount * sizeof(roadTableData*));
    for(i = 0; i < cityAmount; i++) roadTable[i] = (roadTableData*)malloc(cityAmount * sizeof(roadTableData));

    for(i = 0; i < cityAmount; i++)
        for(j = 0; j < cityAmount; j++)
        {
            roadTable[i][j].weight = -1;
        }

    for(i = 1; i < cityAmount; i++)
    {
        fscanf(in, "%hd %hd", &temp1, &temp2);

        cityDataBase[i].x = temp1;
        cityDataBase[i].y = temp2;
    }
    
    for(i = 0; i < tempRoad; i++)
    {
        fscanf(in, "%hd %hd %hd", &temp1, &temp2, &temp3);

        roadTable[temp1][temp2].weight = temp3;
        roadTable[temp2][temp1].weight = temp3;

        cityDataBase[temp1].roads_incoming++;
        cityDataBase[temp2].roads_incoming++;
    }

    fscanf(in, "%hu %hu", &startCity, &endCity);
    
    fclose(in);
}

void init()
{
    cityDataBase[0].x = cityDataBase[startCity].x;
    cityDataBase[0].y = cityDataBase[startCity].y;
    cityDataBase[0].y--;

    roadTable[0][startCity].weight = 0;

    roadTree_create();
    roadTree_set(0, 0);
}

unsigned needPenalty(unsigned short A, unsigned short B, unsigned short C)
{
    int x1, y1, x2, y2, x3, y3, result;

    x1 = (int)cityDataBase[A].x;
    y1 = (int)cityDataBase[A].y;
    x2 = (int)cityDataBase[B].x;
    y2 = (int)cityDataBase[B].y;
    x3 = (int)cityDataBase[C].x;
    y3 = (int)cityDataBase[C].y;

    /*calcutates for left turn*/
    result = (x1-x2)*(y3-y2)-(y1-y2)*(x3-x2);

    if(result < 0) return 1;
    if(result > 0) return 0;

    /*calculates for same direction*/
    result = (x1-x2)*(x3-x2)+(y1-y2)*(y3-y2);

    if(result < 0) return 0;
    return 1;
}

void visit(RoadData road)
{
    unsigned C, temp;
    unsigned short number;

    if(road.B == endCity)
    {
        endVisited = 1;
        answer = road.actual_weight;
        return;
    }

    for(C = 0; C < cityAmount; C++)
    {
        if(roadTable[road.B][C].weight >= 0)
        {
            temp = road.actual_weight + (unsigned)roadTable[road.B][C].weight + 
            cityDataBase[road.B].roads_incoming * needPenalty(road.A, road.B, (unsigned short)C) * penalty;
            number = roadTable[road.B][C].number;

            if(roadTree_getWeight(number) > temp)
                roadTree_set(number, temp);
        }
    }

    roadTable[road.A][road.B].weight = -2;
    roadTree_set(roadTable[road.A][road.B].number, VISITED);
}

void dijkstra()
{
    while(roadTree[0].actual_weight != UNVISITED && endVisited == 0)
        visit(roadTree[0]);  
}

void writeOutputs()
{
    FILE*out = fopen("output.txt", "w");
    if(endVisited)
        fprintf(out, "Yes\n%u\n", answer);
    else
        fprintf(out, "No\n");
    fclose(out);
}

void final()
{
    unsigned i;
    free(cityDataBase);
    free(roadTable);
    for(i = 0; i < cityAmount; i++) free(roadTable[i]);
    free(roadTable);
}

int main()
{
    readInputs();
    init();

    dijkstra();
    writeOutputs();

    final();
    return 0; 
}