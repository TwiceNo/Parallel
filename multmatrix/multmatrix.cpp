#include "prototypes.h"


void main()
{
	cout << "Matrix dimension: ";
	int n; cin >> n;
	int** a = make_matrix(n);
	int** b = transpose(make_matrix(n), n);
	
	int** res = multiply_seq(a, b, n);
	check_sum(res, n);
	//print(res, n);

	res = block_striped(a, b, n);
	check_sum(res, n);
	//print(res, n);

	res = chessboard_block(a, b, n);
	check_sum(res, n);
	//print(res, n);
	
	system("pause");
}