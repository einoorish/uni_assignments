#include <iostream>
#include <vector>
#include <string>

using namespace std;

int NSD(int n, int m){
	if (n < m) { int buf = n; n = m; m = buf; }
	for (int i = m; i >= 1; i--)
		if (n % i == 0 && m % i == 0) return i;
	return 1;
}

int NSK(int n, int m){
	return n * m / NSD(n, m);
}

void make_result_beautiful_again(int result_numerator, int result_denominator) {

	int remains = 0;
	int check_result = 0;
	//ціла частина
	while (check_result < result_numerator - result_denominator) {
		remains++;
		check_result += result_denominator;

	}result_numerator -= check_result;

	//скорочення
	int nsd = NSD(result_numerator, result_denominator);
	result_numerator /= nsd;
	result_denominator /= nsd;

	if (remains == 0) {
		if (result_numerator == result_denominator) cout << 1;
		else cout << result_numerator << "/" << result_denominator;
	}
	else if (result_numerator == 0)
		cout << remains;
	else if (result_numerator != result_denominator) {
		cout << remains << '+' << result_numerator << "/" << result_denominator;
	} else cout << remains + 1;
}

int main()
{
	char temp_input = '0';
	int numerator1, denominator1, numerator2, denominator2, result_numerator, result_denominator;
	size_t firstIndex, secondIndex;
	string input;
	char delimiter[] = {'+', '-', '*', ':'};

	////////////////////////////////////////////////      ВВІД       /////////////////////////////////////////////////// 
	cin >> input;

	firstIndex = input.find('/') + 1;
	numerator1 = stoi(input.substr(0, firstIndex));

	int i = 1;
	int operationIndex = input.find(delimiter[0]);
	while (operationIndex == std::string::npos) {
		operationIndex = input.find(delimiter[i]);
		i++;
	} i--;
	denominator1 = stoi(input.substr(firstIndex,operationIndex));

	input = input.substr(operationIndex+1);

	secondIndex = input.find('/') + 1;

	numerator2 = stoi(input.substr(0, secondIndex));
	denominator2 = stoi(input.substr(secondIndex, operationIndex));

	if (denominator1 == 0 || denominator2 == 0) {
		cout << "на нуль ділити не можна, розбійник";
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	switch (i) {
		case 0: {
			int remains = 0;
			result_denominator = NSK(denominator1, denominator2);
				numerator1 *= result_denominator / denominator1;
				numerator2 *= result_denominator / denominator2;
			result_numerator = numerator1 + numerator2;

			make_result_beautiful_again(result_numerator, result_denominator);

			break;
		}
		case 1: {
			int remains = 0;
			result_denominator = NSK(denominator1, denominator2);
				numerator1 *= result_denominator / denominator1;
				numerator2 *= result_denominator / denominator2;
			result_numerator = numerator1 - numerator2;

			make_result_beautiful_again(result_numerator, result_denominator);

			break;
		}
		case 2: {
			result_numerator = numerator1 * numerator2;
			if (result_numerator == 0) {
				cout << 0;
				break;
			}
			result_denominator = denominator1 * denominator2;
			
			make_result_beautiful_again(result_numerator, result_denominator);

			break;
		}

		case 3: {
			result_numerator = numerator1 * denominator2;
			result_denominator = numerator2 * denominator1;

			make_result_beautiful_again(result_numerator, result_denominator);

			break;
		}
	}


	return 0;

}
