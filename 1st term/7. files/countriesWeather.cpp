#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <iterator>
#include <vector>


using namespace std;

int max(const int a, const int b) { return b < a; }

int min(const int a, const int b) { return b > a; }

int compareTemp(vector<int> temperatures, int (*compareType)(int, int)) { // finds Max or Min temperature value
	int minOrMaxTemp = temperatures.at(0), minOrMaxIndex = 0;

	for (int i = 1; i < temperatures.size(); i++) {
		if ((*compareType)(temperatures.at(i), minOrMaxTemp)) {
			minOrMaxTemp = temperatures.at(i);
			minOrMaxIndex = i;
		}
	}
	return minOrMaxIndex;
}

void getData(string dataString);//writes string data into vectors

void coutAnalyzedData();
void userInteractionTasks();

static vector<string> countryNames;
static vector<int> winterTemp, autumnTemp, summerTemp, springTemp, allSeasonTemps;

int main()
{
	string dataString;
	ifstream f("countriesWeather.txt");

	stringstream buffer;
	buffer << f.rdbuf();
	dataString = buffer.str();

	f.close();

	int temperatureIndex = 0, i = 0;

	getData(dataString);
	coutAnalyzedData();

	cout << "-----------------------------------------------------------------------------------------------\n";
	cout << "-----------------------------------------------------------------------------------------------\n\n";
	
	string input;
	cin >> input;
	if (input == "clear") cout << "\x1B[2J\x1B[H";
	userInteractionTasks();
	
}

void getData(string dataString) {

	istringstream iss(dataString);
	vector<string> data((istream_iterator<string>(iss)), istream_iterator<string>());

	//[назва країни] [темп_влітку] [темп_восени] [темп_взимку] [темп_навесні]
	int i = 0;
	while (i < data.size() - 4) {
		countryNames.push_back(data.at(i)); i++;
		summerTemp.push_back(stoi(data.at(i))); i++;
		autumnTemp.push_back(stoi(data.at(i))); i++;
		winterTemp.push_back(stoi(data.at(i))); i++;
		springTemp.push_back(stoi(data.at(i))); i++;
	}
}

void task1(int temperatureIndex) {
	temperatureIndex = compareTemp(summerTemp, max);
	cout << "\nМаксимальна температура влітку - " << countryNames.at(temperatureIndex) << endl;
	temperatureIndex = compareTemp(summerTemp, min);
	cout << "Мінімальна температура влітку - " << countryNames.at(temperatureIndex) << endl;
	temperatureIndex = compareTemp(autumnTemp, max);
	cout << "\nМаксимальна температура восени - " << countryNames.at(temperatureIndex) << endl;
	temperatureIndex = compareTemp(autumnTemp, min);
	cout << "Мінімальна температура восени - " << countryNames.at(temperatureIndex) << endl;
	temperatureIndex = compareTemp(winterTemp, max);
	cout << "\nМаксимальна температура взимку - " << countryNames.at(temperatureIndex) << endl;
	temperatureIndex = compareTemp(winterTemp, min);
	cout << "Мінімальна температура взимку - " << countryNames.at(temperatureIndex) << endl;
	temperatureIndex = compareTemp(springTemp, max);
	cout << "\nМаксимальна температура весною - " << countryNames.at(temperatureIndex) << endl;
	temperatureIndex = compareTemp(springTemp, min);
	cout << "Мінімальна температура весною - " << countryNames.at(temperatureIndex) << endl;
}

void task2(int temperatureIndex) {
	allSeasonTemps.insert(allSeasonTemps.end(), summerTemp.begin(), summerTemp.end());
	allSeasonTemps.insert(allSeasonTemps.end(), autumnTemp.begin(), autumnTemp.end());
	allSeasonTemps.insert(allSeasonTemps.end(), winterTemp.begin(), winterTemp.end());
	allSeasonTemps.insert(allSeasonTemps.end(), springTemp.begin(), springTemp.end());

	temperatureIndex = compareTemp(allSeasonTemps, max);
	cout << "\nМаксимальна температура за рік - " << countryNames.at(temperatureIndex % countryNames.size());
	switch ((temperatureIndex % 4) - 1) {
		case 0: cout << " (літо, " << summerTemp.at(temperatureIndex % countryNames.size()); break;
		case 1: cout << " (осінь, " << autumnTemp.at(temperatureIndex % countryNames.size()); break;
		case -1:
		case 2: cout << " (зима, " << winterTemp.at(temperatureIndex % countryNames.size()); break;
		case 3: cout << " (весна, " << springTemp.at(temperatureIndex % countryNames.size()); break;
	} cout << ")" << endl;

	temperatureIndex = compareTemp(allSeasonTemps, min);
	cout << "Мінімальна температура за рік - " << countryNames.at(temperatureIndex % countryNames.size());
	switch ((temperatureIndex % 4) - 1) {
		case 0: cout << " (літо, " << summerTemp.at(temperatureIndex % countryNames.size()); break;
		case 1: cout << " (осінь, " << autumnTemp.at(temperatureIndex % countryNames.size()); break;
		case -1:
		case 2: cout << " (зима, " << winterTemp.at(temperatureIndex % countryNames.size()); break;
		case 3: cout << " (весна, " << springTemp.at(temperatureIndex % countryNames.size()); break;
	} cout << ")\n";

}

void task3(vector<int> seasonTemp) {
	vector<int> copySeasonTemp = seasonTemp;
	sort(copySeasonTemp.begin(), copySeasonTemp.end());
	copySeasonTemp.erase(unique(copySeasonTemp.begin(), copySeasonTemp.end()), copySeasonTemp.end());
	for (int i = 0; i < copySeasonTemp.size(); i++) {
		cout << copySeasonTemp.at(i) << " - ";
		for (int j = 0; j < seasonTemp.size(); j++)
			if (seasonTemp.at(j) == copySeasonTemp.at(i)) cout << countryNames.at(j% countryNames.size()) << "    ";
		cout << "\n";
	}cout << endl ;
}

static void coutAnalyzedData(){

	static int temperatureIndex;

	//1. назву країн(и) з максимальною/мінімальною температурою влітку/взимку/навесні/восени.
	task1(temperatureIndex);
	cout << "\n-----------------------------------------------------------------------------------------------\n";

	//2. назву країн(и) з max / min середньою температорою за всі сезони, найбільшу та найменшу температуру (серед всіх країн всіх сезонів), а також назву країни та сезон коли ця температура досяглась
	task2(temperatureIndex);
	cout << "\n-----------------------------------------------------------------------------------------------\n";

	//3. відсортований (за зростанням/спаданням) список країн за температурою влітку/взимку/навесні/восени/середньою за всі сезони
	cout << "літо \n";
	task3(summerTemp);

	cout << "осінь \n";
	task3(autumnTemp);

	cout << "зима \n";
	task3(winterTemp);

	cout << "весна \n";
	task3(springTemp);

	cout << "за всі сезони \n";
	task3(allSeasonTemps);
	cout << "-----------------------------------------------------------------------------------------------\n\n";

	//4. список країн, в яких влітку було більше 30oC 
	cout << "Країни, в яких влітку було більше 30oC: ";
	for (int i = 0; i < summerTemp.size(); i++ ){
		if (summerTemp.at(i) >= 30) cout << countryNames.at(i) << "    ";
	}

	//5. список країн, у яких взимку була від’ємна температура*/
	cout << "\n\nКраїни, у яких взимку була від’ємна температура: ";
	for (int i = 0; i < summerTemp.size(); i++) {
		if (winterTemp.at(i) < 0) cout << countryNames.at(i) << "    ";
	}


	cout << "\n\n-----------------------------------------------------------------------------------------------\n";


}


void userInteractionTasks() {
	string country;
	cout << "Введіть країну\n";
	cin >> country;

	int countryIndex;
	for (int i = 0; i < countryNames.size(); i++) {
		if (countryNames.at(i) == country) { countryIndex = i; break; }
	}

	vector<int> temperatures;
	temperatures.push_back(summerTemp.at(countryIndex));
	temperatures.push_back(autumnTemp.at(countryIndex));
	temperatures.push_back(winterTemp.at(countryIndex));
	temperatures.push_back(springTemp.at(countryIndex));

///	taskA: 

	sort(temperatures.begin(), temperatures.end());

	cout << "Мінімальна температура: " << temperatures.at(0);
	cout << "\nМаксимальна температура: " << temperatures.at(3);
	cout << "\nСередня за рік: " << (temperatures.at(0) + temperatures.at(1) + temperatures.at(2) + temperatures.at(3)) / 4;

///	taskB: 
	int number;
	bool isNumberHigher = true;
	cout << "\nВведіть число\n"; cin >> number;

	for (int i = 0; i < 4; i++) {
		if (temperatures.at(i) > number) isNumberHigher = false; 
	}
	if(!isNumberHigher) cout << "Температура за рік була вище, ніж " << number;
	else cout << "Температура за рік не була вище, ніж " << number;

// taskC:

	cout << "\nРізниця між максимальною та мінімальною температурою за рік: "<< temperatures.at(3)-temperatures.at(0);
}

//https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/ istream iterator///