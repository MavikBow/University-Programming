#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int lily_numder;

int* food_per_lily;
int food_total = 0;

int maxAB(int a, int b)
{
	return a > b ? a : b;
}

int main()
{

	scanf("%d", &lily_numder);
	food_per_lily = (int*)malloc((lily_numder + 1) * sizeof(int));

	int i, temp;

	for (i = 0; i < lily_numder; i++)
	{
		scanf("%d", &temp);
		food_per_lily[i] = temp;
	}

	// Special cases

	if (lily_numder == 2)
	{
		printf("%d\n", -1);
		free(food_per_lily);
		return 0;
	}

	if (lily_numder == 1)
	{
		printf("%d\n1\n", food_per_lily[0]);
		free(food_per_lily);
		return 0;
	}

	food_per_lily[lily_numder] = 0;
	food_per_lily[lily_numder - 2] = 0;

	for (i = lily_numder - 1 - 2; i >= 0; i--)
	{
		food_per_lily[i] += maxAB(food_per_lily[i + 2], food_per_lily[i + 3]);
	}

	food_total = food_per_lily[0];
	printf("%d\n", food_total);
	
	printf("%d", 1);
	for (i = 0; i < lily_numder - 1;)
	{
		if (food_per_lily[i + 2] >= food_per_lily[i + 3])
		{
			i += 2;
		}
		else
		{
			i += 3;
		}
		printf(" %d", i + 1);
	}

	free(food_per_lily);

	return 0;
}