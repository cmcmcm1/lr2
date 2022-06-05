// lab2_cm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
double eps = 0.005;

int signum(int n) {
    return (n > 0 ? 1 : (n == 0 ? 0 : -1));
}
vector <vector <double>> getS(vector <vector <double>> a) {
    vector <vector <double>> s = { {0,0,0},{0,0,0},{0,0,0} };
    int d11 = signum(a[0][0]);
    s[0][0] = sqrt(fabs(a[0][0]));
    s[0][1] = a[0][1] / (d11 * s[0][0]);
    s[0][2] = a[0][2] / (d11 * s[0][0]);
    int d22 = signum(a[1][1] - d11 * s[0][1] * s[0][1]);
    s[1][1] = sqrt(fabs(a[1][1] - d11 * s[0][1] * s[0][1]));
    s[1][2] = (a[1][2] - d11 * s[0][1] * s[0][2]) / (d22 * s[1][1]);
    int d33 = signum(a[2][2] - s[0][2] * s[0][2] * d11 - s[1][2] * s[1][2] * d22);
    s[2][2] = sqrt(fabs(a[2][2] - s[0][2] * s[0][2] * d11 - s[1][2] * s[1][2] * d22));
    return s;
}
vector <vector <double>> transp(vector <vector <double>> m) {
    vector <vector <double>> mt = { {0,0,0},{0,0,0},{0,0,0} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mt[i][j] = m[j][i];
        }
    }
    return mt;
}
vector < vector <double>> matrixMult(vector <vector <double>> m1, vector <vector <int>> m2) {
    vector <vector <double>> mul = { {0,0,0},{0,0,0},{0,0,0} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++)
            {
                mul[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return mul;
}
void m1(vector <vector <double>> a, int b[3]) {
    cout << "the first method: " << endl;
    vector <vector <double>> s = getS(a); //find S
    cout << "S: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }

    int d11 = signum(a[0][0]), //find D
        d22 = signum(a[1][1] - d11 * s[0][1] * s[0][1]),
        d33 = signum(a[2][2] - s[0][2] * s[0][2] * d11 - s[1][2] * s[1][2] * d22);
    vector <vector<int>> d = { {d11, 0, 0}, {0,d22,0}, {0,0,d33} };
    cout << "D: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
    vector <vector <double>> m2 = matrixMult(transp(s), d);
    double y1 = b[0] / m2[0][0],
        y2 = (b[1] - m2[1][0] * y1) / m2[1][1],
        y3 = (b[2] - m2[2][0] * y1 - m2[2][1] * y2) / m2[2][2];
    cout << "vector y = (" << y1 << ", " << y2 << ", " << y3 << ")T" << endl;
    double x3 = y3 / s[2][2],
        x2 = (y2 - s[1][2] * x3) / s[1][1],
        x1 = (y1 - s[0][2] * x3 - s[0][1] * x2) / s[0][0];
    cout << "vector x = (" << x1 << ", " << x2 << ", " << x3 << ")T" << endl;
}
void m2(vector <vector <double>> a, int b[3]) {
    cout << "the second method:" << endl;
    double xk1 = 0, xk2 = 0, xk3 = 0, x1 = 0, x2 = 0, x3 = 0;  //xk, x(k+1)
    int k = 0;
    cout << k << ":  " << x1 << ", " << x2 << ", " << x3 << endl;
    while (true) {
        k++;
        x1 = xk1;
        x2 = xk2;
        x3 = xk3;
        xk1 = (b[0] - a[0][1] * x2 - a[0][2] * x3) / a[0][0];
        xk2 = (b[1] - a[1][0] * x1 - a[1][2] * x3) / a[1][1];
        xk3 = (b[2] - a[2][0] * x1 - a[2][1] * x2) / a[2][2];
        cout << k << ":  " << xk1 << ", " << xk2 << ", " << xk3 << endl;
        if (max(max(fabs(xk1 - x1), fabs(xk2 - x2)), fabs(xk3 - x3)) < eps) break;
    }
}

int main()
{
    vector <vector <double>> a = { {0,0,0},{0,0,0},{0,0,0} };
    int b[3];
    cout << "enter matrix 3*3: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }
    cout << "enter b: " << endl;
    for (int i = 0; i < 3; i++) {
        cin >> b[i];
    }
    m1(a, b);
    m2(a, b);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
