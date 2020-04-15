#pragma once
#include <iostream>
#include <ctime>
#include <omp.h>
#include <iomanip>
using namespace std;


class Matrix
{
	double** matrix;
	double* result;
	double eps;
	int n; 

public:
	Matrix(int, bool);
	~Matrix();

	void sequential();
	void parallel();

	void print_matrix();
	void print_result();
	bool diagonally_dominant();
	void reduction();

private:
	double* first_approach();
	bool check_precision(double*&, double*&);
	void generate();
	void set();
	void print(double*);
};