// https://www.acmicpc.net/problem/1310 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

typedef struct {
    ll x;
    ll y;
} Point;

Point startPoint;

Point getVector(Point& A, Point& B) { //return vector AB
    Point vec = {B.x - A.x, B.y - A.y};
    return vec;
}

int ccw(Point& v1, Point& v2) { //ccw btw v1 and v2
    ll value = (v1.x * v2.y - v1.y * v2.x);

    if(value > 0) return 1; //ccw
    else if(value == 0) return 0; //parallel
    else return -1; //cw
}

bool comp(Point& A, Point& B) {
    Point v1 = getVector(startPoint, A);
    Point v2 = getVector(startPoint, B);

    if(ccw(v1, v2) > 0) return true;
    else if(ccw(v1, v2) < 0) return false;

    if(v1.x == v2.x) return v1.y < v2.y;
    else return v1.x < v2.x;
}

ll getDistSquare(Point& A, Point& B) { return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y); }

ll maxDistance(vector<Point>& group) {
    if(group.size() == 1) return 0;
    if(group.size() == 2) return getDistSquare(group[0], group[1]);

    ll ret = 0;
    int aIdx = 1, bIdx = 2;

    Point aStart = group[0], aEnd = group[1], bStart = group[1], bEnd = group[2];
    while(true) {
        ret = max(ret, getDistSquare(aStart, bStart));

        Point v1 = getVector(aStart, aEnd);
        Point v2 = getVector(bStart, bEnd);

        if(ccw(v1, v2) > 0) {
            bIdx = (bIdx + 1) % group.size();
            bStart = bEnd;
            bEnd = group[bIdx];
        }
        else {
            aIdx++;

            if(aIdx == group.size()) {
                aStart = aEnd;
                aEnd = group[0];
            }
            else if(aIdx == group.size() + 1) break; //end condition

            aStart = aEnd;
            aEnd = group[aIdx];
        }
    }

    return ret;
}

vector<Point> getConvexHull(vector<Point>& group) {
    startPoint = {50001, 50001};
    for(int i = 0; i < group.size(); ++i) {
        if(group[i].x < startPoint.x) startPoint = group[i];
        else if(group[i].x == startPoint.x && group[i].y < startPoint.y) startPoint = group[i];
    }

    sort(group.begin(), group.end(), comp); //sort by ccw (to use Graham's Scan)

    vector<Point> ret;
    for(int i = 0; i < group.size(); ++i) {
        if(ret.size() < 2) ret.push_back(group[i]);
        else {
            Point prev = ret[ret.size() - 2];
            Point now = ret[ret.size() - 1];

            Point v1 = getVector(prev, now);
            Point v2 = getVector(now, group[i]);

            while(ccw(v1, v2) <= 0) {
                ret.pop_back();
                if(ret.size() < 2) break;
                
                now = prev;
                prev = ret[ret.size() - 2];

                v1 = getVector(prev, now);
                v2 = getVector(now, group[i]);
            }

            ret.push_back(group[i]);
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<Point> group(N);
    for(int i = 0; i < N; ++i) cin >> group[i].x >> group[i].y;

    vector<Point> convexHull = getConvexHull(group);
    cout << maxDistance(convexHull);

    return 0;
}