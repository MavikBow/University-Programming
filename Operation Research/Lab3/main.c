/* BFS algorithm to find if an undirected graph is connected.
 * The graph is given as a size number and a logical matrix 
 * with 1 or 0 to mean a connection or lack of thereof.
 * The input file is passed as a parameted to the binary.
 */

#include <stdio.h>
#include <stdlib.h>

#define VISITED 1
#define UNVISITED 2
#define MARKED 3

short size;
short** A;
short* node;
short* queue;
int q_head = 0;
int q_tail = 0;

int main(int argc, char* argv[])
{
    FILE *in;
    short i;
    short j;

	if(argc == 1)
	{
		printf("Input file was not specified.\n");
		return 1;
	}
    in = fopen(argv[1], "r");
	if(in == NULL)
	{
		printf("File %s not found.\n", argv[1]);
		return 1;
	}

    fscanf(in, "%hd", &size);

    A = malloc(sizeof(*A) * size);
	node = malloc(sizeof(*node) * size);
	queue = malloc(sizeof(*queue) * size);
    for(i = 0; i < size; i++)
    {
		A[i] = malloc(sizeof(*A[i]) * size); 
    }
 
    for(i = 0; i < size; i++)
    for(j = 0; j < size; j++)
    {
    	fscanf(in, "%hd", &A[i][j]);
    }

    fclose(in);

	/*----------------------------------*/

	queue[q_head] = 0;
	q_tail++;

	node[0] = MARKED;
	for(i = 1; i < size; i++)
		node[i] = UNVISITED;

	do
	{
		for(i = 0; i < size; i++)
		{
			if(A[i][queue[q_head]] == 1)
			if(node[i] == UNVISITED)
			{
				node[i] = MARKED;
				queue[q_tail] = i;
				q_tail++;
			}
		}

	node[q_head] = VISITED;
	q_head++;

	} while(q_head != q_tail);


	/* As VISITED is defined as 1,
	 * if every node is visited,
	 * their sum should be equal to the
	 * amount of nodes, which is the size
	 * of the A matrix
	 */

	for(i = 0, j = 0; i < size; j+=node[i], i++);

	if(j == size)
		printf("YES\n");
	else
		printf("NO\n");
			
	/*----------------------------------*/
    for(i = 0; i < size; i++)
    {
        free(A[i]);
    }
    free(A);
	free(node);
	free(queue);

    return 0;
}
