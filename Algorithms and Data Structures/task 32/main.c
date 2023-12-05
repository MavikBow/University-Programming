#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int varCount, opCount;
int*varTree;
char exists;

void add(int A, int B)
{
	int rA = varTree[A], rB = varTree[B];
	while(rA >= 0)
	{
		A = rA;
		rA = varTree[A];
	}
	while(rB >= 0)
	{
		B = rB;
		rB = varTree[B];
	}

	if(A == B) return;

	if(rA >= rB)
	{
		varTree[B] += varTree[A];
		varTree[A] = B;
	}
	else
	{
		varTree[A] += varTree[B];
		varTree[B] = A;
	}
}

char relatives(int A, int B)
{
	int rA = varTree[A], rB = varTree[B];
	while(rA >= 0)
	{
		A = rA;
		rA = varTree[A];
	}
	while(rB >= 0)
	{
		B = rB;
		rB = varTree[B];
	}

	if(A == B) return 1;
	return 0;
}

int main()
{
	FILE*in,*out;
	char temp1[8],temp2[3],temp3[8];	
	int var1, var2, i;

	exists = 1;

	in = fopen("equal-not-equal.in", "r");
	fscanf(in, "%d %d", &varCount, &opCount);

	varTree = (int*)malloc((unsigned)varCount * sizeof(int));

	for(i = 0; i < varCount; i++)
		varTree[i] = -1;

	for(i = 0; i < opCount; i++)
	{
		fscanf(in, "%s %s %s", temp1, temp2, temp3);
		var1 = atoi(temp1 + 1) - 1;
		var2 = atoi(temp3 + 1) - 1;

		if(strcmp(temp2, "==") == 0)
			add(var1, var2);
	}

	fclose(in);

	/*======================================*/

	in = fopen("equal-not-equal.in", "r");
	fscanf(in, "%d %d", &varCount, &opCount);

	for(i = 0; i < opCount; i++)
	{
		fscanf(in, "%s %s %s", temp1, temp2, temp3);
		var1 = atoi(temp1 + 1) - 1;
		var2 = atoi(temp3 + 1) - 1;

		if(strcmp(temp2, "!=") == 0)
			if(relatives(var1, var2))
			{
				exists = 0;
				break;
			}
	}

	fclose(in);
	
	/*======================================*/

	out = fopen("equal-not-equal.out", "w");
	if(exists)
		fprintf(out, "Yes\n");
	else
		fprintf(out, "No\n");
	fclose(out);

	free(varTree);
	
	return 0;
}
