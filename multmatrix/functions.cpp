#include "prototypes.h"

int** make_matrix(int n)
{
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
		for (int j = 0; j < n; j++)
			a[i][j] = 1;
	}
	return a;
}

int** transpose(int** a, int n)
{
	int** b = a;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
		{
			int temp = b[i][j];
			b[i][j] = b[j][i];
			b[j][i] = temp;
		}
	return b;
}

int** multiply_seq(int** a, int** b, int n)
{
	int** c = new int* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[n];
		for (int j = 0; j < n; j++)
			c[i][j] = 0;
	}

	double time = omp_get_wtime();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				c[i][j] += a[i][k] * b[j][k];
		
	time = omp_get_wtime() - time;
	cout << "\nSequential multiplying: " << time << " sec" << endl;

	return c;
}

int** block_striped(int** a, int** b, int n)
{
	int** c = new int* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[n];
		for (int j = 0; j < n; j++)
			c[i][j] = 0;
	}

	int threads_num = 4, num = n / threads_num;
	omp_set_num_threads(threads_num);
	double time = omp_get_wtime();
	#pragma omp parallel
	{
		int thread = omp_get_thread_num();
		for (int i = 0; i < num; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					c[i + thread * num][j] += a[i + thread * num][k] * b[j][k];
	}

	time = omp_get_wtime() - time;
	cout << "Block-striped: " << time << " sec" << endl;

	return c;
}

//int** block_striped(int** a, int** b, int n)
//{
//	int** c = new int* [n];
//	for (int i = 0; i < n; i++)
//	{
//		c[i] = new int[n];
//		for (int j = 0; j < n; j++)
//			c[i][j] = 0;
//	}
//	#pragma omp parallel for schedule(static)
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//			for (int k = 0; k < n; k++)
//				c[i][j] += a[i][k] * b[j][k];
//	return c;
//}

int** chessboard_block(int** a, int** b, int n)
{
	int** c = new int* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[n];
		for (int j = 0; j < n; j++)
			c[i][j] = 0;
	}
	int threads_num = 4, num = n / 2;
	omp_set_num_threads(threads_num);
	double time = omp_get_wtime();
	#pragma omp parallel
	{
		int thread = omp_get_thread_num();
		int x = 0, y = 0;
		if (thread > 1) x = num;
		if (thread % 2 == 1) y = num;
		for (int i = 0; i < num; i++)
			for (int j = 0; j < num; j++)
				for (int k = 0; k < num; k++)
				{
					c[i + x][j + y] += a[i + x][k] * b[j + y][k];
					c[i + x][j + y] += a[i + x][k + num] * b[j + y][k + num];
				}
	}

	time = omp_get_wtime() - time;
	cout << "Chessboard block: " << time << " sec" << endl;

	return c;
}

//int thread = omp_get_thread_num();
//int x = thread % num;
//int y = thread / num;
//for (int s = 0; s < num; s++)
//	for (int i = y * num; i < y + 1; i++)
//		for (int j = y * x; j < x + 1; j++)
//			for (int k = s * num; k < s + 1; k++)
//				c[i][j] += a[i][k] * b[j][k];

void check_sum(int** a, int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			sum += a[i][j];
	cout << "Checksum: " << sum << endl << endl;
}


void print(int** a, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "\t";
		cout << endl;
	}
}
