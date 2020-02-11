#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;
class myUtils
{

public:  vector<string> cutStringByDelimiter(string string, char delimiter);
		 void coutVector(vector<string> vector);
		 string cutTimeFromDate(string date);
		 string vectorToString(vector<string> vec, string delimeter);
		 string stringToList(string data);
		 void rewriteFile(string filename, vector<string> data);
		 string dateInNumbersToDateText(string date);
		 void clearConsole();

		 string getDataByIndexFromDate(string dataString, int index);
		 string findStringInVector(string string, vector<std::string> vector);
		 vector<string> getAllFileData(string file);
};

