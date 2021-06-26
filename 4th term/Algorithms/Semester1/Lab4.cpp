

#include <iostream>
#include <vector>

using namespace std;

//вивід масиву у консоль
void print(vector <pair <int, char>> a, int n) {    
for (int i = 0; i < n; i++) {
        cout << a[i].first;
        cout << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i].second << " ";
    }
    cout << "\n\n";
}

//копіює вектор b в а
void copy(vector<pair<int, char>>& a, vector<pair<int, char>> b) {    for (int i = 0; i < b.size(); i++)
        a[i] = b[i];
}

//--------------------------------------------------------------------

 // Критерії 1, 2:  О(n), стійке сортування

void first_case(vector <pair <int, char>>& a, int n) {
    vector <pair <int, char>> result;
    int p = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first == 0)
            result.push_back(a[i]);
    }
    for (int i = 0; i < n; i++) {
        if (a[i].first == 1)
            result.push_back(a[i]);
    }

    copy(a, result);
}




// Критерії 1, 3: O(n), сортування на місці
void second_case(vector <pair <int, char>>& a) { 
    int p = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first == 0) {
            swap(a[p], a[i]);
            p++;
        }
    }
}



// Критерії 2, 3:  стійкість, сортування на місці
void third_case(vector <pair <int, char>>& a, int n) { 
    int cnt = 0;
    int n = a.size();
    bool flag = true;
    while (flag) {
        flag = false;
        for (int j = 0; j < n - 1; j++) {
            if (a[j].first > a[j + 1].first) {
                swap(a[j], a[j + 1]);
                flag = true;
            }
        }
    }
}

//--------------------------------------------------------------------

int main()
{
    int n = 10;
    vector<pair<int, char>> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        a[i].first = rand() % 2;
        a[i].second = rand() % 100 + '0';
    }
    copy(b, a);
    copy(c, a);
    print(a, 10);


    cout << "sort  1" << endl;
    first_case(b, 10);
    print(b, 10);

    cout << "sort  2" << endl;
    second_case(c);
    print(c, 10);

    cout << "sort  3" << endl;
    third_case(a, 10);
    print(a, 10);


}

