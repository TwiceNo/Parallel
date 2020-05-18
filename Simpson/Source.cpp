#include "Header.h"


float function(float x)
{
	return sin(3 * x) + 4 * cos(2 * x);
}

float simpson(float a, float b)
{
	return (b - a) / 6 * (function(a) + 4 * function((a + b) / 2) + function(b));
}

float get_approach(float a, float b, int n)
{
	float sector = (b - a) / n;
	float sum = 0;
	for (int i = 0; i < n; i++)
	{
		float x = a + i * sector;
		float y = x + sector;
		sum += simpson(x, y);
	}
	return sum;
}

float sequential(float a, float b, float e)
{
	int n = 1;
	float prev = 0, appr = get_approach(a, b, n);
	while (abs(appr - prev) >= e)
	{
		prev = appr; n *= 2;
		appr = get_approach(a, b, n);
	}
	return appr;
}


float parallel(float a, float b, float e)
{
	int n = 1;
	int thread = 4;
	float sector = (b - a) / thread;
	float prev = 0, appr = 0;
	#pragma omp parallel
	{
		float x = a + omp_get_thread_num() * sector;
		float y = x + sector;
		appr += simpson(x, y);
	}
	while (abs(appr - prev) >= e)
	{
		prev = appr; appr = 0; n *= 2;
		#pragma omp parallel
		{
			float x = a + omp_get_thread_num() * sector;
			float y = x + sector;
			appr += get_approach(x, y, n);
		}
	}
	return appr;
}