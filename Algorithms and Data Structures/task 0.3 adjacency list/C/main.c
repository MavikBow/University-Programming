#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int i, h;
} Head;

typedef struct
{
    int B, next;
} Edge;

Head*edgeHead;
Edge*edgeList;
int nodeAmount, edgeAmount, edgeWriter;

void edgeList_addEdge(int A, int B)
{
    Edge temp;
    temp.B = B;
    temp.next = edgeHead[A].i;

    edgeList[edgeWriter] = temp;
    edgeHead[A].h++;
    edgeHead[A].i = edgeWriter++;
}

void readInputs()
{
    FILE *in;
    int i, temp1, temp2;

    in = fopen("input.txt", "r");
    fscanf(in, "%d %d", &nodeAmount, &edgeAmount);

    edgeList = (Edge*)malloc((unsigned)((edgeAmount << 1) + 1) * sizeof(Edge));
    edgeHead = (Head*)calloc((unsigned)nodeAmount, sizeof(Head));
    
    edgeWriter = 1;
    
    for(i = 0; i < edgeAmount; i++)
    {
        fscanf(in, "%d %d", &temp1, &temp2);

        temp1--;
        temp2--;

        edgeList_addEdge(temp1, temp2);
        edgeList_addEdge(temp2, temp1);
    }

    fclose(in);
}

void writeOutputs()
{
    FILE *out;
    int i, j;
    out = fopen("output.txt", "w");
    for(i = 0; i < nodeAmount; i++)
    {
        fprintf(out, "%d", edgeHead[i].h);
        for(j = edgeHead[i].i; j != 0; j = edgeList[j].next)
        {
            fprintf(out, " %d", edgeList[j].B + 1);
        }
        fprintf(out, "\n");
    }
    fclose(out);
}

int main()
{
    readInputs();
    writeOutputs();

    free(edgeList);
    free(edgeHead);

    return 0;
}