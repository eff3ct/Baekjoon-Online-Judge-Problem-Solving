#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef struct _Point {
    ll x;
    ll y;
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

//Graham's Scan Method
vector<Point> getConvexHull(vector<Point>& A) {
    S = *min_element(A.begin(), A.end());
    sort(A.begin(), A.end(), comp);
    int n = (int)A.size();

    vector<Point> convexHull;

    //get Convex Hull
    for(int i = 0; i < n; ++i) {
        while((int)convexHull.size() > 1 
        && ccw(convexHull[(int)convexHull.size() - 2], convexHull.back(), A[i]) <= 0) {
            convexHull.pop_back();
        }
        convexHull.push_back(A[i]);
    }
    
    return convexHull;
}

double getDist(const Point& A, const Point& B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, L; cin >> N >> L;

    vector<Point> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i].x >> A[i].y;

    A = getConvexHull(A);

    double ret = 0;
    int sz = (int)A.size();
    for(int i = 0; i < sz; ++i) {
        ret += getDist(A[i], A[(i + 1) % sz]);

        Point u = getVector(A[i], A[(i + 1) % sz]);
        Point v = getVector(A[(i + 1) % sz], A[(i + 2) % sz]);

        ret += (double)L * acos((u.x * v.x + u.y * v.y) / (sqrt(u.x * u.x + u.y * u.y) * sqrt(v.x * v.x + v.y * v.y)));
    }

    cout << (ll)round(ret);
}