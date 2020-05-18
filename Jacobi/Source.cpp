#include "Header.h"

Matrix::Matrix(int x, bool f)
{
	n = x; eps = 0.0001;

	matrix = new float* [n];
	result = new float[n];

	for (int i = 0; i < n; i++)
		matrix[i] = new float[n + 1];

	if (f)
	{
		generate(); 
		cout << "\n0. Не выводить полученную систему." << endl;
		cout << "1. Вывести." << endl; bool p; cin >> p;
		if (p) print_matrix();

	}
	else set();

	cout << "\nТочность по умолчанию: " << fixed << eps << endl;
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


float* Matrix::first_approach()
{
	float* a = new float[n];
	for (int i = 0; i < n; i++)
		a[i] = matrix[i][n];
	return a;
}


void Matrix::sequential()
{
	float* appr = first_approach();
	float* prev = new float[n];
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


bool Matrix::check_precision(float*& a, float*& b)
{
	bool f = 1;
	for (int i = 0; i < n; i++)
	{
		if (abs(b[i] - a[i]) >= eps) f = 0;
		a[i] = b[i]; b[i] = 0;
	}
	return f;
}


void Matrix::parallel()
{
	float* appr = first_approach();
	float* prev = new float[n];
	for (int i = 0; i < n; i++)
		prev[i] = 0;

	int set = n / 4;

	while (!check_precision(prev, appr))
	#pragma omp parallel
	{
		int thread = omp_get_thread_num();
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
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < n; i++)
	{
		float div = matrix[i][i];
		for (int j = 0; j <= n; j++)
			matrix[i][j] /= div;
	}
}


void Matrix::print_result()
{
	for (int i = 0; i < n; i++)
		cout << "X" << i << " = " << fixed << result[i] << endl;
}


void Matrix::print(float* a)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << "\t";
	cout << endl;
}


void Matrix::generate()
{
	srand(time(0));

	solution = new float[n];
	for (int i = 0; i < n; i++)
		solution[i] = -2 + rand() % 7;

	#pragma omp parallel for schedule(static)
	for (int i = 0; i < n; i++)
	{ 
		float sum = 0, right_part = 0;
		for (int j = 0; j < n; j++)
			if (i != j)
			{
				matrix[i][j] = -3 + rand() % 7;
				sum += abs(matrix[i][j]);
				right_part += matrix[i][j] * solution[j];
			}
		matrix[i][i] = sum + 1;
		right_part += matrix[i][i] * solution[i];
		matrix[i][n] = right_part;
	}
}


bool Matrix::diagonally_dominant()
{
	for (int i = 0; i < n; i++)
	{
		float sum = 0;
		for (int j = 0; j < n; j++)
			if (i != j) sum += abs(matrix[i][j]);
		if (sum > abs(matrix[i][i])) return false;
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


float Matrix::maximal_deviation()
{
	float deviation = 0;
	for (int i = 0; i < n; i++)
		if (abs(result[i] - solution[i]) > deviation)
			deviation = abs(result[i] - solution[i]);
	return deviation;
}