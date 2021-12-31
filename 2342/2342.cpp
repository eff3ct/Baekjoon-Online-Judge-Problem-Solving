#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<vector<int>>> dp(5, vector<vector<int>>(5, vector<int>(100001, -1)));

int cost(int a, int b) {
    if(a == 0) return 2;
    else if(abs(a - b) == 0) return 1;
    else if(abs(a - b) == 2) return 4;
    else return 3;
}

int solve(int a, int b, int idx, vector<int>& seq) {
    if(seq[idx] == 0) return 0;

    int& ret = dp[a][b][idx];

    if(ret != -1) return ret;

    return ret = min(solve(seq[idx], b, idx + 1, seq) + cost(a, seq[idx]),
    solve(a, seq[idx], idx + 1, seq) + cost(b, seq[idx]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> seq(100001);
    int idx = 0;
    while(true) {
        int n; cin >> n;
        if(n == 0) break;
        seq[idx++] = n;
    }

    cout << solve(0, 0, 0, seq);

    return 0;
}