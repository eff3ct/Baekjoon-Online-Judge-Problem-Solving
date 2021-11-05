#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
    int N; cin >> N;
    vector<ll> dp(31);

    dp[0] = 1;
    dp[1] = 0;
    dp[2] = 3;
    dp[3] = 0;
    dp[4] = 11;

    for(int i = 5; i <= N; ++i) {
        dp[i] = 3 * dp[i - 2];
        for(int j = i - 4; j >= 0; j -= 2) dp[i] += 2 * dp[j];
    }

    cout << dp[N];

    return 0;
}