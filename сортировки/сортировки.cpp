#include <iostream>
#include <omp.h>
#include <ctime>
#include <iomanip>
using namespace std;


void OddEvenSort(int* mas, int size)
{
	int upper_bound;
	if (size % 2 == 0)
		upper_bound = size / 2 - 1;
	else
		upper_bound = size / 2;
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
			for (int j = 0; j < size / 2; j++)
				if (mas[2 * j] > mas[2 * j + 1])
					swap(mas[2 * j], mas[2 * j + 1]);
				else
					for (int j = 0; j < upper_bound; j++)
						if (mas[2 * j + 1] > mas[2 * j + 2])
							swap(mas[2 * j + 1], mas[2 * j + 2]);
	}
}


void OddEvenSortParallel(int* mas, int size, int  th_num)
{
	int upper_bound;
	if (size % 2 == 0)
		upper_bound = size / 2 - 1;
	else
		upper_bound = size / 2;
#pragma omp parallel shared (mas) num_threads(th_num)
	{
		for (int i = 0; i < size; i++)
			if (i % 2 == 0)
#pragma omp critical (first)
			{
				for (int j = 0; j < size / 2; j++)
					if (mas[2 * j] > mas[2 * j + 1])
						swap(mas[2 * j], mas[2 * j + 1]);
			}
			else
#pragma omp critical (second)
			{
				for (int j = 0; j < upper_bound; j++)
					if (mas[2 * j + 1] > mas[2 * j + 2])
						swap(mas[2 * j + 1], mas[2 * j + 2]);
			}
	}
}


void ShellSort(int* mas, int size)
{
	int j, range = size / 2;
	while (range > 0)
	{
		for (int i = 0; i < size - range; i++)
		{
			j = i;
			while (j >= 0 && mas[j] > mas[j + range])
			{
				swap(mas[j], mas[j + range]);
				j--;
			}
		}
		range = range / 2;
	}
}


void ShellSortParallel(int* mas, int size, int th_num)
{
	int j, range = size / 2;
	while (range > 0)
	{
		int threadAmount = omp_get_num_threads();
		int threadRange = range / threadAmount;
		int threadCurrent = omp_get_thread_num();
		#pragma omp parallel shared (mas) num_threads(th_num)
		{
			if (threadCurrent < threadAmount - 1)
			#pragma omp critical
			{
				for (int i = threadRange * threadCurrent; i <= threadRange * (threadCurrent + 1); i++)
				{
					j = i;
					while (j >= 0 && mas[j] > mas[j + range])
					{
						swap(mas[j], mas[j + range]);
						j--;
					}
				}
			}
			else
			{
				#pragma omp critical
				{
					for (int i = threadRange * threadCurrent; i < size - range; i++)
					{
						j = i;
						while (j >= 0 && mas[j] > mas[j + range]) 
						{
							swap(mas[j], mas[j + range]);
							j--;
						}
					}
				}
			}
			range = range / 2;
		}
	}
}


void HoareSort(int* mas, int begin, int end)
{
	if (begin < end)
	{
		int supElem = mas[begin];
		int key = begin;
		for (int i = begin + 1; i < end; i++)
			if (mas[i] <= supElem)
			{
				key++;
				swap(mas[i], mas[key]);
			}
		swap(mas[begin], mas[key]);
		HoareSort(mas, begin, key);
		HoareSort(mas, key + 1, end);

	}
}


void HoareSortParallel(int* mas, int begin, int end, int th_num)
{
	if (begin < end)
	{
		int supElem = mas[begin];
		int key = begin;
		for (int i = begin + 1; i < end; i++)
			if (mas[i] <= supElem)
			{
				key++;
				swap(mas[i], mas[key]);
			}
		swap(mas[begin], mas[key]);
#pragma omp parallel sections num_threads (th_num)
		{
#pragma omp section
			{
				HoareSortParallel(mas, begin, key, th_num);
			}
#pragma omp section
			{
				HoareSortParallel(mas, key + 1, end, th_num);
			}
		}
	}
}


int* copy_list(int* list, int n)
{
	int* out = new int[n];
	for (int i = 0; i < n; i++)
		out[i] = list[i];
	return out;
}


bool sorted(int* list, int n)
{
	for (int i = 0; i < n - 1; i++)
		if (list[i] > list[i + 1])
			return false;
	return true;
}


void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	cout.precision(6);

	cout << "Длина: ";
	int n; cin >> n;

	int* list = new int[n];
	int* list_to_sort = new int[n];
	for (int i = 0; i < n; i++)
		list[i] = 0 + rand() % 10;

	double start;

	cout << "\nПоследовательные алгоритмы:\n";
	
	list_to_sort = copy_list(list, n);
	cout << "Пузырьковая сортировка: ";
	start = omp_get_wtime();
	OddEvenSort(list_to_sort, n);
	if (sorted(list_to_sort, n))
		cout << fixed << omp_get_wtime() - start << endl << endl;

	list_to_sort = copy_list(list, n);
	cout << "Сортировка Шелла: ";
	start = omp_get_wtime();
	ShellSort(list_to_sort, n);
	if (sorted(list_to_sort, n))
		cout << fixed << omp_get_wtime() - start << endl << endl;

	list_to_sort = copy_list(list, n);
	cout << "Быстрая сортировка: ";
	start = omp_get_wtime();
	HoareSort(list_to_sort, 0, n);
	if (sorted(list_to_sort, n))
		cout << fixed << omp_get_wtime() - start << endl << endl;

	cout << "\nПараллельные алгоритмы:\n\n";

	list_to_sort = copy_list(list, n);
	cout << "Пузырьковая сортировка: ";
	start = omp_get_wtime();
	OddEvenSortParallel(list_to_sort, n, 4);
	if (sorted(list_to_sort, n))
		cout << fixed << omp_get_wtime() - start << endl << endl;

	list_to_sort = copy_list(list, n);
	cout << "Сортировка Шелла: ";
	start = omp_get_wtime();
	ShellSortParallel(list_to_sort, n, 4);
	if (sorted(list_to_sort, n))
		cout << fixed << omp_get_wtime() - start << endl << endl;

	list_to_sort = copy_list(list, n);
	cout << "Быстрая сортировка: ";
	start = omp_get_wtime();
	HoareSortParallel(list_to_sort, 0, n, 4);
	if (sorted(list_to_sort, n))
		cout << fixed << omp_get_wtime() - start << endl << endl;
}
