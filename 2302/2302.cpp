#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

const ll MOD = 2e9;

int main() {
    vector<ll> dp(41);
    dp[0] = 1, dp[1] = 1;
    for(int i = 2; i <= 40; ++i) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    }

    int N, M; cin >> N >> M;
    ll ret = 1;

    int fixed = 0;
    for(int i = 0; i < M; ++i) {
        int temp; cin >> temp;
        int count = temp - fixed - 1;
        fixed = temp;
        ret *= dp[count];
        ret %= MOD;
    }
    ret *= dp[N - fixed];
    ret %= MOD;

    cout << ret;

    return 0;
}