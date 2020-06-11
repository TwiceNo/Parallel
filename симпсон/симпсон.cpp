#include <iostream>
#include <math.h>
#include <omp.h>
using namespace std;


double getFunction(double x)
{
    return pow(x, 2) * cos(x);
}


double simpson(double leftBorder, double rightBorder, int steps)
{
    double h = (rightBorder - leftBorder) / steps;
    double sumFunX1 = 0, sumFunX2 = 0;
    for (int i = 1; i < steps; i++) 
    {
        if (i % 2 != 0)
            sumFunX1 += getFunction(leftBorder + i * h); 
        else
            sumFunX2 += getFunction(leftBorder + (i + 1) * h); 
    }
    return h / 3 * (getFunction(leftBorder) + getFunction(rightBorder) + 4 * sumFunX1 + 2 * sumFunX2); 
}


double simpsonParallel(double leftBorder, double rightBorder, int steps, int th_num)
{
    double h = (rightBorder - leftBorder) / steps;
    double sum1 = 0, sum2 = 0;
#pragma omp parallel num_threads(th_num)
    {
        double sumFunX1 = 0, sumFunX2 = 0;
        int th_size = steps / th_num;
        int th_curr = omp_get_thread_num();
        for (int i = th_size * th_curr; i < th_size * th_curr + th_size; i++)
        {
            if (i % 2 != 0)
                sumFunX1 += getFunction(leftBorder + i * h);
            else
                sumFunX2 += getFunction(leftBorder + (i + 1) * h);
        }
        sum1 += sumFunX1;
        sum2 += sumFunX2;
    }
    return h / 3 * (getFunction(leftBorder) + getFunction(rightBorder) + 4 * sum1 + 2 * sum2);
}


int main()
{
    setlocale(LC_ALL, "rus");
    cout.precision(6);

    cout << "Введите границы интегрирования:" << endl;
    cout << "A = "; double a; cin >> a;
    cout << "B = "; double b; cin >> b;
    cout << "Количество отрезков интегрирования = ";
    int n; cin >> n;

    double start;

    cout << "\nПоследовательный алгоритм:" << endl << endl;
    start = omp_get_wtime();
    simpson(a, b, n);
    cout << "Время выполнения: " << omp_get_wtime() - start << " сек" << endl;

    cout << "\nПараллельный алгоритм:" << endl << endl;
    start = omp_get_wtime();
    simpsonParallel(a, b, n, 4);
    cout << "Время выполнения: " << omp_get_wtime() - start << " сек" << endl;
    
    system("pause");
}
