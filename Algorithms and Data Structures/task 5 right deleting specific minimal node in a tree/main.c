#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int target;

struct node
{
    int key;
    struct node* left;
    struct node* right;
    int height, sum;
};

typedef struct
{
    struct node* root;
    int length;
    int sum;
} Route;

Route origin = {.root = NULL, .length = INT_MAX, .sum = INT_MAX};

void adopt_root(struct node** root)
{
    origin.root = *root;
    origin.length = (*root)->left->height + (*root)->right->height + 2;
    origin.sum = (*root)->sum + (*root)->left->sum + (*root)->right->sum;
}

void further_inspect(struct node** root)
{
    if(origin.root == NULL)
    {
        adopt_root(&(*root));
    }
    else
    {
        if(origin.length > (*root)->left->height + (*root)->right->height + 2)
        {
            adopt_root(&(*root));
        }
        else if(origin.length == (*root)->left->height + (*root)->right->height + 2)
        {
            if(origin.sum > (*root)->sum + (*root)->left->sum + (*root)->right->sum)
            {
                adopt_root(&(*root));
            }
            else if(origin.sum == (*root)->sum + (*root)->left->sum + (*root)->right->sum)
            {
                if(origin.root->key > (*root)->key)
                {
                    adopt_root(&(*root));
                }
            }
        }
    }
}

struct node* createNode(int value)
{
    struct node* newNode = (struct node *) malloc(sizeof(struct node));

    newNode->key = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->sum = value;

    return newNode;
}

void addNode(struct node* root, int value)
{
    if(value == root->key)
    {
        return;
    }
    
    if(value < root->key)
    {
        if(root->left == NULL)
        {
            root->left = createNode(value);
            return;
        }
        else
        {
            addNode(root->left, value);
            return;
        }
    }
    else
    {
        if(root->right == NULL)
        {
            root->right = createNode(value);
            return;
        }
        else
        {
            addNode(root->right, value);
            return;
        }
    }

    return;
}

void inheritLeft(struct node** root)
{
    (*root)->height = (*root)->left->height + 1;
    (*root)->sum += (*root)->left->sum;
}
void inheritRight(struct node** root)
{
    (*root)->height = (*root)->right->height + 1;
    (*root)->sum += (*root)->right->sum;
}

void inspect(struct node** root)
{
    if(*root == NULL){
        return;
    }

    if((*root)->left == NULL && (*root)->right == NULL)
    {
        (*root)->height = 0;
        return;   
    }

    inspect(&(*root)->left);
    inspect(&(*root)->right);

    if((*root)->left != NULL && (*root)->right != NULL)
    {
        further_inspect(&(*root));

        if((*root)->left->height < (*root)->right->height)
        {
            inheritLeft(&(*root));
        }
        else if((*root)->left->height > (*root)->right->height)
        {
            inheritRight(&(*root));
        }
        else
        {
            if((*root)->left->sum < (*root)->right->sum)
            {
                inheritLeft(&(*root));
            }
            else
            {
                inheritRight(&(*root));
            }
        }
        return;
    }

    if((*root)->left != NULL)
    {
        inheritLeft(&(*root));
        return;
    }
    if((*root)->right != NULL)
    {
        inheritRight(&(*root));
        return;
    }
}

void memFree(struct node** root)
{
    if((*root)->left != NULL)
    {
        memFree(&(*root)->left);
    }

    if((*root)->right != NULL)
    {
        memFree(&(*root)->right);
    }

    free(*root);
    *root = NULL;
}

void straightLeft_fprintf(FILE* out, struct node* root)
{
    if(root != NULL)
    {
        fprintf(out, "%d\n", root->key);
        straightLeft_fprintf(out, root->left);
        straightLeft_fprintf(out, root->right);
    }
}

void readInputs(struct node** root)
{
    FILE *in = fopen("in.txt", "r");
    if (in == NULL)
    {
        printf("error opening input.txt\n");
        exit(1);
    }

    int root_value, leaf_value;

    /*fscanf(in, "%d\n\n", &target);*/
    fscanf(in, "%d\n", &root_value);

    *root = createNode(root_value);

    while(!feof(in))
    {
        fscanf(in, "%d\n", &leaf_value);
        addNode(*root, leaf_value);
    }

    fclose(in);
}

void writeOutputs(struct node* root)
{
    FILE* out = fopen("out.txt", "w");
    if (out == NULL)
    {
        printf("error opening output.txt\n");
        exit(1);
    }

    straightLeft_fprintf(out, root);

    fclose(out);
}

int leftmost_key(struct node* root)
{
    if(root->left != NULL)
    {
        return leftmost_key(root->left);
    }

    return root->key;
}

void passConnection(struct node** root, struct node** leaf)
{
    struct node* temp = *root;
    *root = *leaf;
    free(temp);
}

void straightLeft_search(struct node** root, int victim)
{
    if(*root == NULL){
        return;
    }

    if((*root)->key == victim)
    {
        if((*root)->left == NULL && (*root)->right == NULL)
        {
            // Delete the node

            free(*root);
            *root = NULL;
            return;
        }

        if((*root)->left != NULL && (*root)->right == NULL)
        {
            passConnection(&(*root), &(*root)->left);
            return;
        }

        if((*root)->left == NULL && (*root)->right != NULL)
        {
            passConnection(&(*root), &(*root)->right);
            return;
        }

        if((*root)->right != NULL)
        {
            int new_victim = leftmost_key((*root)->right); 
            (*root)->key = new_victim;
            straightLeft_search(&(*root)->right, new_victim);
            return;
        }

        return;
    }

    if((*root)->key > victim)
        straightLeft_search(&(*root)->left, victim);
    else
        straightLeft_search(&(*root)->right, victim);
}

struct node* goDown(struct node** root, int fall)
{
    if(fall == 0)
    {
        return *root;
    }

    if((*root)->left == NULL)
    {
        return goDown(&(*root)->right, fall - 1);
    }
    if((*root)->right == NULL)
    {
        return goDown(&(*root)->left, fall - 1);
    }

    if((*root)->right->height < (*root)->left->height)
    {
        return goDown(&(*root)->right, fall - 1);
    }
    if((*root)->right->height > (*root)->left->height)
    {
        return goDown(&(*root)->left, fall - 1);
    }

    if((*root)->right->sum < (*root)->left->sum)
    {
        return goDown(&(*root)->right, fall - 1);
    }
    if((*root)->right->sum > (*root)->left->sum)
    {
        return goDown(&(*root)->left, fall - 1);
    }
    
    return NULL;
}

struct node* findImposter()
{
    if((origin.length & 1) == 1)
    {
        return NULL;
    }

    int h1 = origin.root->left->height;
    int h2 = origin.root->right->height;
    int fall;

    if(h1 == h2)
    {
        return origin.root;
    }
    if(h1 < h2)
    {
        fall = (origin.length>>1) - h1 - 1;
        return goDown(&origin.root->right, fall - 1);
    }
    else
    {
        fall = (origin.length>>1) - h2 - 1;
        return goDown(&origin.root->left, fall - 1);
    }
}

int main()
{
    struct node* root, *imposter = NULL;
    readInputs(&root);
    inspect(&root);
    imposter = findImposter();
    if(imposter != NULL)
    {
        straightLeft_search(&root, imposter->key);
    }
    writeOutputs(root);
    memFree(&root);
    return 0;
}