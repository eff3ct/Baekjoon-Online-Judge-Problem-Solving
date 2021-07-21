// https://www.acmicpc.net/problem/9465 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximum = 0;

int solve(vector<int> (&sticker)[2], vector<int>*& dp, int stat, int level, int& n) {
    if(level == n) return 0;
    if(dp[level][stat] != -1) return dp[level][stat];

    int res = solve(sticker, dp, 0, level + 1, n);
    if(stat != 1) res = max(res, sticker[1][level] + solve(sticker, dp, 1, level + 1, n));
    if(stat != 2) res = max(res, sticker[0][level] + solve(sticker, dp, 2, level + 1, n));

    dp[level][stat] = res;

    return res;
}

int main() {
    int T; cin >> T;
    for(int testCase = 0; testCase < T; ++testCase) {
        int n; cin >> n;

        vector<int> sticker[2];
        vector<int>* dp = new vector<int>[n];

        for(int i = 0; i < n; ++i) {
            int x; cin >> x;
            sticker[0].push_back(x);
            dp[i].push_back(-1); dp[i].push_back(-1); dp[i].push_back(-1);
        }
        for(int i = 0; i < n; ++i) {
            int x; cin >> x;
            sticker[1].push_back(x);
        }
        cout << solve(sticker, dp, 0, 0, n) << "\n";

        delete[] dp;
    }
    return 0;
}