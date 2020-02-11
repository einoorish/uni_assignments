
#include <cstdlib>
#include "BigInt1.h"
#include <vector>
#include <string>
#include <iostream>
#include "math.h"

using namespace std;


int main()
{

	vector<int> a, b;
	int index_a = -10, index_b = -10;

	char input = '0';
	while (isdigit(input) || input == '.') {
		cin >> noskipws >> input;
		if (input == 10)
			break;
		else if (input != '.') {
			a.insert(a.begin(), (int)input - 48);
		}
		else
			index_a = a.size();
	}

	input = '0';
	while (isdigit(input) || input == '.') {
		cin >> noskipws >> input;
		if (input == 10)
			break;
		else if (input != '.') {
			b.insert(b.begin(), (int)input - 48);
		}
		else
			index_b = b.size();
	}
	int maxIndex = -10;

	if (index_a == index_b) {
		maxIndex = index_a;
	}

	if (index_a == -10) index_a = a.size();
	if (index_b == -10) index_b = b.size();
	//cout <<a.size()- index_a << " " <<b.size()- index_b << endl;
	//cout << index_a << " " << index_b << endl;

	if (a.size() - index_a != b.size() - index_b) {
		while (a.size() - index_a < b.size() - index_b) {
	
			if (a.size() == index_a) {
					maxIndex = a.size() - (b.size() - index_b);
					cout << maxIndex << endl;
				} else {
					maxIndex = index_a; 
				//	cout << "s1" << endl;

				}  

			if (b.size() == index_b) {
				maxIndex = b.size() - (a.size() - index_a);
			//	cout << "b" << endl;

			}
			else if (a.size() != index_a) {
				maxIndex = index_b;
				//cout << "b2" << endl;
			}
			a.insert(a.begin(), 0);

		}

	//	cout << maxIndex << endl;

		while (a.size() - index_a > b.size() - index_b) {
			b.insert(b.begin(), 0);
			if (b.size() - index_b == 0) {
				maxIndex = a.size() - (b.size() - index_b) - 1;
			}
			else {
				maxIndex = index_b;
			}

			if (a.size() - index_a == 0) {
				maxIndex = b.size() - (a.size() - index_a) - 1;
			}
			else {
				maxIndex = index_a;
			}
			
		}
	}
	else maxIndex = index_a;

	BigInt number1 = BigInt(a);
	BigInt number2 = BigInt(b);
	BigInt result;
	
//	cout << maxIndex<< endl;
//	cout << number1 << " " << number2 << endl;

	int operation;

	std::cout << "Оберіть операцію: " << endl << "1 - додавання" << endl << "2 - віднімання" << endl << "3 - множення" << endl << "4 - ділення" << endl;
	cin >> operation;
	std::cout << "-----------------------------------------\n";

	switch (operation) {
	case 1:
		result = number1 + number2;
		break;
	case 2:
		//if (number2.digits.at(number2.digits.size() - 1) == 0) number2.digits.erase(number2.digits.begin() + number2.digits.size() - 1);
		result = number1 - number2;
		cout << result.digits.size() << endl;
		break;
	case 3:
		result = number1 * number2;
		//maxIndex /= 2;
		break;
	case 4:
		while (number2.digits.at(number2.digits.size()-1) == 0) number2.digits.erase(number2.digits.begin()+ number2.digits.size() - 1);
		while (number1.digits.at(number1.digits.size() - 1) == 0) number1.digits.erase(number1.digits.begin() + number1.digits.size() - 1);
		//cout << number1 << " " << number2 << endl;
		result = number1 / number2;
		if (result.digits.at(result.digits.size() - 1) == -10) result.digits.erase(result.digits.begin() + result.digits.size() - 1);
		cout << result;
		return 0;
	}
	///*
	if (result.digits.size() > number1.digits.size()) maxIndex++;
	else if (result.digits.size() < number1.digits.size()) maxIndex--;

//	cout << result.digits.at(result.digits.size() - 1) << endl;

	if (maxIndex != -10) 
		result.digits.insert(result.digits.begin() +result.digits.size() -  maxIndex, -10);

	if (result.digits.at(result.digits.size()-1) != -10)
	{
		for (int i = result.digits.size() - 1; i > 0; i--) {
			if (result.digits.at(i) == -10) {
				cout << '.';
			}
			else cout << result.digits.at(i);
		}

		if(result.digits.at(0) != -10)
			cout << result.digits.at(0);
		
	}
	else {
			cout << 0 << '.';
			int r = result.digits.size();
			while (r < number1.digits.size()) {
				++r;
				cout << 0;
			}

			for (int i = result.digits.size()-2; i >= 0; i--) {
					cout << result.digits.at(i);
			}
	}//*/



	//cout << result;
}
