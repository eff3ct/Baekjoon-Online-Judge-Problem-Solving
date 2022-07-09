#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

typedef struct _Point {
    int x;
    int y;
    int idx;
} Point;

//Standard Point to Sort
Point S;

Point getVector(const Point& A, const Point& B) {
    Point v = {B.x - A.x, B.y - A.y};
    return v;
}

//if size of data can make overflow, change to long long type
int ccw(const Point& v, const Point& u) {
    ll val = (ll)v.x * u.y - (ll)v.y * u.x;
    if(val > 0) return 1;
    else if(val < 0) return -1;
    else return 0;
}

int ccw(const Point& A, const Point& B, const Point& C) {
    Point v = getVector(A, B);
    Point u = getVector(B, C);
    return ccw(v, u);
}

//to sort by ccw
bool comp(const Point& A, const Point& B) {
    Point v = getVector(S, A);
    Point u = getVector(S, B);

    if(ccw(v, u) > 0) return true;
    else if(ccw(v, u) < 0) return false;

    return (v.x == u.x) ? (v.y < u.y) : (v.x < u.x);
}

bool operator<(const Point& A, const Point& B) {
    return (A.x == B.x) ? (A.y < B.y) : (A.x < B.x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int c; cin >> c;

    while(c --> 0) {
        int n; cin >> n;

        vector<Point> points(n);
        for(int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
            points[i].idx = i;
        }

        S = *min_element(points.begin(), points.end());
        sort(points.begin(), points.end(), comp);

        for(int i = n - 1; i >= 1; --i) {
            Point u = getVector(S, points[i]);
            Point v = getVector(S, points[i - 1]);

            if(ccw(u, v) != 0) {
                reverse(points.begin() + i, points.end());
                break;
            }
        }

        for(int i = 0; i < n; ++i) cout << points[i].idx << ' ';
        cout << '\n';
    }

    return 0;
}