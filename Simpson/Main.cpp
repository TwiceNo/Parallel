#include "Header.h"

void main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Функция для интегрирования:" << endl;
	cout << "sin(3 * x )+ 4 * cos(2 * x)" << endl << endl;

	cout << "Введите пределы интегрирования:" << endl;
	cout << "A = "; double a; cin >> a;
	cout << "B = "; double b; cin >> b;

	cout << "\nНеобходимая точность: ";
	double eps; cin >> eps;

	cout << "\nЧисленное интегрирование по формуле Симпсона" << endl << endl;

	cout << "Последовательный алгоритм" << endl;
	cout << "Определенный интеграл: ";
	double start_time = omp_get_wtime();
	cout << sequential(a, b, eps) << endl;
	double end_time = omp_get_wtime() - start_time;
	cout << "Время выполнения: " << end_time << " сек" << endl << endl;

	cout << "Параллельный алгоритм" << endl;
	cout << "Определенный интеграл: ";
	start_time = omp_get_wtime();
	cout << parallel(a, b, eps) << endl;
	end_time = omp_get_wtime() - start_time;
	cout << "Время выполнения: " << end_time << " сек" << endl << endl;

	system("pause");
}