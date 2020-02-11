using namespace std;
#include <iostream>

void drabynka(int a, int b, int& count) {
	if (a == 1) {
		count++;
		return;
	}
	if (a == 2) {
		count++;
		return;
	}
	if (a > 0) {
		if (a < b) {
			count++;
		}
		int x = 0;
		int u = 0;
		for (int i = 0; ; i++) {
			u += i;
			if (u >= a) {
				break;
			}
			x++;
		}
		for (int i = x; i < a; i++) {
			if (i < b) {
				drabynka(a - i, i, count);
			}
		}
	}
}

int main()
{
	int count = 0;
	int n = 3;
	drabynka(n, (n + 1), count);
	cout << count;
}