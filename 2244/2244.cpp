#include <vector>
#include <iostream>
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

int main() {
    int N, M; cin >> N >> M;
    vector<Point> A(N);
    vector<Point> B(M);
    vector<Point> C(N * M);

    for(int i = 0; i < N; ++i) cin >> A[i].x >> A[i].y;
    for(int i = 0; i < M; ++i) cin >> B[i].x >> B[i].y;

    int idx = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            C[idx].x = A[i].x + B[j].x;
            C[idx].y = A[i].y + B[j].y;
            idx++;
        }
    }

    C = getConvexHull(C);
    cout << C.size() << '\n';
    for(Point& p : C) {
        cout << p.x << ' ' << p.y << '\n';
    }

    return 0;
}