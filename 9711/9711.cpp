#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

ll solve(ll P, ll Q) {
    if(Q == 1) return 0;

    vector<ll> dp(10001);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    for(int i = 3; i <= P; ++i) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % Q;
    }

    return dp[P];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    int cnt = 0;
    while(T --> 0) {
        ll P, Q; cin >> P >> Q;
        cout << "Case #" << ++cnt << ": " << solve(P, Q) << '\n';
    }

    return 0;
}   