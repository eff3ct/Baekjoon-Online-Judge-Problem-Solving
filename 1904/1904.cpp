#include <iostream>
#include <vector>
#define MOD 15746

using namespace std;

int main() {
    int N; cin >> N;

    vector<int> dp(1000001);
    dp[1] = 1;
    dp[2] = 2;

    for(int i = 3; i <= N; ++i) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    }

    cout << dp[N];
}