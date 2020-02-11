#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<int> add(vector<int> a, vector<int> b);
vector<int> substract(vector<int> a, vector<int> b);
vector<int> multiply(vector<int> a, vector<int> b);
vector<int> divide(vector<int> a, vector<int> b);
vector<int> findMax(vector<int> a, vector<int> b);
bool ifMax(vector<int> a, vector<int> b);

int main()
{
	vector<int> a, b, result;
	int operation;
	char input = '0';

	while (isdigit(input)) {
		cin >> noskipws >> input;
		if (input == 10) break;
		a.insert(a.begin(), (int)input - 48);
	}
	input = '0';
	while (isdigit(input)) {
		cin >> noskipws >> input;
		if (input == 10) break;
		b.insert(b.begin(), (int)input - 48);
	}


	cout << "Оберіть операцію: " << endl << "1 - додавання" << endl << "2 - віднімання" << endl << "3 - множення" << endl << "4 - ділення" << endl;
	cin >> operation;
	cout << "-----------------------------------------\n";

	switch (operation) {
		case 1:
			result = add(a, b);
			reverse(result.begin(), result.end());
			break;
		case 2: {
			result = findMax(a, b);
			//while (result.at(result.size() - 1) == 0) result.erase(result.begin() + result.size() - 1); //result.begin bc the erase method on std::vector is overloaded
			reverse(result.begin(), result.end());
			break;
		}
		case 3:result = multiply(a, b);
			reverse(result.begin(), result.end());
			
			break;
		case 4:
			result = divide(a, b);
			break;
		}

	for (vector<int>::iterator it = result.begin(); it != result.end(); ++it)
		cout << *it;
}

vector<int> findMax(vector<int> a, vector<int> b) {

	vector<int> result = { 0 };

	if (a.size() > b.size()) {
		return substract(a, b);
	}
	else if (a.size() < b.size()) {
		result = substract(b, a);
		result.at(result.size() - 1) = result.at(result.size() - 1) * (-1);
		return result;
	}
	else {
		for (int i = a.size()-1; i >= 0; i--) {
			if (a.at(i) > b.at(i)) {
				return substract(a, b);
			}
			else if (a.at(i) < b.at(i)) {
				result = substract(b, a);
				result.at(result.size() - 1) = result.at(result.size() - 1) * (-1);
				return result;
			}
		}
	}
	return result;
}

vector<int> add(vector<int> a, vector<int> b) {
	int remains = 0;
	vector<int> result, max;
	int x=a.size(), y=b.size(), min, sum;
	
	if (x <= y) {
		min = x;
		max = b;
	} else {
		min = y;
		max = a;
	}

	for (int i = 0; i < min;i++) {
		sum = a.at(i) + b.at(i);
		if (sum % 10 + remains < 10)
			result.push_back(sum % 10 + remains);
		else result.push_back((sum % 10 + remains) % 10);
		remains = (sum +remains) / 10;

	}

	for (int i = min; i < max.size(); i++) {
		
		result.push_back(max.at(i)%10+remains);
		remains = max.at(i) / 10;
	}

	return result;
}

vector<int> substract(vector<int> a, vector<int> b) {
	int remains = 0, sum;
	vector<int> result;
	
	for (int i = 0; i < b.size(); i++) {
		sum = a.at(i) - b.at(i) - remains;
		if (sum < 0) {
			result.push_back(sum + 10);
			remains = 1;
		}
		else {
			result.push_back(sum);
			remains = 0;
		}


	}
	for (int i = b.size(); i < a.size(); i++) {

		int sum = a.at(i) - remains;

		if (sum < 0) {
			remains = 1;
			result.push_back(sum + 10);
		}
		else {
			result.push_back(sum);
			remains = 0;
		}

	}

	while (result.at(result.size() - 1) == 0) {
		result.erase(result.begin() + result.size() - 1);
	}
	
	return result;
}

vector<int> multiply(vector<int> a, vector<int> b) {

	vector<int> result, mid;
	int remains=0, step = 0;

	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {

			int temp = a.at(i) * b.at(j);

			if (temp % 10 + remains < 10) {
				result.push_back(temp % 10 + remains);
			} else result.push_back((temp % 10 + remains)%10);

			remains = (temp+remains) / 10;
		}
		
		if (remains != 0)
			result.push_back(remains);

		for (int g = 0; g < step; g++) {
			result.insert(result.begin(), 0);
		}

		step++;
		mid = add(result,mid);
		result.clear();
		remains = 0;
	}
	return mid;
}


vector<int> divide(vector<int> a, vector<int> b) {
	vector<int> result, mid;

	for (int j = a.size() - 1; j >= a.size() - b.size(); j--) {
		mid.insert(mid.begin(), a.at(j));
	}
		
	int i = a.size() - b.size();
	while(ifMax(a,b) && i>0) {

		vector<int> counter = { 0 };
		if (ifMax(b, mid)) {
			i--;
			mid.insert(mid.begin(), a.at(i));
		}

		while (ifMax(mid, b)) {
			mid = substract(mid, b);
			counter.at(0) += 1;
		}

		result.push_back(counter.at(0));
		
	//	vector<int> temp = mid;
	//	while (temp.size() < a.size() -1) {
	//		temp.insert(temp.begin(), 0);
	//	} 
	
	}
	
	return result;

}

bool ifMax(vector<int> a, vector<int> b) {

	if (a.size() > b.size() && a.at(a.size() -1)!=0) {
		return true;
	}
	else if (a.size() < b.size()) {
		return false;
	}
	else {
		for (int j = a.size() - 1; j >= 0; j--) {
			if (a.at(j) > b.at(j)) {
				return true;
			}
			else if (a.at(j) < b.at(j)) {
				return false;
			}
		}
	}
	return true;
}
/*
vector<int> divide(vector<int> a, vector<int> b) {
	//трабл з ноліками
	int counter = 0;
	vector<int> result, mid;

	for (int i = a.size() - b.size(); i < a.size(); i++) {
		mid.insert(mid.begin(), a.at(i));
	}

	for (int i = b.size(); i >= 0; i--) {



		if (!ifMax(mid, b)) {
			mid.insert(mid.begin(), a.at(i));
		}

		while (ifMax(mid, b)) {
			mid = findMax(mid, b);
			counter++;
		}

		for (vector<int>::reverse_iterator it = mid.rbegin(); it != mid.rend(); ++it)
		{
			cout << *it;
		}
		cout << endl;
		//cout << counter;

		int g = mid.size() - 1;

		while (g >= 0 && mid.at(g) == 0)
		{
			mid.erase(mid.begin() + g);
			g--;
		}

		//result.insert(result.begin(), counter);
		counter = 0;
	}

	/*for (vector<int>::reverse_iterator it = result.rbegin(); it != result.rend(); ++it)
	{
		cout << *it;
	}*/
	/*return result;
}*/

