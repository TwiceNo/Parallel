#include "Header.h"

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Количество переменных: ";
	int n; cin >> n;
	cout << "\n0. Ввод системы вручную." << endl;
	cout << "1. Сгенерировать систему." << endl;
	bool f; cin >> f;
	Matrix matrix(n, f);

	if (matrix.diagonally_dominant())
	{
		matrix.reduction();

		cout << "\nПоследовательный алгоритм:" << endl;
		float start_time = omp_get_wtime();
		matrix.sequential();
		float end_time = omp_get_wtime();
		matrix.print_result();
		cout << end_time - start_time << " секунд." << endl;

		system("pause");

		cout << "\nПараллельный алгоритм:" << endl;
		start_time = omp_get_wtime();
		matrix.parallel();
		end_time = omp_get_wtime();
		matrix.print_result();
		cout << end_time - start_time << " секунд." << endl;
	}
	else
		cout << "\nВ матрице нет диагонального преобладания. Алгоритм Якоби расходится." << endl;
	system("pause");
}