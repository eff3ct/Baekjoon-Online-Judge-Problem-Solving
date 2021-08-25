#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    double x;
    double y;
} Point;

Point s;
vector<Point> intersect;

Point getVector(Point& A, Point& B) { //return AB vector
    Point vec = {B.x - A.x, B.y - A.y};
    return vec;
}

int ccw(Point v, Point u) { //(v x u) cross product
    double val = v.x * u.y - v.y * u.x;
    if(val > 0) return 1;
    else if(val < 0) return -1;
    else return 0;
}

bool comp(Point& A, Point& B) {
    Point v = getVector(s, A);
    Point u = getVector(s, B);

    if(ccw(v, u) > 0) return true;
    else if(ccw(v, u) < 0) return false;

    if(v.x == u.x) return v.y < u.y;
    else return v.x < u.x;
}

bool isInside(vector<Point>& Q, Point& P) {
    Point start = Q[0];

    int right = Q.size() - 1;
    int left = 1;
    int mid = (left + right) / 2;

    Point slVec = getVector(start, Q[left]);
    Point srVec = getVector(start, Q[right]);
    Point sPVec = getVector(start, P);
    Point smVec;

    if(ccw(sPVec, slVec) > 0 || ccw(sPVec, srVec) < 0) return false;

    while(left + 1 < right) {
        mid = (left + right) / 2;

        smVec = getVector(start, Q[mid]);

        if(ccw(smVec, sPVec) > 0) left = mid;
        else right = mid;
    }

    Point lPVec = getVector(Q[left], P);
    Point PrVec = getVector(P, Q[right]);

    return ccw(lPVec, PrVec) < 0;
}

void initPoint_s(vector<Point>& Q) {
    s = {1001, 1001};
    for(auto& element : Q) {
        if(element.x < s.x) s = element;
        else if(element.x == s.x && element.y < s.y) s = element;
    }
}

Point getMeet(Point& A, Point& B, Point& C, Point& D) {
    Point ret;
    double a, b, c, d, e, f;

    a = A.y - B.y;
    b = B.x - A.x;
    c = A.x * a + A.y * b;

    d = C.y - D.y;
    e = D.x - C.x;
    f = C.x * d + C.y * e;

    double dn = a * e - b * d;

    ret = {((e * c - b * f) / dn), ((a * f - c * d) / dn)};

    return ret;
}


vector<Point> getConvexHull() {
    initPoint_s(intersect);
    sort(intersect.begin(), intersect.end(), comp); //sort by ccw (to use Graham's Scan)

    vector<Point> ret;
    for(int i = 0; i < intersect.size(); ++i) {
        if(ret.size() < 2) ret.push_back(intersect[i]);
        else {
            Point prev = ret[ret.size() - 2];
            Point now = ret[ret.size() - 1];

            Point v1 = getVector(prev, now);
            Point v2 = getVector(now, intersect[i]);

            while(ccw(v1, v2) <= 0) {
                ret.pop_back();
                if(ret.size() < 2) break;
                
                now = prev;
                prev = ret[ret.size() - 2];

                v1 = getVector(prev, now);
                v2 = getVector(now, intersect[i]);
            }

            ret.push_back(intersect[i]);
        }
    }

    return ret;
}

double getArea() {
    double ret = 0;

    vector<Point> group = getConvexHull();

    for(int i = 0; i < group.size() - 1; ++i) ret += group[i].x * group[i + 1].y;
    ret += group[group.size() - 1].x * group[0].y;

    for(int i = 0; i < group.size() - 1; ++i) ret -= group[i + 1].x * group[i].y;
    ret -= group[0].x * group[group.size() - 1].y;

    ret = abs(ret) / 2;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<Point> A(N);
    vector<Point> B(M);

    for(int i = 0; i < N; ++i) cin >> A[i].x >> A[i].y;
    for(int i = 0; i < M; ++i) cin >> B[i].x >> B[i].y;

    for(int i = 0; i < M; ++i) if(isInside(A, B[i])) intersect.push_back(B[i]);
    for(int i = 0; i < N; ++i) if(isInside(B, A[i])) intersect.push_back(A[i]);

    vector<Point> node;

    Point v, u;
    for(int i = 0; i < N; ++i) {
        v = getVector(A[i], A[(i + 1) % N]);
        
        for(int j = 0; j < M; ++j) {
            u = getVector(B[j], B[(j + 1) % M]);

            if(ccw(v, getVector(A[(i + 1) % N], B[j])) * ccw(v, getVector(A[(i + 1) % N], B[(j + 1) % M])) < 0 
            && ccw(u, getVector(B[(j + 1) % M], A[i])) * ccw(u, getVector(B[(j + 1) % M], A[(i + 1) % N])) < 0)
                node.push_back(getMeet(A[i], A[(i + 1) % N], B[j], B[(j + 1) % M]));
        }
    }

    //merge
    intersect.insert(intersect.end(), node.begin(), node.end());

    double ret = (intersect.size()) ? getArea() : 0;

    cout << fixed;
    cout.precision(15);

    cout << ret;

    return 0;
}