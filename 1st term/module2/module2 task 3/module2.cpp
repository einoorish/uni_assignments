#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <vector>
#include <iterator>

using namespace std;


void swap(string* a, string* b)
{
	string temp = *a;
	*a = *b;
	*b = temp;
}

void bubble(vector<string> &array)
{
	for (int i = 0; i < array.size(); i+=2)
	{
		for (int j = 1; j < array.size() -2; j+=2)
		{
			if (stoi(array[j]) > stoi(array[j + 2])) {
				swap(&array[j], &array[j + 2]);
				swap(&array[j-1], &array[j + 1]);
			}
		}
	}
}

vector<string> stringToVector(string str) {

	istringstream iss(str);
	vector<string> data((istream_iterator<string>(iss)), istream_iterator<string>());

	int i = 2;
	while (i < data.size()-1) {
		string temp = data.at(i);
		data.at(i) = data.at(i+1);
		data.at(i+1) = temp;
		i += 4;
	}

	return data;
}

int main()
{
	string dataString;

	ifstream f("matches_in.txt");

	stringstream buffer;
	buffer << f.rdbuf();
	dataString = buffer.str();

	f.close();


	vector<string> data = stringToVector(dataString);

	//сумує очки команди
	int k = 0;
	while (k < data.size()-1) {
		int i = 2+k;
		while (i < data.size()-1) {
			if (data.at(k) == data.at(i)) {
				data.at(k + 1) = to_string((stoi(data.at(k + 1)) + stoi(data.at(i + 1))));
				data.erase(data.begin() + i, data.begin() + i + 2);
				i = 2+k;
			}
			i += 2;
		} k += 2;
	}

	bubble(data);
	
	ofstream fout("matches_out.txt");
	for (int i = 0; i < data.size(); i++) {
		fout << data.at(i);
		if (i % 2 != 0) fout << "\n"; else fout << " ";
	}
	fout.close();
	   	 
}