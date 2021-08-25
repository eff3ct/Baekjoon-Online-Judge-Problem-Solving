#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <stack>

using namespace std;
typedef long long ll;

typedef struct {
    int x;
    int y;
} Point;

Point s;

bool ccw(Point& A, Point& B, Point& C) { 
    //AB x BC
    Point v1 = {B.x - A.x, B.y - A.y};
    Point v2 = {C.x - B.x, C.y - B.y};
    return ((ll)v1.x * v2.y - (ll)v1.y * v2.x) > 0;
}

bool comp(Point& A, Point& B) {
    //sA x sB
    Point v1 = {A.x - s.x, A.y - s.y};
    Point v2 = {B.x - s.x, B.y - s.y};
    ll value = (ll)v1.x * v2.y - (ll)v1.y * v2.x;

    if(value > 0) return true;
    else if(value < 0) return false;

    //case ccw = 0
    if(A.x == B.x) return A.y < B.y;
    else return A.x < B.x;
}

vector<Point> ch(vector<Point>& group) {
    s = {40001, 40001};
    for(int i = 0; i < group.size(); ++i) {
        if(s.x > group[i].x) {
            s.x = group[i].x;
            s.y = group[i].y;
        }
        else if(s.x == group[i].x && s.y > group[i].y) {
            s.x = group[i].x;
            s.y = group[i].y;
        }
    }

    sort(group.begin(), group.end(), comp);

    vector<Point> ch;
    for(int i = 0; i < group.size(); ++i) {
        if(ch.size() < 2) ch.push_back(group[i]);
        else {
            Point prev = ch[ch.size() - 2];
            Point now = ch[ch.size() - 1];

            while(!ccw(prev, now, group[i])) { //if not ccw,
                ch.pop_back(); //pop stack top
                if(ch.size() < 2) break;
                now = prev;
                prev = ch[ch.size() - 2];
            }

            ch.push_back(group[i]); //if ccw push
        }
    }

    return ch;
}

double getDist(Point& A, Point& B) {
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

double rotCalipers(vector<Point>& cH) {
    if(cH.size() == 2) return getDist(cH[0], cH[1]);

    double dist = 0;
    int aIdx = 1, bIdx = 2;

    Point As, Ae, Bs, Be;
    As = cH[0], Ae = cH[1], Bs = cH[1], Be = cH[2];

    while(true) {
        dist = max(dist, getDist(As, Bs));

        Point v1 = {Ae.x - As.x, Ae.y - As.y};
        Point v2 = {Be.x - Bs.x, Be.y - Bs.y};

        ll crossProduct = (v2.y * v1.x - v2.x * v1.y);

        if(crossProduct > 0) {
            Bs = Be;
            bIdx = (bIdx + 1) % cH.size();
            Be = cH[bIdx];
        }
        else {
            As = Ae;
            aIdx += 1;

            if(aIdx == cH.size()) Ae = cH[0];
            else if(aIdx == cH.size() + 1) break; //end condition

            Ae = cH[aIdx];
        }
    }

    return dist;
}

int main() {
    int C; cin >> C;

    vector<Point> group(C);
    for(int i = 0; i < C; ++i) cin >> group[i].x >> group[i].y;
  
    vector<Point> convexHull = ch(group);

    cout << fixed;
    cout.precision(8);

    cout << rotCalipers(convexHull);
    
    return 0;
}