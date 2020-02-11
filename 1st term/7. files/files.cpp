#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <vector>

using namespace std;

void task1(string text); // порахувати кількість букв, символів та розділових знаків розділові знаки: .,-!?:;”()
void task2(string text); // порахувати кількість слів та речень
void task3(string text); // порахувати кількість слів, що починаються та закінчуються голосною / приголосною буквою
void task4(string text); // порахувати кількість слів(та вивести їх на екран), які містять подвоєні букви 
void task5(string text); // вивести найдовше / найкоротше слово та його довжину
void task6(string text); // перевірити на наявність у тексті слово, введене користувачем
void task7(string text); // замінити в тексті всі голосні букви символом *
void task8(string text); // видалити всі голосні букви
void task9(string text); // замінити всі літери k на рядок “math”

const char symbols[] = { '.',',','-','!','?', ':', ';','”','(',')' ,'"'};
const char voiceLetters[] = {65, 69, 73, 79, 85, 89};//(+32 for lowercase)

inline bool isLetter(char character) {
	return (character >= 65 && character <= 90) || (character >= 97 && character <= 122);
}

inline bool isVoiceLetter(char character) {
	return any_of(begin(voiceLetters), end(voiceLetters), [&](char c) {return c == character || c == character - 32; });
}

inline bool isSymbol(char character) {
	return any_of(begin(symbols), end(symbols), [&](char c) {return c == character; });
}

vector<string> static getWords(string text) {

	int i = 0;
	int characterNumbers = text.length();
	vector<string> words;

	for (i; i < text.length(); i++) {

		if (isSymbol(text[i])) { // erase punctuation
			text.erase(i, 1);
			characterNumbers--;
		}
	}

	i = 0;
	string word = "";
	while (i < text.length()) {
		// якщо перед " " була буква - > було слово

		if (text[i] == '\'' || (isLetter(text[i]) && text[i + 1] != ' ' && text[i + 1] != '\n' && !isSymbol(text[i + 1]))) {
			word += text[i];
		}
		else {
			if (isLetter(text[i])) {// last character of the word
				word += text[i];
				words.push_back(word);
			}

			word = "";
		}
		i++;
	}
	words.push_back(word);

	return words;
}

int main()
{
	string text;

	ifstream f("files_test.txt");

	stringstream buffer;
	buffer << f.rdbuf();
	text = buffer.str();

	f.close();

	task2(text);
	cout << "\n------\n";
	task5(text);
}

void task1(string text) {
	int symbolsAmount = 0, lettersAmount = 0;
	int charactersAmount = text.length();

	char character;
	for (int i = 0; i < charactersAmount; i++) {
		character = text[i];
		if (isLetter(character)) {
			lettersAmount++;
		}
		else if (isSymbol(character)) symbolsAmount++;
	}
	cout << "characters amount: " << charactersAmount << "\tsymbols amount: " << symbolsAmount << "\tletters amount: " << lettersAmount;
}

void task2(string text) {
	int wordsNumber=0, sentencesNumber = 0;

	vector<string> words = getWords(text);
	wordsNumber = words.size();

	for (int i = 0; i < text.size()-2; i++) {
		if(text.at(i) == '.' && text.at(i+1)!='.') //to avoid counting "..." as the end of the sentence
			sentencesNumber++;
	}
	sentencesNumber++;

	cout << "words: " << wordsNumber << "\tsentences: " << sentencesNumber;
}

void task3(string text) {
	int subtask = 1;
	string word;

	vector<string> words = getWords(text);

	cout << "\nслова, що починаються/закінчуються голосними: ";
	for (int i = 0; i < words.size(); i++) {
		word = words.at(i);
		if (isVoiceLetter(word[0]) && isVoiceLetter(word[word.length() - 1]))  
			cout << word << " ";
	}


	cout << "\nслова, що починаються/закінчуються приголосними: ";
	for (int i = 0; i < words.size(); i++) {word = words.at(i);
		word = words.at(i);
		if (!isVoiceLetter(word[0]) && !isVoiceLetter(word[word.length() - 1])) 
			cout << word <<" ";
	}

}

void task4(string text) {
	int counter = 0;
	vector<string> words = getWords(text);

	for (int i = 0; i < words.size(); i++) {
		for (int j = 0; j < words.at(i).length() - 1; j++) {
			if (words.at(i)[j] == words.at(i)[j + 1]) {
				cout << words.at(i) << " "; counter++;
			}
		}
	} cout << endl << counter;

}

void task5(string text) {
	static int maxLength = 0, minLength, maxLengthIndex;
	vector<string> words = getWords(text);
	
	for (int i = 0; i < words.size(); i++) {
		if (words.at(i).length() > maxLength) {
			maxLength = words.at(i).length(); 
			maxLengthIndex = i;
		}
	} cout << words.at(maxLengthIndex) << " має " << words.at(maxLengthIndex).length() << " букв\n";

	minLength = words.at(0).length();
	for (int i = 0; i < words.size(); i++) {
		if (words.at(i).length() < minLength) {
			minLength = words.at(i).length();
			maxLengthIndex = i;
		}
	} cout << words.at(maxLengthIndex) << " має " << words.at(maxLengthIndex).length() << " букв\n";
}

void task6(string text) {
	cout << "введіть слово\n";
	string word;
	cin >> word;
	if (text.find(word) != std::string::npos) {
		cout << "таке слово у тексті є" << '\n';
	} else cout << "такого слова у тексті немає" << '\n';
}

void task7(string text) {

	for (int i = 0; i < text.size(); i++) {
		if (isVoiceLetter(text[i])) text[i] = '*';
	}

	ofstream f("files_test.txt");
	f << text;
	f.close();
}

void task8(string text) {
	
	for (int i = 0; i < text.size(); i++) {
		if (isVoiceLetter(text[i])) text.erase(i,1);
	}

	ofstream f("files_test.txt");
	f << text;
	f.close();
}

void task9(string text) {

	for (int i = 0; i < text.size(); i++) {
		if ((text[i]) == 'k') {
			text.erase(i, 1);
			text.insert(i, "MATH");
		}
	}

	ofstream f("files_test.txt");
	f << text;
	f.close();
}