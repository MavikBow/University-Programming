#include <stdio.h>

int N; int K;
int up; int down;
unsigned long long C = 1;
unsigned long long down_C = 1;
const int MOD = 1e9 + 7;

unsigned long long binpow(unsigned long long x)
{
	unsigned long long res = 1;
	int pow = MOD - 2;

	while (pow > 0)
	{
		if(pow & 1)
		{
			res = res * x % MOD;
		}

		x = x * x % MOD;
		pow >>= 1;
	}

	return res;
}

int main()
{
	scanf("%d %d", &N, &K);

	if (K > N - K)
	{
		up = K + 1;
		down = N - K;
	}
	else
	{
		up = N - K + 1;
		down = K;
	}

	while (up <= N || down >= 1)
	{
		if (up <= N)
		{
			C = C * up % MOD;

			up++;
		}

		if (down >= 1)
		{
			down_C = down_C * down % MOD;

			down--;
		}
	}

	C = C * binpow(down_C) % MOD;

	printf("%llu\n", C);

	return 0;
}