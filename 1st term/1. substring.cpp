#include <iostream>
using namespace std;

int main()
{
	char fat[] = { 'f','a','t' };
	char input[30];
	int indexArr[10];
	int indexArrCurrentIndex = 0;

	cin.getline(input, 30);

	int inputSize =  strlen(input);

	for (int i = 0; i < inputSize; i++) {
		if (input[i] == fat[0]) {
			if (i < inputSize-1) {
				if (input[i + 1] == fat[1] && input[i + 2] == fat[2]) {
					indexArr[indexArrCurrentIndex] = i+1;
					indexArrCurrentIndex++;
					i += 2;
				}
			}
			else break;
		}
	}

	if (indexArrCurrentIndex == 0) cout << "NO";
	else {
		cout << "YES";
		for (int i = 0; i < indexArrCurrentIndex; i++) {
			cout << ", " << indexArr[i];
		}
		cout << ".";
	}

}


