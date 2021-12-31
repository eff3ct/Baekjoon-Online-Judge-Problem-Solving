#include <iostream>
#include <vector>
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

bool isInsidePoint(Point& X, vector<Point>& convexHull) {
    if((int)convexHull.size() <= 2) return false;
    int left = 1, right = (int)convexHull.size() - 1, mid;

    Point vecOL = getVector(convexHull[0], convexHull[left]);
    Point vecOR = getVector(convexHull[0], convexHull[right]);
    Point vecOX = getVector(convexHull[0], X);

    if(ccw(vecOR, vecOX) > 0 || ccw(vecOL, vecOX) < 0) return false;

    while(left + 1 < right) {
        mid = (left + right) / 2;

        Point vecOM = getVector(convexHull[0], convexHull[mid]);

        if(ccw(vecOM, vecOX) <= 0) right = mid;
        else left = mid;
    }

    Point vecLX = getVector(convexHull[left], X);
    Point vecXR = getVector(X, convexHull[right]);

    return ccw(vecLX, vecXR) <= 0;
}

bool operator<=(const Point A, const Point B) {
    if(A.x < B.x) return true;
    else if(A.x == B.x && A.y <= B.y) return true;
    else return false;
}

//cross test
bool isCross(const Point& A, const Point& B, const Point& C, const Point& D) {
    if(ccw(A, B, C) * ccw(A, B, D) == 0 && ccw(C, D, A) * ccw(C, D, B) == 0) {
        Point _A(A), _B(B), _C(C), _D(D);
        if(_B <= _A) swap(_A, _B);
        if(_D <= _C) swap(_C, _D);

        if(_A <= _D && _C <= _B) return true;
        else return false;
    }
    else if(ccw(A, B, C) * ccw(A, B, D) <= 0 && ccw(C, D, A) * ccw(C, D, B) <= 0) return true;
    else return false;
}

bool isInside(vector<Point>& A, vector<Point>& B) {
    if((int)A.size() == 1 && (int)B.size() == 2) {
        Point vecP = getVector(B[0], A[0]);
        Point vecQ = getVector(A[0], B[1]);

        if(ccw(vecP, vecQ) == 0) return true;
        else return false;
    }
    else if((int)A.size() == 2 && (int)B.size() == 1) {
        Point vecP = getVector(A[0], B[0]);
        Point vecQ = getVector(B[0], A[1]);

        if(ccw(vecP, vecQ) == 0) return true;
        else return false;
    }
    else if((int)A.size() == 1 && (int)B.size() == 1) {
        return false;
    } 

    for(int i = 0; i < (int)A.size(); ++i) {
        Point vecA = getVector(A[i], A[(i + 1) % (int)A.size()]);
        for(int j = 0; j < (int)B.size(); ++j) {
            Point vecB = getVector(B[j], B[(j + 1) % (int)B.size()]);
            Point vecAl = getVector(A[(i + 1) % (int)A.size()], B[j]), vecAr = getVector(A[(i + 1) % (int)A.size()], B[(j + 1) % (int)B.size()]);
            Point vecBl = getVector(B[(j + 1) % (int)B.size()], A[i]), vecBr = getVector(B[(j + 1) % (int)B.size()], A[(i + 1) % (int)A.size()]);

            if(ccw(vecA, vecAl) * ccw(vecA, vecAr) == 0 && ccw(vecB, vecBl) * ccw(vecB, vecBr) == 0) {
                if(isCross(A[i], A[(i + 1) % (int)A.size()], B[j], B[(j + 1) % (int)B.size()])) return true;
            }
            else if(ccw(vecA, vecAl) * ccw(vecA, vecAr) <= 0 && ccw(vecB, vecBl) * ccw(vecB, vecBr) <= 0) return true;
        }
    }

    for(int i = 0; i < (int)A.size(); ++i) {
        if(isInsidePoint(A[i], B)) return true;
    }

    for(int i = 0; i < (int)B.size(); ++i) {
        if(isInsidePoint(B[i], A)) return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    while(T --> 0) {
        int n, m; cin >> n >> m;

        vector<Point> black(n);
        vector<Point> white(m);

        for(int i = 0; i < n; ++i) cin >> black[i].x >> black[i].y;
        for(int i = 0; i < m; ++i) cin >> white[i].x >> white[i].y;

        vector<Point> blackCH = getConvexHull(black);
        vector<Point> whiteCH = getConvexHull(white);

        if(isInside(blackCH, whiteCH)) cout << "NO" << '\n';
        else cout << "YES" << '\n';
    }

    return 0;
}