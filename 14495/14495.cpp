#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
    int n; cin >> n;

    vector<ll> dp(117);
    dp[1] = dp[2] = dp[3] = 1;
    for(int i = 4; i <= n; ++i) dp[i] = dp[i - 1] + dp[i - 3];
    cout << dp[n];

    return 0;
}
