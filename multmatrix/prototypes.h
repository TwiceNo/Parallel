#pragma once
#include <iostream>
#include <omp.h>
using namespace std;

int** make_matrix(int);
int** multiply_seq(int**, int**, int);
int** block_striped(int**, int**, int);
int** chessboard_block(int**, int**, int);
void print(int**, int);
int** transpose(int**, int);
void check_sum(int**, int);