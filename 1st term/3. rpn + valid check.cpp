#include <iostream> 
#include <stack> 
#include <string>
#include<vector>
#include<sstream>
#include <map>

using namespace std;

bool isOperator(char b)
{
	return b == '+' || b == '*';

}

bool priority(char a, char b)
{
	if (b == '(')
	{
		return true;
	}
	if (b == '+')
	{
		return true;

	}
	if (a == '+')
	{
		return false;
	}

	return false;

}

void calculateAndCout(const string& expression)
{
	double l = 0, r = 0, res;
	stringstream expression_stream(expression);
	vector<double> temp; // тут лежатимуть циферки
	string token;

	while (expression_stream >> token) {
		if (isOperator(token[0]))
		{
			if (temp.size() < 2) {
				cout << "неправильний вираз" << endl;
				return;
			}

			r = temp.back();
			temp.pop_back();

			l = temp.back();
			temp.pop_back();

			switch (token[0]) {
			case '+': res = l + r; break;
			case '*': res = l * r; break;
			}

			temp.push_back(res); // результат на місці виразу
		}
		else {
			try {
				temp.push_back(stod(token));
			}
			catch (invalid_argument e) { }//зайвий оператор
		}

	}

	cout << temp[0];
}

int main()
{
	string input;

	cin >> input;

	string rpn_result = "";
	stack<char> s;
	int i, j = 0, k = 0;
	bool space = false;

	for (i = 0; i < input.size(); i++) {
		
		//якщо число
		if (input[i] != '(' && input[i] != ')' && isOperator(input[i]) == false) {
			j++;
			k++;
			if (j == 1)
				rpn_result += input[i];
			else if (k == 1)
				rpn_result = rpn_result + " " + input[i];
			else
				rpn_result = rpn_result + input[i];
		}
		else
			k = 0;

		//якщо оператор
		if (isOperator(input[i]) == true) {

			if (s.empty() || (!s.empty() && priority(input[i], s.top()))) {
				s.push(input[i]);
			}
			else {
				while (!s.empty() && priority(s.top(), input[i])) {

					rpn_result = rpn_result + " " + s.top();
					s.pop();
					s.push(input[i]);
				}
			}
		}

		//якщо дужки
		else if (input[i] == '(') {
				if (i == 0 || isOperator(input[i - 1]))
					s.push(input[i]);
				else {
					cout << "неправильний вираз1";
					return 0;
				}
		} else if (input[i] == ')') {
			if (i > 0 && !isOperator(input[i - 1])) {
				while (s.top() != '(') {
					rpn_result = rpn_result + " " + s.top();
					s.pop();
				}
				s.pop();
			} 
			else {
				cout << "неправильний вираз2";
				return 0;
			}
		} 

	}

	while (!s.empty()) {
		rpn_result = rpn_result + " " + s.top();
		s.pop();
	}

	calculateAndCout(rpn_result);
}