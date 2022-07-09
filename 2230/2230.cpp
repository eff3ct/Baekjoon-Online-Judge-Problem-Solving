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

    int left = 0, right = 0;
    int res = INF, diff = 0;

    while(right != N) {
        diff = number[right] - number[left];

        if(diff >= M) {
            res = min(res, diff);
            left++;
        }
        else right++;
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
