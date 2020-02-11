#include "myUtils.h"

void myUtils::coutVector(vector<string> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector.at(i) << endl;
	}
}

vector<string> myUtils::cutStringByDelimiter(string string, char delimiter) {
	vector<std::string> result;
	size_t pos = 0;

	while (string.substr(pos).find(delimiter) != string::npos)
	{
		result.push_back(string.substr(pos, string.substr(pos).find(delimiter)));
		pos += string.substr(pos).find(delimiter) + 1;
	}

	result.push_back(string.substr(pos));
	return result;
}

string myUtils::cutTimeFromDate(string date) {
	//Thu Nov 14 15:53:20 2019 - > Thu Nov 14 2019
	return date.erase(date.length() - 5 - 10, 9);
}

string myUtils::vectorToString(vector<string> vec, string delimeter) {

	if (!vec.empty())
	{
		std::stringstream ss;
		auto it =vec.cbegin();
		while (true)
		{
			ss << *it++;
			if (it != vec.cend())
				ss << delimeter;
			else
				return ss.str();
		}
	}
}

string myUtils::stringToList(string data) {

	vector<string> vec = cutStringByDelimiter(data, '|');
	if (vec.size()>1) {
		vec.erase(vec.begin() + 0, vec.begin() + 1);
		return vectorToString(vec, "\n");
	} return vec.at(0);
}

void myUtils::rewriteFile(string filename, vector<string> data) {

	ofstream file (filename + ".txt", ios::out | ios::trunc);
	file << vectorToString(data, "\n");
	file.close(); 
}

string myUtils::dateInNumbersToDateText(string numbers) {
	//14/11/2019 - > Nov 14 2019
	vector<string> data = cutStringByDelimiter(numbers,'/');
	string month;
	switch (stoi(data.at(1))) {
		case 1: month = "Jan"; break;
		case 2: month = "Feb"; break;
		case 3: month = "Mar"; break;
		case 4: month = "Apr"; break;
		case 5: month = "May"; break;
		case 6: month = "Jun"; break;
		case 7: month = "Jul"; break;
		case 8: month = "Aug"; break;
		case 9: month = "Sep"; break;
		case 10: month = "Oct"; break;
		case 11: month = "Nov"; break;
		case 12: month = "Dec"; break;
	}
	return month + ' ' + data.at(0) + ' ' + data.at(2);
}


void  myUtils::clearConsole() {
	cout << "\x1B[2J\x1B[H"; // clears the console;
	//CursorPosition.Y = 0;
	//SetConsoleCursorPosition(console, CursorPosition);
}


string myUtils::getDataByIndexFromDate(string dataString, int index) {
	return cutStringByDelimiter(dataString, '|').at(index);
}

string  myUtils::findStringInVector(string string, vector<std::string> vector) {
	for (int i = 0; i < vector.size(); i++) {
		if (strstr(vector.at(i).c_str(), string.c_str()))
			return vector.at(i);
	} return "no plans for this date";
}

vector<string> myUtils::getAllFileData(string file) {
	ifstream filedata(file);
	string dataString;

	stringstream buffer;
	buffer << filedata.rdbuf();
	dataString = buffer.str();

	filedata.close();


	return cutStringByDelimiter(dataString, '\n');
}
