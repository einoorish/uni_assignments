#include <iostream> 
#include <stack> 
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace std;

struct Point
{
	int x, y;
};

// A global point needed for  sorting points with reference 
// to  the first point Used in compare function of qsort() 
Point p0;

//to find next to top in a stack
Point nextToTop(stack<Point>& S)
{
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

void swap(Point& p1, Point& p2)
{
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

int distance(Point p1, Point p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) +
		(p1.y - p2.y) * (p1.y - p2.y);
}

// to find orientation of (!)ordered triplet (p, q, r). 
int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear 
	return (val > 0) ? 1 : 2; // 1 -> clockwise, 2 -> counterclock wise 
}

// A function used by library function qsort() to sort an array of 
// points with respect to the first point 
int compare(const void* vp1, const void* vp2)
{
	Point* p1 = (Point*)vp1;
	Point* p2 = (Point*)vp2;

	int o = orientation(p0, *p1, *p2);
	if (o == 0)
		return (distance(p0, *p2) >= distance(p0, *p1)) ? -1 : 1;

	return (o == 2) ? -1 : 1;
}

void convexHull(vector<Point> points, int n)
{
	// Find the bottommost point 
	int ymin = points[0].y, min = 0;
	for (int i = 1; i < n; i++)
	{
		int y = points[i].y;

		// Pick the bottom-most or chose the left most point in case of tie 
		if ((y < ymin) || (ymin == y &&
			points[i].x < points[min].x))
			ymin = points[i].y, min = i;
	}

	// Place the bottom-most point at first position 
	swap(points[0], points[min]);

	// sorts n-1 points with respect to the first point. 
	// A point p1 comes before p2 in sorted output if p2 has larger polar angle (in counterclockwise direction) than p1 
	p0 = points[0];
	qsort(&points[1], n - 1, sizeof(Point), compare);

	// If two or more points make same angle with p0, removes all but the one that is farthest from p0(should be the last point) 
	int m = 1; // Initialize size of modified array 
	for (int i = 1; i < n; i++)
	{
		//move to next if the angle is the same
		while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
			i++;

		points[m] = points[i];
		m++;  // update size of modified array 
	}

	//if modified array of points has less than 3 points, convex hull is not possible 
	if (m < 3) return;

	// Create an empty stack and push first three points 
	// to it. 
	stack<Point> S;
	S.push(points[0]);
	S.push(points[1]);
	S.push(points[2]);

	// Process remaining n-3 points 
	for (int i = 3; i < m; i++)
	{
		// Keep removing top while the angle formed by 
		// points next-to-top, top, and points[i] makes 
		// a non-left turn 
		while (orientation(nextToTop(S), S.top(), points[i]) != 2)
			S.pop();
		S.push(points[i]);
	// Now stack has the output points
	}

	float diameter = 0, diam_temp = 0;
	vector<Point> convex, result;
	int k, l;

	while (!S.empty())
	{
		convex.push_back(S.top());
		S.pop();
	}

	for (int i = 0; i <= convex.size() - 1; i++) {
		for (int j = 0; j <= convex.size() - 1; j++) {
			if (i != j) {
				diam_temp = sqrt(distance(convex.at(i), convex.at(j)));
				//cout << convex.at(i).x <<"&" << convex.at(i).y << "and" << convex.at(j).x << "&" << convex.at(j).y << "->" <<diam_temp << "\n";
				if (diam_temp > diameter) {
					diameter = diam_temp;
					k = i; l = j;
				}
			}
		}
	}

	result.push_back(convex.at(k));
	result.push_back(convex.at(l));

	int angle=1, max_angle=0, max_x = 0, max_y = 0;

	for (int i = 0; i < convex.size() - 1; i++) {
		if (i != k && i != l) {

			angle = (convex.at(i).x - result.at(0).x) * (convex.at(i).x - result.at(1).x) -
					(convex.at(i).y - result.at(0).y) * (convex.at(i).y - result.at(1).y);

			if (angle > max_angle) {
				max_angle = angle;
				max_x = convex.at(i).x;
				max_y = convex.at(i).y;
			}
		}
	}

	float side1 = sqrt(pow((max_y - result.at(0).y), 2) + pow((max_x - result.at(0).x), 2)),
		side2 = sqrt(pow((max_y - result.at(1).y), 2) + pow((max_x - result.at(1).x), 2)),
		side3 = sqrt(pow((result.at(1).y - result.at(0).y), 2) + pow((result.at(1).x - result.at(0).x), 2));

	float p = (side1 + side2 + side3) / 2;

	cout <<  side1 * side2 * side3 / (4 * sqrt(p * (p - side1) * (p - side2) * (p - side3)));
	
}

int main()
{
	int n;
	cout << "Points amount:\n";
	cin >> n;
	vector<Point> points;

	string input ="";
	getline(cin, input);
	int x, y;
	for (int i = 0; i < n; i++) {
		
		getline(cin, input);

		size_t spaceIndex = input.find_first_of(" ");
		if (input != "") {

			x = stoi(input.substr(0, spaceIndex));
			y = stoi(input.substr(spaceIndex + 1));

			points.push_back({ x, y });

		}
	}

	//points = { {0, 3}, {1, 1}, {2, 2}, {4, 4},
	//				  {0, 0}, {1, 2}, {3, 1}, {3, 3} };

	convexHull(points, points.size());
	
	return 0;
}
