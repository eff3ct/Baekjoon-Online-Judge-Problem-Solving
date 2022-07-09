#include <bits/stdc++.h>

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

ll getDist(Point& A, Point& B) {
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

ll rotCalipers(vector<Point>& convexHull) {
    ll ret = 0;
    int b = 1, f = 0;
    int s = (int)convexHull.size();
    bool flag = false;
    while(true) {
        Point frontVector = getVector(convexHull[f], convexHull[(f + 1) % s]);
        Point backVector = getVector(convexHull[b], convexHull[(b + 1) % s]);

        ret = max(ret, getDist(convexHull[f], convexHull[b]));

        if(ccw(frontVector, backVector) > 0) b = (b + 1) % s;
        else {
            f = (f + 1) % s;
            flag = true;
        }

        if(f == 0 && flag) break;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll N, T; cin >> N >> T;

    vector<Point> coord(N), speed(N);
    for(int i = 0; i < N; ++i) cin >> coord[i].x >> coord[i].y >> speed[i].x >> speed[i].y;

    ll left = 0, right = T;
    vector<Point> l_mid_stars(N), r_mid_stars(N);
    vector<Point> l_mid_cHullStars, r_mid_cHullStars;
    ll l_mid_dist = LLONG_MAX, r_mid_dist;

    while(left + 4 < right) {
        ll l_mid = (2 * left + right) / 3, r_mid = (left + 2 * right) / 3;

        for(int i = 0; i < N; ++i) {
            l_mid_stars[i] = {coord[i].x + speed[i].x * l_mid, coord[i].y + speed[i].y * l_mid};
            r_mid_stars[i] = {coord[i].x + speed[i].x * r_mid, coord[i].y + speed[i].y * r_mid};
        }

        l_mid_cHullStars = getConvexHull(l_mid_stars);
        r_mid_cHullStars = getConvexHull(r_mid_stars);

        l_mid_dist = rotCalipers(l_mid_cHullStars);
        r_mid_dist = rotCalipers(r_mid_cHullStars);

        if(l_mid_dist < r_mid_dist) right = r_mid;
        else left = l_mid;
    }

    ll ret = l_mid_dist;
    ll retTime = left;

    for(int j = left; j <= right; ++j) {
        for(int i = 0; i < N; ++i) {
            l_mid_stars[i] = {coord[i].x + speed[i].x * j, coord[i].y + speed[i].y * j};
        }
        l_mid_cHullStars = getConvexHull(l_mid_stars);
        l_mid_dist = rotCalipers(l_mid_cHullStars);
        if(ret > l_mid_dist) {
            retTime = j;
            ret = l_mid_dist;
        }
    }

    cout << retTime << '\n' << ret;
    
    return 0;
}