/* unbounded knapsack problem
 * with answer recontruction
 */

#include <stdio.h>
#define MAXN 100
#define MAXW 100

int F[MAXN][MAXW]; 
int P[MAXN][MAXW];
int w[MAXN];      
int p[MAXN];     
int ans[MAXN];  

int i, k, s;

int max(int a, int b) {
    return a > b ? a : b;
}

void findAns(int n, int W) {
	if (n == 0 || W <= 0)
		return;
	
	if (P[n][W] == 0)
		findAns(n-1,W);
	else
	{
		ans[n]++;
		findAns(n,W-w[n]);
	}
}

int main() {
    int n = 3;   
    int W = 10; 

    w[1] = 3; p[1] = 4;
    w[2] = 4; p[2] = 8;
    w[3] = 5; p[3] = 13;

	for (i = 0; i <= n; i++)
		ans[i] = 0;
    for (i = 0; i <= W; i++)
	{
        F[0][i] = 0;
        P[0][i] = 0;
	}
    for (i = 0; i <= n; i++)
	{
        F[i][0] = 0;
        P[i][0] = 0;
	}

    for (k = 1; k <= n; k++) {
        for (s = 1; s <= W; s++) {
            if (w[k] <= s)
                F[k][s] = max(max(F[k - 1][s], F[k - 1][s - w[k]] + p[k]), p[k] * (s / w[k]));
            else
                F[k][s] = F[k - 1][s];

			if (F[k][s] == F[k - 1][s])
				P[k][s] = 0;
			else
				P[k][s] = 1;
        }
    }

    findAns(n, W);

    printf("Maximum value: %d\n", F[n][W]);
    printf("x_i: ");
    for (i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    printf("\n");

	printf("the F matrix\n");
	for (k = 1; k <= n; k++)
	{
		for(s = 1; s <= W; s++)
			printf("%2d ", F[k][s]);
		printf("\n");
	}

	printf("the P matrix\n");
	for (k = 1; k <= n; k++)
	{
		for(s = 1; s <= W; s++)
			printf("%2d ", P[k][s]);
		printf("\n");
	}

    return 0;
}
