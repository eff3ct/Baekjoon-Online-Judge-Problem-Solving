#include <iostream>
#include <cmath>

using namespace std;
double A, B, C;

double f(double x) {
    return A * x + B * sin(x);
}

int main() {
    cin >> A >> B >> C;

    double left = 0, right = 100000;
    double mid;
    for(int i = 0; i < 1000; ++i) {
        mid = (left + right) / 2.0;
        if(f(mid) >= C) right = mid;
        else left = mid;
    }

    cout << fixed;
    cout.precision(9);

    cout << mid;

    return 0;
}