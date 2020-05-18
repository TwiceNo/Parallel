#pragma once
#include <iostream>
#include <math.h>
#include <omp.h>
using namespace std;

float function(float x);
float simpson(float a, float b);
float get_approach(float a, float b, int n);

float sequential(float a, float b, float e);
float parallel(float a, float b, float e);

