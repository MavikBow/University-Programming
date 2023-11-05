#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arrSize;
int treeSize;
long long* tree;

typedef struct
{
    char name[20];
    int x, y;
} Request;

int requestSize;
Request request;

int step2(int x)
{
    int res = 1;
    while(res < x)
    {
        res <<= 1;
    }
    return res;
}

void buildTree()
{
    tree = (long long*)calloc(treeSize, sizeof(long long));

    int i;
    for(i = treeSize>>1; i < (treeSize>>1) + arrSize; i++)
    {
        scanf("%lld", &tree[i]);
    }

    for(i = (treeSize>>1) + arrSize - 1; i > 0; i--)
    {
        tree[i>>1] += tree[i];
    }
}

void readRequest()
{
    scanf("%s%d%d", request.name, &request.x, &request.y);
}

void add()
{
    int pos = request.x + (treeSize>>1);
    while(pos > 0)
    {
        tree[pos] += (long long)request.y;
        pos >>= 1;
    }
}

long long sum()
{
    long long res = 0;
    int L = request.x + (treeSize>>1);
    int R = request.y + (treeSize>>1);
    R--;

    while(L <= R)
    {
        if((L & 1) == 1) res += tree[L];
        if((R & 1) == 0) res += tree[R];
        L++;
        L >>= 1;
        R--;
        R >>= 1;
    }

    return res;
}

void processRequest()
{
    if(strcmp(request.name, "Add") == 0)
    {
        add();
    }

    if(strcmp(request.name, "FindSum") == 0)
    {
        printf("%lld\n", sum());
    }
}

int main()
{
    scanf("%d", &arrSize);

    treeSize = step2(arrSize)<<1;

    buildTree();

    int i;
    scanf("%d", &requestSize);
    for(i = 0; i < requestSize; i++)
    {
        readRequest();
        processRequest();
    }

    free(tree);
    return 0;
}