#pragma once
#include <iostream>

class Ñoordinates {

public:

	int x = 0, y = 0, z = 0;
	Ñoordinates() = default;
	Ñoordinates(int x, int y, int z) : x(x), y(y), z(z) {};

	bool operator>(const Ñoordinates& rhs) {
		return (x-y-z) > (rhs.x - rhs.y - rhs.z);
	}

	bool operator<(const Ñoordinates& rhs) {
		return (x - y - z) < (rhs.x - rhs.y - rhs.z);
	}

	bool operator==(const Ñoordinates& rhs) {
		return (x - y - z) == (rhs.x - rhs.y - rhs.z);
	}

	friend std::ostream& operator<<(std::ostream& os, const Ñoordinates& c) {
		os << "(" << c.x << ";" << c.y << ";" << c.z << ")";
		return os;
	}

};