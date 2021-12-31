#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

typedef struct _Point {
    int x;
    int y;
} Point;

//Standard Point to Sort
Point S;

Point getVector(const Point& A, const Point& B) {
    Point v = {B.x - A.x, B.y - A.y};
    return v;
}

//ccw test
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

double solve(vector<Point>& poly) {
    vector<Point> convexHull;

    S = *min_element(poly.begin(), poly.end());
    sort(poly.begin(), poly.end(), comp);

    for(int i = 0; i < (int)poly.size(); ++i) {
        while((int)convexHull.size() > 1 
        && ccw(convexHull[(int)convexHull.size() - 2], convexHull.back(), poly[i]) <= 0) {
            convexHull.pop_back();
        }

        convexHull.push_back(poly[i]);
    }

    double ret = 987654321.0;
    int s = (int)convexHull.size();
    for(int i = 0; i < s; ++i) {
        Point dir = getVector(convexHull[i], convexHull[(i + 1) % s]);
        double dist = 0.0;
        for(int j = 0; j < s; ++j) {
            Point uv = getVector(convexHull[i], convexHull[j]);
            dist = max(dist, fabs(uv.x * dir.y - uv.y * dir.x) / sqrt(pow(dir.x, 2) + pow(dir.y, 2)));
        }

        ret = min(dist, ret);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int cnt = 0;

    cout << fixed;
    cout.precision(2);

    while(true) {
        int n; cin >> n;
        if(n == 0) break;

        vector<Point> poly(n);
        for(int i = 0; i < n; ++i) cin >> poly[i].x >> poly[i].y;

        cout << "Case " << ++cnt << ": ";
        double ret = ceil(solve(poly) * 100.0) / 100.0;
        
        cout << ret << '\n';
    }

    return 0;
}