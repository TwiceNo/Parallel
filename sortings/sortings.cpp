#include "Header.h"

void main()
{
	cout.precision(8);
	cout << "Length" << endl;
	int n; cin >> n;
	List list(n);

	//cout << list.is_sorted(list.list) << endl;
	//list.print(list.list);

	////--------------------------------

	//double start, end;

	//cout << "Bubble" << endl;
	//start = omp_get_wtime();
	//list.sequential_bubble(list.res);
	//end = omp_get_wtime() - start;
	//cout << "Runtime: " << fixed << end << endl << endl;

	//list.copy_list();


	//cout << "Shell" << endl;
	//start = omp_get_wtime();
	//list.sequential_shell(list.res);
	//end = omp_get_wtime() - start;
	//cout << "Runtime: " << fixed << end << endl << endl;

	//list.copy_list();


	//cout << "Hoare" << endl;
	//start = omp_get_wtime();
	//list.sequential_quick(list.res);
	//end = omp_get_wtime() - start;
	//cout << "Runtime: " << fixed << end << endl << endl;

	//list.copy_list();

	//cout << "-------------------------------" << endl;

	//cout << "Bubble" << endl;
	//start = omp_get_wtime();
	//list.parallel_bubble(list.res);
	//end = omp_get_wtime() - start;
	//cout << list.is_sorted(list.res) << endl;
	//list.print(list.res);
	//cout << "Runtime: " << fixed << end << endl << endl;

	//list.copy_list();


	//cout << "Shell" << endl;
	//start = omp_get_wtime();
	//list.parallel_shell(list.res);
	//end = omp_get_wtime() - start;
	//cout << list.is_sorted(list.res) << endl;
	//list.print(list.res);
	//cout << "Runtime: " << fixed << end << endl << endl;

	//list.copy_list();

	system("pause");
}