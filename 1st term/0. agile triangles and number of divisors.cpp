#include "pch.h"
#include <iostream>
#include <cmath>

using namespace std;

void two();
void eight();

int main()
{

	two();
}

void two() {

	int a, b, c, max;
	double cos;

	cout << "a, b, c:" << endl;;
	cin >> a >> b >> c;

	max = a;

	if (max < b) max = b;
	if (max < c) max = c;

	if (max < a + b + c - max) {

		cout << "существует ";
	}
	else cout << "не существует " << endl;

	cos = (-2 * pow(max, 2) + pow(a, 2) + pow(b, 2) + pow(c, 2))*max / (2 * b*c*a);

	cout << cos << endl;

	if (cos != 0.5 && cos > 0) cout << "остроугольный";
	else cout << "не остроугольный :c";

}

void eight() {

	int counter;

	//cout << "2  ";

	for (int i = 2; i < 100; i++) {
		counter = 0;
		//i += 1;

		int j = i - 1;
		for (j; j > 1; j--) {
			if (i%j == 0) {
				counter++;
				break;
			}
		}

		if (counter == 0) {
			cout << i << "  ";
		}

	}
}

