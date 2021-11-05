#include <iostream>
#include <vector>
#define MOD 1000000000

using namespace std;

vector<vector<int>> dp;

int solve(int number, int length) {
    if(number < 0 || number > 9) return 0;

    int& ret = dp[number][length];
    if(ret != -1) return ret;

    if(length == 1) return ret = 1;

    return ret = (solve(number + 1, length - 1) + solve(number - 1, length - 1)) % MOD;
}

int main() {
    int N; cin >> N;

    dp.resize(10, vector<int>(N + 1, -1));
    int ret = 0;
    for(int i = 1; i <= 9; ++i) {
        ret = (ret + solve(i, N)) % MOD;
    }

    cout << ret;

    return 0;
}