#include <string>
#include <iostream>

using namespace std;

bool result = false;
int i = 0;

bool fitsTemplate(string &temp, string &word) {
		while ( i < temp.length()) {
				if (temp.at(i) != word.at(i) && temp.at(i) != '?') {
					if (temp.at(i) == '*' && i < temp.length() - 1) {
						temp = temp.substr(i + 1);
						while (i < word.length()) {
							if (word.length() > temp.length())

							word = word.substr(i);
							i = 0;
							result = fitsTemplate(temp, word);
						}return result;
					}
					else {
						word.erase(i, i + 1);
						if (word.length() < temp.length())
						temp.erase(0, 1);
						return false;
					}
				}
				else {
					result = true;
				}
					i++;
		}
		return true;
}

int main()
{

	string _template = "A??**R", word="ABXFFR";

	cout << fitsTemplate(_template, word);


}
