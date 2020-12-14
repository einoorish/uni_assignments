#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void swap(int* a, int i, int j)
{
	int s = a[i];
	a[i] = a[j];
	a[j] = s;
}
/*
bool nextPermutation(int* arr, int n)
{
	int j = n - 2;
	while (j != -1 && arr[j] >= arr[j + 1]) j--;
	if (j == -1)
		return false; // больше перестановок нет
	int k = n - 1;
	while (arr[j] >= arr[k]) k--;
	swap(arr, j, k);
	int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
	while (l < r)
		swap(arr, l++, r--);
	return true;
}*/

void print(int* arr, int n) 
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void nextPermutation(int* arr, int i, int n)// i - число елементів, що буде переставлятися
{
	if (i == 1) print(arr,n);
	else{
		for (int j = 0; j < i; j++)
		{
			swap(arr[j], arr[i - 1]); //міняємо останній елемент з кожним ( в тому числі з самим собою)

			nextPermutation(arr, i - 1, n); //функція для i-1 елементів
			swap(arr[j], arr[i - 1]); // для "красивого" виходу з рекурсії
		}
	}
}

int main()
{
	const int n = 3;
	int arr[n];
	for (int i = 0; i < n; i++) {
		arr[i] = i+1;
	}
	nextPermutation(arr,n, n);
	//while (nextPermutation(arr, 4))
		//print(arr, 4);
	return 0;

	
	/*
	do {
		for (int i = 0; i < 8; i++)
			std::cout << arr[i] << ' ';
		std::cout << '\n';
	} while (std::next_permutation(arr, arr + 8));

	std::cout << "After loop: \n";
	for (int i = 0; i < 8; i++)
		std::cout << arr[i] << ' ';
	std::cout << '\n';
	return 0;*/
	
}