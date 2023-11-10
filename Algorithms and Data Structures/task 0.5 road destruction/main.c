#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int A, B;
    char isNuked;
} Road;

int countCity, countRoad, countQuake;
int* arrCity, *arrQuake;
Road* arrRoad;
char* answer;

int countIslands;

void connect(Road R)
{
	int rA = arrCity[R.A], rB = arrCity[R.B];
	while(rA > 0)
	{
		R.A = rA;
		rA = arrCity[R.A];
	}
	while(rB > 0)
	{
		R.B = rB;
		rB = arrCity[R.B];
	}

	if(R.A == R.B) return;

    countIslands--;

	if(rA >= rB)
	{
		arrCity[R.B] += arrCity[R.A];
		arrCity[R.A] = R.B;
	}
	else
	{
		arrCity[R.A] += arrCity[R.B];
		arrCity[R.B] = R.A;
	}
}


int main()
{
    FILE *in, *out;
    int i;

    in = fopen("input.txt", "r");
    fscanf(in, "%d%d%d", &countCity, &countRoad, &countQuake); 

    arrCity = (int*)malloc((countCity + 1) * sizeof(int));
    arrRoad = (Road*)malloc((countRoad + 1) * sizeof(Road));
    arrQuake = (int*)malloc((countQuake + 1) * sizeof(int));
    answer = (char*)malloc((countQuake + 1) * sizeof(char));

    countIslands = countCity;
    
    for(i = 1; i <= countCity; i++)
    {
        arrCity[i] = -1;
    }
    for(i = 1; i <= countRoad; i++)
    {
        fscanf(in,"%d%d", &arrRoad[i].A, &arrRoad[i].B);
        arrRoad[i].isNuked = 0;
    }
    for(i = 1; i <= countQuake; i++)
    {
        fscanf(in, "%d", &arrQuake[i]);
        arrRoad[arrQuake[i]].isNuked = 1;
    }

    fclose(in);

    for(i = 1; i <= countRoad; i++)
    {
        if(arrRoad[i].isNuked == 0)
        {
            connect(arrRoad[i]);
        }
    }
    for(i = countQuake; countIslands > 1; i--)
    {
        connect(arrRoad[arrQuake[i]]);
        answer[i - 1] = '0';
    }
    for(; i > 0; i--)
    {
        answer[i - 1] = '1';
    }
    
    answer[countQuake] = '\0';

    out = fopen("output.txt", "w");
    fprintf(out, "%s\n", answer);
    fclose(out);

    free(arrCity);
    free(arrRoad);
    free(arrQuake);
    free(answer);

    return 0;
}