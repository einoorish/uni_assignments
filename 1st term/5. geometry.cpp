#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Point {
	int x, y;
};

void task1() {
	int diam, a, b;//a - height, b - width

	cin >> diam >> a >> b;
	diam *= 2;

	if (diam * diam >= a * a + b * b) {
		cout << "yes";
	}
	else cout << "no";
}

void task2() {
	int a, b, x, y, z, counter = 0;
	cin >> a >> b >> x >> y >> z;

	if (z <= b && y <= b) {
		cout << "можна так:(" << z << "," << y << ")"<<endl;
		counter++;
	}
	
	if (z <= b && x <= a) {
		cout << "можна так:(" << z << "," << x << ")" << endl;
		counter++;
	}

	if (y <= b && x <= a) {
		cout << "можна так:(" << y << "," << x << ")" << endl;
		counter++;
	}
			
	if(counter==0) cout << "не судьба";
}

bool task3() {
	int n;
	vector<Point> points;
	/*
		cout << "Points amount:\n";
		cin >> n;
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
		}*/

	points = { {0, 3}, {1, 1}, {2, 2}, {4, 4}, {3, -1}, {0, -3}, {-2, 0} };
	
	//points = { {0, 0} , {0, 5}, {5, 5}, {5, 0} };
	n = points.size();

	Point m = {2,3};

	bool b = false;
	for (int i = 0; i < n - 1; i++)//промінь вздовж вісі Ох
	{
		/*
		//перетин., якщо:
		//x1>, y1< ==> x2>, y1> ==> x2<, y2>
		if (m.x < points.at(i).x && m.y < points.at(i + 1).y && 
			(m.y < points.at(i + 1).y && m.x > points.at(i + 1).x) || m.y > points.at(i + 1).y && m.x < points.at(i + 1).x) {
			b = !b;
		}//x1<, y1<, x2>, y2>
		else if (m.x > points.at(i).x && m.y > points.at(i).y && m.y < points.at(i + 1).y && m.y < points.at(i + 1).y)
			b = !b;
		*/

		//if(m.x < points.at(i).x && m.y < points.at(i).y && m.y > points.at(i + 1).y 
			//|| m.x < points.at(i).x && m.y > points.at(i).y && m.y < points.at(i+1).y) b = !b;

		//якщо точка належить вершині
		if (m.x == points.at(i).x && m.y == points.at(i).y)return true;

		//якщо точка лежить на ребрі
		if (points.at(i).y != points.at(i+1).y) {
			if (((m.x< points.at(i).x && m.x> points.at(i+1).x) || (m.x > points.at(i).x && m.x < points.at(i+1).x))
				&& (m.x * (points.at(i).x - points.at(i+1).x) / (points.at(i).y - points.at(i + 1).y) == m.y))return true;
		}//якщо точка лежить на ребрі 2.0
		else if ((points.at(i).y == points.at(i + 1).y) && (m.y == points.at(i).y) 
			&& ((m.x < points.at(i).x && m.x> points.at(i+1).x) 
				|| (m.x > points.at(i).x && m.x < points.at(i+1).x))) return true;

		//якщо ребро належить променю
		if ((points.at(i).y == points.at(i+1).y) && (m.y == points.at(i).y))b = !b;
	}
	if (m.x < points.at(0).x && m.y<points.at(0).y && m.y>points.at(n-1).y 
		|| m.x<points.at(0).x && m.y>points.at(0).y && m.y < points.at(n-1).y) b = !b;//перетин з останнім ребром
	if ((points.at(0).y == points.at(n-1).y) && (points.at(0).y == m.y))b = !b;	//якщо ребро належить променю
	if (m.x == points.at(n-1).x && m.y == points.at(n-1).x)return true;//якщо точка у вершині

	return b;
}


int main()
{
	//task1();
	//task2();
	cout << task3(); 
}

