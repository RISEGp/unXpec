#include <stdio.h>
#include <math.h>
#include <string.h>
double data[6][4][6][2];
int main()
{
//	freopen("result.txt", "r", stdin);
//	freopen("finalresult.txt", "w", stdout);
	for (int k = 1; k <= 5; k++)
	{
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 5; j++)
			{
				scanf("%lf%lf", &data[k][i][j][0], &data[k][i][j][1]);
				data[0][i][j][0] += data[k][i][j][0] / 5;
				data[0][i][j][1] += data[k][i][j][1] / 5;
			}
		}
	}
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			printf("N_NUM = %d, LOADS_NUM = %d\n", i, j);
			printf("Average: %f, %f\n\n", data[0][i][j][0], data[0][i][j][1]);
		}
	}
	return 0;
}
