#include <iostream>

using namespace std;

int main() {
    int x1, y1; cin >> x1 >> y1;
    int x2, y2; cin >> x2 >> y2;
    int x3, y3; cin >> x3 >> y3;

    int ux = x2 - x1;
    int uy = y2 - y1;

    int vx = x3 - x2;
    int vy = y3 - y2;

    if(ux * vy - uy * vx > 0) cout << 1;
    else if(ux * vy - uy * vx == 0) cout << 0;
    else cout << -1;

    return 0;
}