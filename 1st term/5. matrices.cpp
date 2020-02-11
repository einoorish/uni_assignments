#include <iostream>
using namespace std;

int main()
{
	const int m = 5, n = 6;
	int k = 2;
	int matrix[m][n];

	//заповнення матриці
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = k;
			k += 2;
			//cout << matrix[i][j] << "\t ";
		}
	}

	int max = 0;
	int maxArr[n];

	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			if (max < matrix[i][j]) max = matrix[i][j];
		}
		maxArr[j] = max;
		max = 0;
	}


	int result = 0;
	for (int i = 0; i < n; i++) {
		result += maxArr[i];
	}

	cout << endl << result;
}

