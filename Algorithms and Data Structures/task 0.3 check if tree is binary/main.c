#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int nodesTotal;
struct node* tree;

struct node
{
    int key;
    int left;
    int right;
};

struct node createNode(int value, int father, char side, int pointer)
{
    struct node newNode = {.key = value, .left = -1, .right = -1};

    if(side == 'R')
    {
        tree[father].right = pointer;
    }
    else
    {
        tree[father].left = pointer;
    }

    return newNode;
}

int isSearchable(int lowerEdge, int upperEdge, int address)
{
    int middleEdge = tree[address].key; 
    int result = 1;

    if(tree[address].key >= lowerEdge && tree[address].key < upperEdge)
    {
        result = 1;
    }
    else
    {
        result = 0;
        return 0;
    }

    if(tree[address].left != -1)
    {
        result &= isSearchable(lowerEdge, middleEdge, tree[address].left);
    }

    if(result == 0)
    {
        return 0;
    }

    if(tree[address].right != -1)
    {
        result &= isSearchable(middleEdge, upperEdge, tree[address].right);
    }

    return result;
}

void readInputs()
{
    FILE *in = fopen("bst.in", "r");
    if (in == NULL)
    {
        printf("error opening bst.in\n");
        exit(1);
    }

    int key, father;
    char side;

    fscanf(in, "%d\n%d\n", &nodesTotal, &key);

    tree = (struct node*) malloc(nodesTotal * sizeof(struct node));
    tree[0].key = key;
    tree[0].right = -1;
    tree[0].left = -1;

    int i;
    for(i = 1; i < nodesTotal; i++)
    {
        fscanf(in, "%d %d %c", &key, &father, &side);

        tree[i] = createNode(key, father - 1, side, i);
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

void leftprintf(int a)
{
    printf("%d\n", tree[a].key);

    if(tree[a].left != -1)
    {
        leftprintf(tree[a].left);
    }
    if(tree[a].right != -1)
    {
        leftprintf(tree[a].right);
    }

    return;
}

int main()
{
    readInputs();

    //leftprintf(0);

    int success = isSearchable(INT_MIN, INT_MAX, 0);
    
    writeOutputs(success);

    free(tree);

    return 0;
}