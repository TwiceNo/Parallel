#pragma once
#include <iostream>
#include <ctime>
#include <omp.h>
#include <iomanip>
using namespace std;


class Matrix
{
	float** matrix;
	float* result;
	float eps;
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
	float* first_approach();
	bool check_precision(float*&, float*&);
	void generate();
	void set();
	void print(float*);
};