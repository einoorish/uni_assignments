#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class BigInt
{
	public:
		vector<int> digits;
	public:
		BigInt()
		{}

		BigInt(vector<int> value)
		{
			digits = value;
		}

		const BigInt& operator=(const BigInt& b) {
			if (this == &b) {
				return *this;
			}

			digits = b.digits;
			return *this;
		}

		friend const BigInt operator+(const BigInt& a, const BigInt& b) {

				int remains = 0;
				vector<int> result, max;
				int x = a.digits.size(), y = b.digits.size(), min, sum;

				if (x <= y) {
					min = x;
					max = b.digits;
				}
				else {
					min = y;
					max = a.digits;
				}

				for (int i = 0; i < min; i++) {
					sum = a.digits.at(i) + b.digits.at(i);
					if (sum % 10 + remains < 10)
						result.push_back(sum % 10 + remains);
					else result.push_back((sum % 10 + remains) % 10);
					remains = (sum + remains) / 10;

				}

				for (int i = min; i < max.size(); i++) {

					result.push_back(max.at(i) % 10 + remains);
					remains = max.at(i) / 10;
				}

				if (remains != 0) {
					result.push_back(remains);
				}

				BigInt res;
				res.digits = result;
				return res;

		}

		friend const BigInt operator-(const BigInt& a, const BigInt& b) {
			BigInt result = vector<int>{ 0 };//case 0: a == b
			//cout << ifMax(a, b) << endl;
			switch (ifMax(a, b)) {
				case 1: result = substract(a, b);
					break;
				case 2: result = substract(b, a);
					result.digits.at(result.digits.size() - 1) = result.digits.at(result.digits.size() - 1) * (-1);
					break;
			}

			try {
				while (result.digits.at(result.digits.size() - 1) == 0 && result.digits.size() != 1) {
					result.digits.erase(result.digits.begin() + result.digits.size() - 1);
				}
			}
			catch (out_of_range) {}

			return result;
		}

		friend ostream& operator<<(ostream& os, const BigInt& obj) {
			BigInt result = obj;

			/*
			try {
				while (result.digits.at(result.digits.size() - 1) == 0) {
					result.digits.erase(result.digits.begin() + result.digits.size() - 1);
				}
			} catch (out_of_range) {}
			*/
			for (size_t i = result.digits.size()-1; i != 0 ; i--) {
				try {
					os << result.digits.at(i);
				}
				catch (out_of_range) { break; }
			}try {
				os << obj.digits.at(0);
			}
			catch (out_of_range) {}



			return os;
		}

		static BigInt substract(const BigInt& a, const BigInt& b) {
			int remains = 0, sum = 0, i = 0;
			vector<int> result;
			for (i; i < b.digits.size(); i++) {
				sum = a.digits.at(i) - b.digits.at(i) - remains;
				if (sum < 0) {
					sum += 10;
					result.push_back(sum);
					remains = 1;
				}
				else {
					result.push_back(sum);
					remains = 0;
				}
			}

			for (int i = b.digits.size(); i < a.digits.size(); i++) {
				int sum = a.digits.at(i) - remains;

				if (sum < 0) {
					remains = 1;
					result.push_back(sum + 10);
				} else {
					result.push_back(sum);
					remains = 0;
				}
			}

			//if (sum < 0) result.at(0) = result.at(0) * (-1);

			//if (result.at(result.size() - 1) == -1) result.erase(result.begin() + result.size() - 1);
			BigInt res;
			res.digits = result;
			return res;
		}

		friend const BigInt operator*(const BigInt& a, const BigInt& b)
			{	
			BigInt  result, mid;
			int remains = 0, step = 0;

			for (int i = 0; i < a.digits.size(); i++) {
				for (int j = 0; j < b.digits.size(); j++) {

					int temp = a.digits.at(i) * b.digits.at(j);

					if (temp % 10 + remains < 10) {
						result.digits.push_back(temp % 10 + remains);
					}
					else result.digits.push_back((temp % 10 + remains) % 10);

					remains = (temp + remains) / 10;
				}

				if (remains != 0)
					result.digits.push_back(remains);

				for (int g = 0; g < step; g++) {
					result.digits.insert(result.digits.begin(), 0);
				}

				step++;
				mid = result + mid;
				result.digits.clear();
				remains = 0;
			}
			return mid;
		}
		
		friend const BigInt operator/(const BigInt& a, const BigInt& b) {
			BigInt result, mid;
			BigInt a_temp = a;
			int index = 0; // index is used in case a < b 

			/*while (ifMax(b, a_temp) == 1) {
				a_temp.digits.insert(a_temp.digits.begin(), 0);
				index++;
			}*/

			int i = a_temp.digits.size() - b.digits.size();
			for (int j = i; j < a_temp.digits.size(); j++) {
				mid.digits.push_back(a_temp.digits.at(j));
			}

			//cout << i << " ";
			int counter = 0;
			
			if (i == 0) {
				counter = 0;
				while ((ifMax(mid, b) == 1 || ifMax(mid, b) == 0)) {
					mid = mid - b;
					counter += 1;
				}
				result.digits.insert(result.digits.begin(), counter);
				return result;
			}

			while (i > 0) {
				counter = 0;
				if (ifMax(b, mid) == 1 && i != 0) {
					--i;
					mid.digits.insert(mid.digits.begin(), a_temp.digits.at(i));
				}


				int remains = 0, sum = 0;

				while ((ifMax(mid, b) == 1 || ifMax(mid, b) == 0)) {
					mid = mid - b;
					counter += 1;
					//cout << mid << " ";
				}
				try {
					while (mid.digits.at(mid.digits.size() - 1) == 0) mid.digits.erase(mid.digits.begin() + mid.digits.at(mid.digits.size() - 1));
				}
				catch (out_of_range) {}
			//	cout << mid << " " << counter << endl;


				result.digits.insert(result.digits.begin(), counter);
			}
			

			/*	if (mid.digits.at(0) != 0) {
				result.digits.insert(result.digits.begin(), -1);
				//for (int i = mid.size() - 1; i > 0; i--)
				//	result.digits.insert(result.digits.begin(), mid);

			}*/
			return result;
		}
		
		static int ifMax(const BigInt& a, const BigInt& b) {

			if (a.digits.size() > b.digits.size()) {
				return 1;
			}
			else if (a.digits.size() < b.digits.size()) {
				return 2;
			}
			else {
				if (a.digits.at(a.digits.size() - 1) < b.digits.at(b.digits.size() - 1))return 2;
				else if (a.digits.at(a.digits.size() - 1) > b.digits.at(b.digits.size() - 1)) return 1;

				for (int j = a.digits.size() - 1; j >= 0 ; j--) {
				//	cout << a.digits.at(j) << " " << b.digits.at(j) << endl;
					if (a.digits.at(j) > b.digits.at(j)) {
						return 1;
					}
					else if (a.digits.at(j) < b.digits.at(j)) {
						return 2;
					}
				}
				return 0;
			}
		}

};