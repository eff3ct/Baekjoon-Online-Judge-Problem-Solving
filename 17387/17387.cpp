#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

typedef struct _Point {
    ll x;
    ll y;
} Point;

Point getVector(Point& A, Point& B) {
    Point vec = {B.x - A.x, B.y - A.y};
    return vec;
}

int ccw(Point& v, Point& u) {
    ll val = v.x * u.y - v.y * u.x;
    if(val > 0) return 1;
    else if(val < 0) return -1;
    else return 0;
}

bool operator<=(const Point& A, const Point& B) {
    if(A.x < B.x) return true;
    else if(A.x == B.x && A.y <= B.y) return true;
    else return false;
}

bool solve(Point& A, Point& B, Point& C, Point& D) {
    Point vecAB = getVector(A, B);
    Point vecCD = getVector(C, D);

    Point vecBC = getVector(B, C);
    Point vecBD = getVector(B, D);

    Point vecDA = getVector(D, A);
    Point vecDB = getVector(D, B);

    if(ccw(vecAB, vecBC) * ccw(vecAB, vecBD) == 0 && ccw(vecCD, vecDA) * ccw(vecCD, vecDB) == 0) {
        if(B <= A) swap(A, B);
        if(D <= C) swap(C, D);

        if(A <= D && C <= B) return true;
        else return false;
    }
    else if(ccw(vecAB, vecBC) * ccw(vecAB, vecBD) <= 0 && ccw(vecCD, vecDA) * ccw(vecCD, vecDB) <= 0) return true;
    else return false;
}

int main() {
    Point A, B, C, D;
    cin >> A.x >> A.y >> B.x >> B.y;
    cin >> C.x >> C.y >> D.x >> D.y;

    cout << solve(A, B, C, D);

    return 0;
}