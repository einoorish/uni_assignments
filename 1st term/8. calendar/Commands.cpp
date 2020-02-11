#include "Commands.h"
#include<string>
#include <iostream>;
#include <cstdlib>

using namespace std;

string command;

string Commands::availableCommands(string calledFrom)
{
	if (calledFrom == "main") return main_();
	else if (calledFrom == "calendar") return calendar_();
	else if (calledFrom == "search") return search_();
	else exit_();
	
}

void Commands::exit_() {
	exit(1);
}

string Commands::main_() {
	cout << "\nAvailable commands: calendar, exit\n";
	cin >> command;

	if (command == "calendar" || command == "exit") return command;
	else {
		cout << "This command is not allowed. Try again.\n";
		return main_();
	}
}

string Commands::calendar_() {
	cout << "\nAvailable commands: back, edit, search\n";
	cin >> command;

	if (command == "edit" || command == "search") return command;
	if (command == "back") return "main";
	else {
		cout << "This command is not allowed. Try again. ";
		return calendar_();
	}
}

string Commands::search_() {
	cout << "\nAvailable commands: back, search, edit\n";
	cin >> command;

	if (command == "search" || command == "edit") return command;
	else if (command == "back") return "calendar";
	else {
		cout << "This command is not allowed. Try again. ";
		return search_();
	}
}
