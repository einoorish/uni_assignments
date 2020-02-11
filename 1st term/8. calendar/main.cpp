#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>  
#include <string>      
#include <windows.h>
#include <vector>
#include "Commands.h"
#include "myUtils.h"

using namespace std;

static string name;
Commands commands;
myUtils util;

//HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//COORD CursorPosition;

void edit(string date);
void executeCommand(string command);
void calendar();
void search();
string check(string date);
string add(string date);
string _delete(string date);

string getDate() {     
	//CursorPosition.Y = 1;
	//SetConsoleCursorPosition(console, CursorPosition);

	time_t tt;
	time(&tt);

	#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
	return asctime(localtime(&tt));		
}

void mainMenu() {
	cout << util.cutTimeFromDate(getDate());
	util.clearConsole();
	cout << "Hello, " + name << endl;
	cout << "Today is " << getDate();
	
	executeCommand(commands.availableCommands("main"));

}

int main()
{	
	ifstream userdata("userdata.txt");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	if (userdata.peek() == ifstream::traits_type::eof()) { // if userdata file is empty <-> first launch
		cout << "Your name: ";
		cin >> name;
		ofstream userdata("userdata.txt");
		userdata << name;
	}
	else userdata >> name;
	userdata.close();

	mainMenu();
}


void calendar() {
	util.clearConsole();
	string date = util.cutTimeFromDate(getDate());
	date = date.erase(date.length() - 1, 1);
	cout << "-------------------------CALENDAR-------------------------\n\n";
	
	cout << "Meetings planned for today: \n";
	vector<string> meetings = util.getAllFileData("meetings.txt");
	string dayData = util.findStringInVector(date, meetings);
	dayData = util.stringToList(dayData);
	cout << dayData;

	cout << "\n\nTodo: \n";
	vector<string> todo = util.getAllFileData("todo.txt");
	dayData = util.findStringInVector(date, todo);
	dayData = util.stringToList(dayData);
	cout << dayData;

	cout << "\n\n--------------\n\n";

	string command = commands.availableCommands("calendar");
	if (command == "edit") edit(date);
	else executeCommand(command);
}

void edit(string date) {
	string filename, command, edited, availableCommands = "\nAvailable commands: back, add, delete, deleteAll";
	cout << "\nDo you want to edit meetings or todo? Write 'back' to return.\n";
	cin >> filename;
	if (filename == "back") calendar();

	vector<string> data = util.getAllFileData(filename+".txt");
	string dayData = util.findStringInVector(date, data);

	if (filename == "todo") availableCommands.append(", check");
	cout << availableCommands + "\n";
	cin >> command;

	if (dayData == "no plans for this date") dayData = date;
	if (command == "add") edited = add(dayData);
	else if (command == "delete") edited = _delete(dayData);
	else if (command == "deleteAll") edited = "";
	else if (command == "check" && filename == "todo") edited = check(dayData);
	else if (command == "back") edit(date);
	else {cout << "Wrong command, try again."; edit(dayData);}

	int index = distance(data.begin(), find(data.begin(), data.end(), dayData));
	if(dayData!=date)
		data.erase(data.begin() + index, data.begin() + index + 1);
	data.insert(data.begin() + index, edited);

	util.rewriteFile(filename, data);

	cout << "\nChanges have been applied.\n\n--------------\n";
	cout << "\nAvailable commands: add, delete, back\n";
	cin >> command;

	if (dayData == "no plans for this date") dayData = date;
	if (command == "add") edited = add(dayData);
	else if (command == "delete") edited = _delete(dayData);
	else edit(date);
}

string add(string data) {
	string newField;
	cout << "\nNew field: ";
	cin.ignore();
	getline(cin,newField);
	data.append(" | ☐ " +newField);
	return data;
}

string _delete(string data) {
	int index;
	cout << "\nField index you'd like to delete: ";
	cin >> index;
	vector<string> dataVector = util.cutStringByDelimiter(data, '|');
	dataVector.erase(dataVector.begin() + index, dataVector.begin()+ index+1);

	if (dataVector.size() == 1) return "";
	return util.vectorToString(dataVector,"|");
}

string check(string data) {
	int index, stringindex;
	cout << "\nField index you'd like to check/uncheck: ";
	cin >> index;
	vector<string> dataVector = util.cutStringByDelimiter(data, '|');
	string editedString = dataVector.at(index);
	if(editedString.find("☑")==string::npos)
		dataVector.at(index) = " ☑"+editedString.substr(4);
	else
		dataVector.at(index) = " ☐" + editedString.substr(4);

	return util.vectorToString(dataVector, "|");
}

void search() {
	util.clearConsole();
	cout << "------------------------SEARCH------------------------\n\n";
	string date, dayData;
	cout << "Enter date (dd/mm/yyyy): ";
	cin >> date;
	date = util.dateInNumbersToDateText(date);
	//cout << endl << date;

	cout << "\nMeetings planned for "+date+": \n";
	vector<string> meetings = util.getAllFileData("meetings.txt");
	dayData = util.findStringInVector(date, meetings);
	dayData = util.stringToList(dayData);
	cout << dayData;


	cout << "\n\nTodo for " + date + ": \n";
	vector<string> todo = util.getAllFileData("todo.txt");
	dayData = util.findStringInVector(date, todo);
	dayData = util.stringToList(dayData);
	cout << dayData;
	cout << "\n";

	 string command = commands.availableCommands("search");
	 if (command == "edit") edit(date);
		else executeCommand(command);
}

void executeCommand(string command) {
	if (command == "main") main();
	else if (command == "calendar") calendar();
	else if (command == "search") search();
}