#include "Header.h"

int* List::make_list()
{
	srand(time(0));
	int* list = new int[n];
	for (int i = 0; i < n; i++)
		list[i] = -20 + rand() % 41;
	return list;
}


void List::copy_list()
{
	for (int i = 0; i < n; i++)
		res[i] = list[i];
}


void List::swap(int& a, int& b)
{
	int t = a; a = b; b = t;
}


bool List::is_sorted(int* list)
{
	for (int i = 0; i < n - 1; i++)
		if (list[i] > list[i + 1]) return false;
	return true;
}


void List::print(int* list)
{
	for (int i = 0; i < n; i++)
		cout << list[i] << "\t";
	cout << endl;
}


void List::bubble(int* list, int a, int b)
{
	for (int i = a; i <= b; i++)
	{
		bool f = 1;
		for (int j = a + 1; j <= b; j++)
			if (list[j - 1] > list[j])
			{
				f = 0; swap(list[j - 1], list[j]);
			}
		if (f) break;
	}
}


void List::shell(int* list, int a, int b)
{
	for (int step = (b - a + 1) / 2; step >= 1; step--)
		for (int i = a; i <= b - step; i++)
			if (list[i] > list[i + step]) swap(list[i], list[i + step]);
}


void List::shell(int* list, int a, int b, int x, int y)
{
	for (int step = (b - a + 1 + y - x + 1) / 2; step >= 1; step--)
		for (int i = a; i <= y - step; i++)
		{
			if (i == b + 1) i = x;
			int j = i + step;
			if (j > b && j < x) j = x - 1 + j - b;
			if (list[i] > list[j]) swap(list[i], list[j]);
		}
}


void List::quick_sort(int* list, int left, int right)
{
	int l = left, r = right;
	int middle = list[(left + right) / 2];

	do {
		while (list[l] < middle) l++;
		while (list[r] > middle) r--;

		if (l <= r)
		{
			if (l < r)
				swap(list[l], list[r]);
			l++; r--;
		}
	} while (l <= r);

	if (l < right) quick_sort(list, l, right);
	if (left < r) quick_sort(list, left, r);
}


void List::sequential_bubble(int* list)
{
	bubble(list, 0, n - 1);
}


void List::sequential_shell(int* list)
{
	shell(list, 0, n - 1);
}


void List::sequential_quick(int* list)
{
	quick_sort(list, 0, n - 1);
}


void List::parallel_bubble(int* list)
{
	int max_threads = 4, i = 0;
	int section = n / max_threads;

	while (!is_sorted(list))
	{
		#pragma omp parallel
		{
			int thread = omp_get_thread_num();
			if (i % 2 == 0)
			{
				if (thread % 2 == 0)
					if (thread < max_threads - 1)
						bubble(list, thread * section, (thread + 2) * section - 1);
			}
			else
				if (thread % 2 == 1)
					if (thread < max_threads - 1)
						bubble(list, thread * section, (thread + 2) * section - 1);
		}
		i++;
	}
}


void List::parallel_shell(int* list)
{
	print(list);
	cout << endl;

	int max_threads = 4, i = 0;
	int section = n / max_threads;

	while (!is_sorted(list))
	{
		#pragma omp parallel
		{
			int thread = omp_get_thread_num();
			if (i == 0)
				if (thread < max_threads);
		}
		cout << i << endl;
		print(list);
		cout << endl;
		i++;
	}
}



void List::parallel_quick(int* list)
{
	int do_something;
}






