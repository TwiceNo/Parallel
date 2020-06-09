#pragma once
#include <iostream>
#include <ctime>
#include <omp.h>
using namespace std;

class List
{
public:
	int* list, * res; int n;

	List(int n)
	{
		this->n = n;
		res = new int[n];
		list = make_list();
		copy_list();
	}

	int* make_list();
	void copy_list();
	bool is_sorted(int* list);
	void print(int*);
	void swap(int&, int&);
	
	void quick_sort(int*, int, int);
	void shell(int*, int, int);
	void shell(int*, int, int, int, int);
	void bubble(int*, int, int);


	void sequential_bubble(int*);
	void sequential_shell(int*);
	void sequential_quick(int*);

	void parallel_bubble(int*);
	void parallel_shell(int*);
	void parallel_quick(int*);
};

