// https://www.acmicpc.net/problem/19532 //
// 2020 UCPC qualifier A //
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a, b, c, d, e, f; //input
    cin >> a >> b >> c >> d >> e >> f;

    /* using matrix to calculate (x, y)
       (x) = (a b)^(-1)(c) = 1 / (ae - bd) * (e -b)(c)
       (y)   (d e)     (f)                   (-d a)(f) */

    int dn = a * e - b * d;
    cout << (int)((e * c - b * f) / dn) << " " << (int)((a * f - c * d) / dn);

    return 0;
}