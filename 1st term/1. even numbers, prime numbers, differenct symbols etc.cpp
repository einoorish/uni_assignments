
#include "pch.h"
#include <iostream> 
#include <string>

using namespace std;

void differentSymbols();
void isEvenNumber();
void primeSum();
void evenDigitsSmth(); //на парних місцях стоять непарні цифри і навпаки

int main() {

	cout << "введіть число" << endl;
	//differentSymbols();
	//isEvenNumber();
	//primeSum();
	
	evenDigitsSmth(); // игх

	return 0;
}

void differentSymbols() {

	string inputStr; 
	bool hasDiffSymbols = true;

	cin >> inputStr;

	for (unsigned int i = 1; i < inputStr.length(); i++) {

		for (unsigned int j = 0; j < i; j++) {
			if (inputStr[i] == inputStr[j]) {
				hasDiffSymbols = false; 
				break;
			}
		}
	}

	cout << "------------------" << endl;
	if (hasDiffSymbols) {
		cout << "різні";
	} else cout << "є однакові";
}

void isEvenNumber() {

	int number;
	bool isEvenNumber = false;

	cin >> number;

	if (number % 2 == 0) isEvenNumber = true; 

	cout << "------------------" << endl;
	if (isEvenNumber) {
		cout << "парне";
	} else cout << "непарне";
}

void primeSum() {

	int number, sum = 0;
	bool sumIsPrime = true;

	cin >> number;

	while (number != 0) {
		sum += number % 10;
		number /= 10;
	}

	for (int i = 2; i <= sqrt(sum); i++)
	{
		if (sum % i == 0) {
			sumIsPrime = false;
			break;
		}
	}

	cout << "------------------" << endl;
	if (sumIsPrime) {
		cout << "проста сума";
	}
	else cout << "не дуже проста";
}

void evenDigitsSmth() {

	string number;
	cin >> number;

	bool oddNumber = true;
	
	for (unsigned int i = 0; i < number.length(); i++) {
		if (i % 2 != 0) {
			int temp = (int)number[i] - '0';
			if (temp % 2 == 0) {
				oddNumber = false;
				cout << "умова не виконується";
				break;
			}
		}
	}

	if (oddNumber)
		cout << "умова виконується";
	
	/*
	int number = stoi("2"),length = 0;
	bool numbersAreOdd = false;

	cin >> number;

	int temp = number;
	
	while (temp != 0) {
		length++;
		temp = temp / 10;
	}


	for (int i = 0; i < length; i++) {
		temp = number;

		for(int j = i; j > 0 ; j--){
			temp = temp / 10;
			cout << temp % 10 << endl;
		}
	}
	*/
}

