#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
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

void solve(vector<Point>& group) {
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

    cout << ch.size();
}

int main() {
    int N; cin >> N;

    vector<Point> group(N);
    for(int i = 0; i < N; ++i) cin >> group[i].x >> group[i].y;
  
    solve(group);
    
    return 0;
}