#include <iostream> 
#include <stack> 
#include <string>
#include<vector>
#include<sstream>
#include <map>

using namespace std;

bool isOperator(char b)
{
	return b == '+' || b == '-' || b == '*' || b == '/';
}

bool priority(char a, char b)
{
	if (b == '(')
		return true;
	else if (b == '+' || b == '-')
		return true;

	if (a == '+' || a == '-')
		return false;
	
	if (b == a)
		return true;

	return false;
}

void static addToMap(map<char, int>& valuesMap, string input) {
	//input: a=3
	int index = input.find('=');

	char key = input[0];
	int value = stoi(input.substr(2, input.length()-1));
	valuesMap.insert(pair<char, int>(key, value));
}

bool bracketsCheck(string input) {
	vector<char> brackets;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '(' || input[i] == ')') brackets.push_back(input[i]);
	} 

	if (brackets.size() == 1) return false;
	else if (brackets.size() == 0) return true;
	else {
		int i = brackets.size() - 1;

		while (i>0) {
			while (brackets[i] != '(')
				i--;


			if (i == brackets.size() - 1) return false; //if i+1 exists <-> brackets[i+1] == ')'
			else {
				brackets.erase(brackets.begin() + i, brackets.begin() + i + 2);
				i--;
			}
		} 
		return true;
	}
}

void rpn(string input, map<char, int> valuesMap); // input -> rpn expression, (!!) calls calculateAndOtputResult()

void calculateAndOtputResult(const string& expression); // calculates rpn expression and outputs the result, called from rpn()

int main()
{
	string input;
	map<char, int> valuesMap;
	
	cin >> input; 
	if (input.find("=") != string::npos) { // if input is of a = 1 type
		addToMap(valuesMap, input);
		
		while (true) {
			cin >> input;
			if (input.find("=") != string::npos) { // continue to read input
				addToMap(valuesMap, input);
			}
			else break;
		}
	}

	if (bracketsCheck(input))
		rpn(input, valuesMap);
	else cout << "неправильне використання дужок\n";
}


void calculateAndOtputResult(const string& expression)
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
				case '-': res = l - r; break;
				case '*': res = l * r; break;
				case '/': {
					if (r == 0) {
						cout << "на 0 ділити не можна, вибачай..."; return;
					}
					else res = l / r; break;
				}
			}

			temp.push_back(res); // результат на місці виразу
		}
		else {
			temp.push_back(stod(token));
		}

	}

	cout << temp[0] << endl;
}

void rpn(string input, map<char, int> valuesMap) {

	string rpn_result = "";
	stack<char> s;
	int i, j = 0, k = 0;

	for (i = 0; i < input.size(); i++) {
		//якщо змінна0
		if (isalpha(input[i])) {
			if (valuesMap.count(input[i]) == 1) {
				map<char, int>::iterator varIndex = valuesMap.find(input[i]);
				j++;
				if (j == 1)
					rpn_result = rpn_result + to_string(varIndex->second);
				else
					rpn_result = rpn_result + " " + to_string(varIndex->second);
			}
			else {
				cout << "невідома змінна " << input[i]; return;
			}
		}

		//якщо число
		else if (input[i] != '(' && input[i] != ')' && isOperator(input[i]) == false) {
			j++;
			k++;
			if (j == 1)
				rpn_result += input[i];
			else if (k == 1)
				rpn_result = rpn_result + " " + input[i];
			else
				rpn_result = rpn_result + input[i];
		}
		else {
			k = 0;
		}

		//якщо дужки
		if (input[i] == '(') {
			if (i == 0 || isOperator(input[i - 1]) || input[i - 1]=='(')
				s.push(input[i]);
			else { cout << "неправильне використання дужок\n"; return; }
		}
		if (input[i] == ')') {
			while (s.top() != '(') {
				rpn_result = rpn_result + " " + s.top();
				s.pop();
			}
			s.pop();
		}

		//якщо оператор
		if (isOperator(input[i]) == true) {

			if (s.empty() || (!s.empty() && priority(input[i], s.top()))) {
				s.push(input[i]);
			}
			else {
				while (!s.empty() && priority(s.top(), input[i])) {

					rpn_result = rpn_result + " " + s.top();
					s.pop();
				}
				s.push(input[i]);
			}
		}
	}

	while (!s.empty()) {
		rpn_result = rpn_result + " " + s.top();
		s.pop();
	}

	cout << rpn_result << endl << endl;
	calculateAndOtputResult(rpn_result);
}
