// https://www.acmicpc.net/problem/2230 //
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define INF 2000000001

using namespace std;

void solve(vector<int>& number, int& N, int& M) {
    if(M == 0) {
        cout << 0;
        return;
    }

    int nowDiff = 0, low = 0, high = 0, res = INF;
    while(true) {
        if(nowDiff >= M) nowDiff = number[high] - number[low++];
        else if(nowDiff < M && high == N) break;
        else nowDiff = number[high++] - number[low];

        if(nowDiff >= M) res = min(res, nowDiff);
    }
    
    cout << res;
}

int main() {
    int N, M; cin >> N >> M;

    vector<int> seq(N, 0);
    for(int i = 0; i < N; ++i) cin >> seq[i];
    sort(seq.begin(), seq.end());

    solve(seq, N, M);

    return 0;
}
