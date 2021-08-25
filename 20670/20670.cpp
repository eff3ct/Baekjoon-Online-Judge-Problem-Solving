// https://www.acmicpc.net/problem/20670 //
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

typedef struct {
    ll x;
    ll y;
} Point;

Point getVector(Point& A, Point& B) {
    //return AB vector
    Point vec = {B.x - A.x, B.y - A.y};
    return vec;
}

int ccw(Point& v1, Point& v2) { //crossproduct btw v1 and v2 -> v1 x v2, get ccw
    ll value = v1.x * v2.y - v1.y * v2.x;
    if(value > 0) return 1;
    else if (value == 0) return 0;
    else return -1;
}
 
bool isInside(vector<Point>& Q, Point& P) {
    int left = 1;
    int right = Q.size() - 1;
    
    Point rVector = getVector(Q[0], Q[right]);
    Point lVector = getVector(Q[0], Q[left]);
    Point pVector = getVector(Q[0], P);

    if(ccw(rVector, pVector) > 0) return false; // p (r m l) 
    if(ccw(lVector, pVector) < 0) return false; // (r m l) p

    while(left + 1 < right) {
        int mid = (left + right) / 2;

        Point mVector = getVector(Q[0], Q[mid]);

        if(ccw(mVector, pVector) > 0) left = mid;
        else right = mid;
    }

    Point lpVector = getVector(Q[left], P);
    Point prVector = getVector(P, Q[right]);

    return ccw(lpVector, prVector) < 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K; cin >> N >> M >> K;

    vector<Point> groupA(N);
    for(int i = 0; i < N; ++i) cin >> groupA[i].x >> groupA[i].y;
    vector<Point> groupB(M);
    for(int i = 0; i < M; ++i) cin >> groupB[i].x >> groupB[i].y;
    vector<Point> groupS(K);
    for(int i = 0; i < K; ++i) cin >> groupS[i].x >> groupS[i].y;

    int cnt = 0;
    for(int i = 0; i < K; ++i) {
        if(isInside(groupA, groupS[i]) == false || isInside(groupB, groupS[i]) == true) cnt++;
    }

    if(cnt == 0) cout << "YES";
    else cout << cnt;

    return 0;
}