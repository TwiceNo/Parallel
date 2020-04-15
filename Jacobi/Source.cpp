#include "Header.h"

Matrix::Matrix(int x, bool f)
{
	n = x; eps = 0.0001;

	matrix = new double* [n];
	result = new double[n];

	for (int i = 0; i < n; i++)
		matrix[i] = new double[n + 1];

	if (f)
	{
		generate(); 
		cout << "\n0. Не выводить полученную систему." << endl;
		cout << "1. Вывести." << endl; bool p; cin >> p;
		if (p) print_matrix();

	}
	else set();

	cout << "\nТочность по умолчанию: " << eps << endl;
	cout << "0. Оставить." << endl;
	cout << "1. Изменить." << endl;
	cin >> f; if (f)
	{
		cout << "\nТребуемая точность: ";
		cin >> eps;
	}
}


Matrix::~Matrix()
{
	delete matrix, result;
}


double* Matrix::first_approach()
{
	double* a = new double[n];
	for (int i = 0; i < n; i++)
		a[i] = matrix[i][n];
	return a;
}


void Matrix::sequential()
{
	double* appr = first_approach();
	double* prev = new double[n];
	for (int i = 0; i < n; i++)
		prev[i] = 0;

	while (!check_precision(prev, appr))
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= n; j++)
				if (i != j)
					if (j == n) appr[i] += matrix[i][j];
					else
						appr[i] -= matrix[i][j] * prev[j];
	result = prev;
}



bool Matrix::check_precision(double*& a, double*& b)
{
	bool f = 1;
	for (int i = 0; i < n; i++)
	{
		if (b[i] - a[i] >= eps) f = 0;
		a[i] = b[i]; b[i] = 0;
	}
	return f;
}


void Matrix::parallel()
{
	double* appr = first_approach();
	double* prev = new double[n];
	for (int i = 0; i < n; i++)
		prev[i] = 0;

	int set = n / 4;

	while (!check_precision(prev, appr))
	#pragma omp parallel
	{
		int thread = omp_get_thread_num();
		cout << thread << endl;
		for (int i = 0; i < set; i++)
			for (int j = 0; j <= n; j++)
				if ((thread * set + i) != j)
					if (j == n) appr[thread * set + i] += matrix[thread * set + i][j];
					else
						appr[thread * set + i] -= matrix[thread * set + i][j] * prev[j];
	}
	result = prev;
}

void Matrix::print_matrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (j == n) cout << "|\t";
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}



void Matrix::reduction()
{
	for (int i = 0; i < n; i++)
	{
		double div = matrix[i][i];
		for (int j = 0; j <= n; j++)
			matrix[i][j] /= div;
	}
}

void Matrix::print_result()
{
	for (int i = 0; i < n; i++)
		cout << "X" << i << " = " << setprecision(6) << result[i] << endl;
}


void Matrix::print(double* a)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << "\t";
	cout << endl;
}


void Matrix::generate()
{
	srand(time(0));
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < n; i++)
	{ 
		double sum = 0;
		for (int j = 0; j <= n; j++)
			if (i != j)
			{
				matrix[i][j] = 1;//0 + rand() % (51);
				if (j != n) sum += matrix[i][j];
			}
		matrix[i][i] = sum+1;
		//matrix[i][i] += 0 + rand() % (50);
	}
}


bool Matrix::diagonally_dominant()
{
	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		for (int j = 0; j < n; j++)
			if (i != j) sum += matrix[i][j];
		if (sum > matrix[i][i]) return false;
	}
	return true;
}


void Matrix::set()
{
	cout << "\nВведите коэффициенты:" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matrix[i][j];
	cout << "\nВведите правые части:" << endl;
	for (int i = 0; i < n; i++)
		cin >> matrix[i][n];
}
