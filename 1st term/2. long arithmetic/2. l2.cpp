#include <iostream>
#include <vector>

using namespace std;

vector<int> add(vector<int> a, vector<int> b);
vector<int> substract(vector<int> a, vector<int> b);
vector<int> multiply(vector<int> a, vector<int> b);
vector<int> divide(vector<int> a, vector<int> b);

int main()
{
	
	vector<int> a = {3,4,5,6};
	vector<int> b = {1,2};
	vector<int> result;

	int operation;

	
	int input;
	while (cin >> noskipws >> input) {
		a.push_back(input);
	}
	a.push_back(cin.get());

	cout << "Оберіть операцію: "<< endl << "1 - додавання" << endl << "2 - віднімання" << endl << "3 - множення" << endl << "4 - ділення" << endl;
	cin >> operation;
	cout << "-----------------------------------------\n";


	switch (operation) {
		case 1:result = add(a, b); 
			break;
		case 2:result = substract(a, b);
			break;
		case 3:result = multiply(a, b);
			break;
		case 4:result = divide(a, b);
			break;
	}

	for (unsigned int i = 0; i < result.size(); ++i)
		cout << result[i];
}

	vector<int> add(vector<int> a, vector<int> b) {
		vector<int> result;
		bool remains = false;

		a.insert(a.begin(), 0);
		b.insert(b.begin(), 0);
	
		unsigned int i = a.size() - 1, j = b.size() - 1;

		while(i>0 && j >0){
				int sum = a.at(i) + b.at(j);

				if (remains) sum++;

				if (sum < 10) {
					result.insert(result.begin(), sum);
					remains = false;
				}
				else {
					result.insert(result.begin(), sum % 10);
					remains = true;
				}
				i--;
				j--;
		}

		if (j != i) {
			int difference = i - j;
			if (difference > 0) {
				for (unsigned int k = i; k > j; k--) {
					if (remains) {
						a.at(i) += 1;
						if (a.at(i) != 10)
							remains = false;
					}
					result.insert(result.begin(), a.at(k));
				}
			}
		}
		
		/*
		a.insert(a.begin(), 0);
		b.insert(b.begin(), 0);

		for (unsigned int i = b.size()-1; i > 0; i--) {

			//cout << b.at(i);
			int sum = 0;
			
			if (remains) sum++;

			if (sum < 10){
				result.insert(result.begin(), sum);
				remains = false;
			}
			else {
				result.insert(result.begin(), sum%10);
				remains = true;
			}
		}
	*/
		return result;
	}

	vector<int> substract(vector<int> a, vector<int> b) {
		vector<int> result;
		bool remains = false;

		a.insert(a.begin(), 0);
		b.insert(b.begin(), 0);

		unsigned int i = a.size() - 1, j = b.size() - 1;

		while (i > 0 && j > 0) {
			int sum = a.at(i) - b.at(j);
			if (a.at(i) < b.at(j)) {
				sum = 10 + a.at(i) + b.at(j);
				remains = true;
			}
			
			if (remains) {
				sum--;
			    remains = false;
			}

			result.insert(result.begin(), sum);
			i--;
			j--;
		}

		if (j != i) {
			int difference = i - j;
			if (difference > 0) {
				for (unsigned int k = i; k > j; k--) {
					if (remains) {
						a.at(i) -= 1;
						if (a.at(i) >= 0) {
							remains = false;
						}
						else a.at(i) = 9;
					}
					result.insert(result.begin(), a.at(k));
				}
			}
		}

		return result;
	}

	vector<int> multiply(vector<int> a, vector<int> b) {
		vector<int> result;
		int remains = 0;

		a.insert(a.begin(), 0);
		b.insert(b.begin(), 0);

		unsigned int i = a.size() - 1, j = b.size() - 1;

		for (int k = i; k > 0; k--) {
			vector<int> multResult;
			int tempMultResult = 0;
			for (int l = j; l > 0; l--) {
				tempMultResult = a.at(k) * b.at(l);
				
				if (remains != 0) {
					tempMultResult += remains;
				}

				if (tempMultResult < 10) {
					multResult.insert(multResult.begin(), tempMultResult);
					remains = 0;
				}
				else {
					multResult.insert(multResult.begin(), tempMultResult%10);
					remains = tempMultResult / 10;
				}

			//	multResult.push_back(tempMultResult);
				for (unsigned int s = multResult.size() - 1; s > 0; s--){
					result.insert(result.begin() + k-1, multResult.at(s) + remains);
				}
			}


			for(unsigned int s = result.size()-1; s > 0; s--)
				cout << result[s] << " " << endl;

		}
		return result;
	}

	vector<int> divide(vector<int> a, vector<int> b) {
		vector<int> result;
		return result;
	}