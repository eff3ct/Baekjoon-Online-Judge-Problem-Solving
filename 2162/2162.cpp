#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;
typedef long long ll;

typedef struct _Point {
    _Point() = default;
    _Point(ll _x, ll _y) : x(_x), y(_y) {}
    ll x, y;
} Point;

typedef struct _Line {
    Point p1, p2;
} Line;

bool operator<=(const Point& A, const Point& B) {
    if(A.x < B.x) return true;
    else if(A.x == B.x && A.y <= B.y) return true;
    else return false;
}

istream& operator>>(istream& is, Point& p1) {
    is >> p1.x >> p1.y;
    return is;
}

Point get_vector(Point A, Point B) {
    return Point(B.x - A.x, B.y - A.y);
}

int ccw(Point u, Point v) {
    ll val = u.x * v.y - u.y * v.x;
    if(val > 0) return 1;
    else if(val == 0) return 0;
    else return -1;
}

int find(int a, vector<int>& parent) {
    if(a == parent[a]) return a;
    else return parent[a] = find(parent[a], parent);
}

void uni(int a, int b, vector<int>& parent) {
    int a_parent = find(a, parent);
    int b_parent = find(b, parent);

    if(a_parent == b_parent) return;
    else if(a_parent < b_parent) parent[b_parent] = a_parent;
    else parent[a_parent] = b_parent;
}

bool is_cross(Point& A, Point& B, Point& C, Point& D) {
    Point vecAB = get_vector(A, B);
    Point vecCD = get_vector(C, D);

    Point vecBC = get_vector(B, C);
    Point vecBD = get_vector(B, D);

    Point vecDA = get_vector(D, A);
    Point vecDB = get_vector(D, B);

    if(ccw(vecAB, vecBC) * ccw(vecAB, vecBD) == 0 && ccw(vecCD, vecDA) * ccw(vecCD, vecDB) == 0) {
        if(B <= A) swap(A, B);
        if(D <= C) swap(C, D);

        if(A <= D && C <= B) return true;
        else return false;
    }
    else if(ccw(vecAB, vecBC) * ccw(vecAB, vecBD) <= 0 && ccw(vecCD, vecDA) * ccw(vecCD, vecDB) <= 0) return true;
    else return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<Line> lines(N);
    vector<int> parent(N);
    vector<int> count(N);
    iota(parent.begin(), parent.end(), 0);

    for(int i = 0; i < N; ++i) cin >> lines[i].p1 >> lines[i].p2;

    for(int i = 0; i < N; ++i) {
        for(int j = i + 1; j < N; ++j) {
            if(is_cross(lines[i].p1, lines[i].p2, lines[j].p1, lines[j].p2) 
            && (find(i, parent) != find(j, parent))) {
                uni(i, j, parent);
            }
        }
    }

    for(int i = 0; i < N; ++i) count[find(i, parent)]++;
    int group_count = 0;
    for(int i = 0; i < N; ++i) if(count[i]) group_count++;
    cout << group_count << '\n' << *max_element(count.begin(), count.end());

    return 0;
}