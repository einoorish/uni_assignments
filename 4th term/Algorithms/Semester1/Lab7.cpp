#include <string>
#include <vector>

using namespace std;

// Звичайний алгоритм Рабіна-Карпа
int RK_search(string &str, string &substr) { 		
　　　
　　　const int p = 13;//просте число
　　　
	vector<long long> p_pow(max(str.length(), subsrt.length()));
	p_pow[0] = 1;

	for (size_t i = 1; i < p_pow.size(); ++i)
		p_pow[i] = p_pow[i - 1] * p;

	vector<long long> h(str.length());
	for (size_t i = 0; i < str.length(); ++i){
		h[i] = (str[i] - 'a' + 1) * p_pow[i];
		if (i)  h[i] += h[i - 1];
	}

　　　//Шукаємо суму хешів
	long long h_s = 0; 

	for (size_t i = 0; i < substr.length(); ++i)
		h_s += (substr[i] - 'a' + 1) * p_pow[i];

	for (size_t i = 0; i + substr.length() - 1 < str.length(); ++i){
		long long cur_h = h[i + substr.length() - 1];
		if (i)  cur_h -= h[i - 1];
		if (cur_h == h_s * p_pow[i])

　　　//Знайдено збіг на позиції і
			return i;
	}

　　　//Збігів не знайдено
	return -1;
}

 // Узагальнений алгоритм Рабіна-Карпа
pair<int, int> RK_matrixSearch(vector<string>& text, vector<string>& pattern) {
	int m = text.size();
	int n = pattern.size();

	for (int row = 0; i < m - n + 1; row++) {

		int firstColumn = -1;
		int prevColumn = -1;
 
		do {
			prevColumn = firstColumn;
			firstColumn = RK_search(text[row]
　　　.substr(prevColumn + 1, n), pattern[0]);

			if (firstColumn >= 0) {
				firstColumn += prevColumn;
				bool entry = true;
	
				for (int j = 0; j < n; j++) {
					if(RK_search(text[row + j]
　　　.substr(firstColumn, n), pattern[j]) != 0) {
						
　　　entry = false;
						break;
					}
				}

　　　//Успішне завершення алгоритму
				if (entry) return {row, firstColumn};
			}

		} while (firstColumn != -1);	

	}

　　　//Збігів не знайдено
	return {-1, -1};

}