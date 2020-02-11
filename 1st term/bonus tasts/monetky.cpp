#include <iostream>
using namespace std;


int main() {

	int n, m;
	int* mas, * mas2;
	int count = 0;
	bool flag = false;

	cin >> n >> m;
	mas = new int[m];
	mas2 = new int[m];

	for (int i = 0; i < m; i++) {
		cin >> mas[i];
		mas2[i] = mas[i] * 2;
	}

	for (int i = 0; i < m - 1; i++) {
		for (int j = i + 1; j < m; j++) {
			if (mas[i] > mas[j]) {
				swap(mas[i], mas[j]);
				swap(mas2[i], mas2[j]);
			}
		}
	}

	for (int i = 0; i < m; i++) {
		if (mas[i] == n) {
			cout << 1;
			exit(0);
		}
		if (mas2[i] == n) {
			cout << 2;
			exit(0);
		}
	}

	for (int i = 0; i < m - 1; i++) {
		if (mas[i] + mas[i + 1] == n) {
			cout << 2;
			exit(0);
		}
		if (mas2[i] + mas2[i + 1] == n) {
			cout << 4;
			exit(0);
		}
		if (mas[i] + mas[i + 1] > n) {
			flag = true;
		}
		if (mas2[i] + mas2[i + 1] > n) {
			flag = true;
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i == j) {
				continue;
			}
			if (mas[i] + mas2[j] == n) {
				cout << 3;
				exit(0);
			}
		}
	}

	if (flag) {
		cout << 0;
	}
	else {
		cout << -1;
	}

}
