// https://www.acmicpc.net/problem/9663 //
#include <iostream>
#include <vector>

using namespace std;

long long res = 0;
vector<pair<int, int>> queen;

bool isValid(int x, int y) {
    for(int i = 0; i < queen.size(); ++i) {
        int nowX = queen[i].first;
        int nowY = queen[i].second;
        if(x == nowX || y == nowY || (y - x) == (nowY - nowX) || (y + x) == (nowY + nowX)) return false;
    }
    return true;
}

void solve(int& N, int y) {
    if(y == N) {
        res += 1;
        return;
    } //base

    for(int x = 0; x < N; ++x) {
        if(!isValid(x, y)) continue; 
        queen.push_back({x, y});
        solve(N, y + 1);
        queen.pop_back();
    }
    
}

int main() {
    int N; cin >> N;

    solve(N, 0);

    cout << res;

    return 0;
}