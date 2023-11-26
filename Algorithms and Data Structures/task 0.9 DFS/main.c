#include <stdio.h>
#include <stdlib.h>

char**table;
int size;
int*order, orderWriter, orderReader;
int*answer;
char*markedList;

void parr()
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%d", order[i] + 1);
    }
    printf("\n");
}

void readInputs()
{
    FILE *in;
    int i, j, temp;

    in = fopen("input.txt", "r");
    fscanf(in, "%d", &size);

    order = (int*)malloc(size * sizeof(int));
    answer = (int*)malloc(size * sizeof(int));
    markedList = (char*)calloc(size, sizeof(char));
    table = (char**)malloc(size * sizeof(char*));
    for(i = 0; i < size; i++)
    {
        table[i] = (char*)malloc(size * sizeof(char));
    }

    for(i = 0; i < size; i++)
    {
        order[i] = -1;
    }

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            fscanf(in, "%d", &temp);
            table[i][j] = (char)temp;
        }
    }

    fclose(in);
}

void writeOutputs()
{
    FILE *out;
    int i;
    out = fopen("output.txt", "w");
    
    for(i = 0; i < size; i++)
    {
        fprintf(out, "%d ", answer[i] + 1);
    }
    fprintf(out, "\n");

    fclose(out);

    free(order);
    free(answer);
    free(markedList);
    for(i = 0; i < size; i++)
    {
        free(table[i]);
    }
    free(table);
}

void visit(int i)
{
    int j;
    for(j = 0; j < size; j++)
    {
        if(table[i][j] == 1)
        {
            if(markedList[j] == 0)
            {
                order[orderWriter] = j;
		        orderWriter++;
		        markedList[j] = 1;
                visit(j);
            }
        }
    }
    markedList[i] = 1;
}

void load()
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(markedList[i] == 0)
        {
            markedList[i] = 1;
            order[orderWriter] = i;
	    orderWriter++;
            break;
        }
    }
}

void inspection()
{
	orderReader = 0;
	orderWriter = 0;
    for(; orderReader < size; orderReader++)
    {
        if(order[orderReader] == -1)
        {
            load();
        }

        visit(order[orderReader]);
	/*parr();*/
    }
}

void reorder()
{
	int i;
	for(i = 0; i < size; i++)
	{
		answer[order[i]] = i;
	}
}

int main()
{
    readInputs();
    inspection();
    reorder();
    writeOutputs();
    return 0;
}