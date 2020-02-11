#include <iostream> 
#include <stack> 
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace std;

struct Point
{
	float x, y;
};

struct Combination
{
	int i,j,k;
};

/*
float seredPerpendFormulaB(Point a, Point b) {
	return (b.y + a.y) / 2 + (b.x + a.x) / (b.y + a.y) * (a.x + b.x) / 2;
}

Point findO(Point a, Point b, Point c) {
	float x=0, y=0, b1 = seredPerpendFormulaB(a, b);

	x = (seredPerpendFormulaB(b, c) + b1) / ((b.x - a.x) / (b.y - a.y) - (c.x - b.x) / (c.y - b.y));
	y = -x * ((b.x - a.x) / (b.y - a.y)) + b1;
	return {x,y};
}*/
/*
float calculateK(Point a, Point b) {
	return -(b.x - a.x) / (b.y - a.y);
}

Point findO(Point a, Point b, Point c) {
	float k1 = calculateK(a, c), k2 = calculateK(b, c), x, y;

	x = (-b.y + k1 * b.x + a.y - k2 * a.x) / (k1 - k2);
	y = k1 * x + b.y - k1 * b.x;
	return { x,y };
}
*/
float calculateSmth(Point a, Point b) {
	return pow(a.x, 2) + pow(a.y, 2) - pow(b.x, 2) - pow(b.y, 2);
}
Point findO(Point a, Point b, Point c) {

	float y = 1 / 2 * (-1*calculateSmth(b,c)*(b.x - a.x)
		+ calculateSmth(a,b)*(c.x-b.x))/((c.y-b.y)*(b.x-a.x)-(b.y-a.y)*(c.x-b.x));

	float x = 1 / 2 * (calculateSmth(a, b) * (c.y - b.y) - calculateSmth(b, c) * (b.y - a.y)) 
		/ ( (c.x - b.x) * (b.y - a.y) - (b.x - a.x) * (c.y - b.y) );

	return { x,y };
}

bool cmpf(float A, float B, float epsilon = 0.05f)
{
	return (fabs(A - B) < epsilon);
}

float distanceBetweenTwoPoints(Point a, Point b) {
	return sqrt(pow((a.y - b.y), 2) + pow((a.x - b.x), 2));
}

void task2(vector<Point> points) {

	int maxPoints = 0;
	vector<Combination> combinations;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size(); j++) {
			for (int k = 0; k < points.size(); k++) {
				if (i != k && i != j && j != k) {
					combinations.push_back({ i, j, k });
					for (int i = 0; i < combinations.size(); i++) {

						if (combinations.at(i) == {i, k, j}) break;

						else {

							float side1 = distanceBetweenTwoPoints(points.at(i), points.at(j)),
								side2 = distanceBetweenTwoPoints(points.at(i), points.at(k)),
								side3 = distanceBetweenTwoPoints(points.at(k), points.at(j));

							float p = (side1 + side2 + side3) / 2;

							float radius = side1 * side2 * side3 / (4 * sqrt(p * (p - side1) * (p - side2) * (p - side3)));
							if (isinf(radius))  // to skip colinear vectors
								break;

							Point result = findO(points.at(i), points.at(j), points.at(k));
							if (isnan(result.x) || isnan(result.y))
								break;

							cout << "O(" << result.x << "; " << result.y << ") для " << "(" << points.at(i).x << "; " << points.at(i).y << "), "
								<< "(" << points.at(j).x << "; " << points.at(j).y << "), " << "(" << points.at(k).x << "; " << points.at(k).y
								<< "), радіус = " << radius << endl;


							int counter = 0; // number of points on a circle

							for (int n = 0; n < points.size(); n++) {
								if (cmpf(radius, distanceBetweenTwoPoints(result, points.at(n)))) {
									counter++;
								}
							}
							if (maxPoints < counter) maxPoints = counter;
						}
					}
				}
			}
		}
	}
	cout << maxPoints;
}



void task3(vector<Point> points) {

	int maxArea = 0, maxPerimeter = 0, imax, jmax, kmax, amax, bmax, cmax;

	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size(); j++) {
			for (int k = 0; k < points.size(); k++) {
				if (i != k && i != j && j != k) {
					float side1 = distanceBetweenTwoPoints(points.at(i), points.at(j)),
						side2 = distanceBetweenTwoPoints(points.at(i), points.at(k)),
						side3 = distanceBetweenTwoPoints(points.at(k), points.at(j));

					float p = (side1 + side2 + side3)/2, s;
					s = sqrt(p * (p - side1) * (p - side2) * (p - side3));
					
					if (p * 2 > maxPerimeter) {
						maxPerimeter = p; amax = i; bmax = j; cmax = k;
					}
					if (s > maxArea) {
						maxArea = s; imax = i; jmax = j; kmax = k;
					}
				}
			}
		}
	}

	cout << "max периметр = " << maxPerimeter << " з трикутника " << "(" << points.at(amax).x << "; " << points.at(bmax).y << "), " << "(" << points.at(amax).x << "; " << points.at(cmax).y << ")" << "(" << points.at(bmax).x << "; " << points.at(cmax).y << ")"
		<< ",\n площа = " << maxArea << " з трикутника" << "(" << points.at(imax).x << "; " << points.at(imax).y << "), "
		<< "(" << points.at(jmax).x << "; " << points.at(jmax).y << "), " << "(" << points.at(kmax).x << "; " << points.at(kmax).y << ")";
}

int main()
{
	int n;
	//cout << "Points amount:\n";
	//cin >> n;
	vector<Point> points;
	/*
	string input ="";
	getline(cin, input);
	float x, y;
	for (int i = 0; i < n; i++) {

		getline(cin, input);

		size_t spaceIndex = input.find_first_of(" ");
		if (input != "") {

			x = stoi(input.substr(0, spaceIndex));
			y = stoi(input.substr(spaceIndex + 1));

			points.push_back({ x, y });

		}
	}
	*/
	//points = { {0, 3}, {1, 1}, {2, 2}, {4, 4},
	//				  {0, 0}, {1, 2}, {3, 1}, {3, 3} };

	points = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

	task2(points);
	//task3(points);

	return 0;
}

