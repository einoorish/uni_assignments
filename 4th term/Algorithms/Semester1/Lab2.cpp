// Lab num 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>


const int N = 30;

const int MAX = 200;

class Bolt {
public:
	int dat;
};

class Nut {
public:
	int dat;
};

	bool operator<(const Bolt & bolt, const Nut & nut) { return bolt.dat < nut.dat; }
	bool operator<(const Nut & nut, const Bolt & bolt) { return nut.dat < bolt.dat; }
	bool operator>(const Bolt & bolt, const Nut & nut) { return nut < bolt; }
	bool operator>(const Nut & nut, const Bolt & bolt) { return bolt < nut; }
	bool operator<=(const Bolt & bolt, const Nut & nut) { return !(bolt > nut); }
	bool operator<=(const Nut & nut, const Bolt & bolt) { return !(nut > bolt); }
	bool operator>=(const Bolt& bolt, const Nut& nut) { return !(bolt < nut); }
	bool operator>=(const Nut & nut, const Bolt & bolt) { return !(nut < bolt); }
	bool operator==(const Bolt & bolt, const Nut & nut) { return bolt.dat == nut.dat; }
	bool operator==(const Nut& nut, const Bolt& bolt) { return bolt == nut; }

std::ostream& operator<<(std::ostream& os, const Bolt& obj) {
	os << obj.dat;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Nut& obj) {
	os << obj.dat;
	return os;
}

template<typename T>
class Node {
public:
	T data;
	int i_index;
};

int rand_int(int min, int max) {
	static std::random_device rd;
	static std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	static std::mt19937_64 gen(seed);
	std::uniform_int_distribution<int> dist(min, max);

	return dist(gen);
}

template<typename T1, typename T2>
void init(Node<T1>* A, Node<T2>* B, int size) {
	for (int i = 0; i < size; i++) {
		B[i].data.dat = A[i].data.dat = rand_int(0, MAX);
		B[i].i_index = A[i].i_index = i;
	}

	static std::random_device rd;
	static std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	static std::mt19937_64 gen(seed);
	std::shuffle(B, B + size, gen);
}

template<typename T>
void print_array(T* A, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << A[i].data << ' ';
	}
	std::cout << std::endl;
}

template<typename T1, typename T2>
int partition(T1* A, T2* B, int down, int up) {
	int i_p = (down + up) / 2;
	T1 p_1 = A[i_p];
	int i = down - 1;
	int i_tmp = 0;

	for (int j = down; j <= up; j++) {
		if (B[j].data == p_1.data) {
			i_tmp = j;
		}
		else {
			if (B[j].data < p_1.data) {
				i++;
				if (B[i].data == p_1.data) i_tmp = j;
				std::swap(B[i], B[j]);

			}
		}
	}
	std::swap(B[i + 1], B[i_tmp]);
	std::swap(A[i + 1], A[i_p]);

	T2 p_2 = B[i + 1];
	i = down - 1;
	for (int j = down; j <= up; j++) {
		if (A[j].data < p_2.data) {
			i++;
			std::swap(A[i], A[j]);
		}
	}
	return (i + 1);
}

template<typename T1, typename T2>
void quick_sort(T1* A, T2* B, int down, int up) {
	if (down < up) {
		int p = partition(A, B, down, up);

		quick_sort(A, B, down, p - 1);
		quick_sort(A, B, p + 1, up);
	}
}

int main() {
	Node<Bolt> bolts[N];
	Node<Nut> nuts[N];
	for (int i = 1; i <= 10; i++) {
		std::cout << i << '.' << std::endl;

		init(bolts, nuts, N);
		print_array(bolts, N);
		print_array(nuts, N);

		std::cout << std::endl;

		quick_sort(bolts, nuts, 0, N - 1);
		print_array(bolts, N);
		print_array(nuts, N);

		std::cout << std::endl;
	}
	return 0;
}

