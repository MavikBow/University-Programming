#include <stdio.h>
#include <stdlib.h>

int target;

struct node
{
    int key;
    struct node* left;
    struct node* right;
};

struct node* createNode(int value)
{
    struct node* newNode = (struct node *) malloc(sizeof(struct node));

    newNode->key = value;
    newNode->left = NULL;
    newNode->right = NULL;

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
    FILE *in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("error opening input.txt\n");
        exit(1);
    }

    int root_value, leaf_value;

    fscanf(in, "%d\n\n", &target);
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
    FILE* out = fopen("output.txt", "w");
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
    free(*root);
    *root = *leaf;
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

int main()
{
    struct node* root;
    readInputs(&root);
    straightLeft_search(&root, target);
    writeOutputs(root);
    memFree(&root);
    return 0;
}