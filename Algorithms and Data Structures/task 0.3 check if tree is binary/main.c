#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long nodesTotal;
struct node* tree;

struct node
{
    long long value;
    
    long long upperEdge;
    long long lowerEdge;
};

struct node createNode(long long value, long long father, char side)
{
    struct node newNode = {.value = value};

    if(side == 'R')
    {
        newNode.upperEdge = tree[father].upperEdge;
        newNode.lowerEdge = tree[father].value;
    }
    else
    {
        newNode.lowerEdge = tree[father].lowerEdge;
        newNode.upperEdge = tree[father].value;
    }

    return newNode;
}

void readInputs()
{
    FILE *in = fopen("bst.in", "r");
    if (in == NULL)
    {
        printf("error opening bst.in\n");
        exit(1);
    }

    long long key;
    long long father;
    char side;

    fscanf(in, "%lld\n%lld\n", &nodesTotal, &key);

    tree = (struct node*) malloc((nodesTotal + 10) * sizeof(struct node));
    tree[0].value = key;
    tree[0].upperEdge = LONG_LONG_MAX;
    tree[0].lowerEdge = LONG_LONG_MIN;

    long long i;
    for(i = 1; i < nodesTotal; i++)
    {
        fscanf(in, "%lld %lld %c", &key, &father, &side);

        tree[i] = createNode(key, father - 1, side);
    }

    return;
}

void writeOutputs(int success)
{
    FILE* out = fopen("bst.out", "w");
    if (out == NULL)
    {
        printf("error opening bst.out\n");
        exit(1);
    }

    if(success != 0)
    {
        fprintf(out, "YES\n");
    }
    else
    {
        fprintf(out, "NO\n");
    }

    fclose(out); 
}

int belongs(struct node root)
{
    if(root.value >= root.lowerEdge && root.value < root.upperEdge)
    {
        return 1;
    }
    
    return 0;
}

int main()
{
    readInputs();

    int success = 1;
    long long i;
    for(i = 0; i < nodesTotal; i++)
    {
        success &= belongs(tree[i]);
    }
    
    writeOutputs(success);

    free(tree);

    return 0;
}