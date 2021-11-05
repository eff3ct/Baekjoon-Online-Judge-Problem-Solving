#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> wine(n);
    for(int i = 0; i < n; ++i) cin >> wine[i];

    if(n >= 3) {
        vector<int> dp(10001);
        dp[0] = wine[0];
        dp[1] = wine[0] + wine[1];
        dp[2] = max({wine[0] + wine[1], wine[1] + wine[2], wine[0] + wine[2]});

        for(int i = 3; i < n; ++i) {
            dp[i] = max(dp[i - 3] + wine[i - 1] + wine[i], dp[i - 2] + wine[i]);
            dp[i] = max(dp[i], dp[i - 1]);
        }

        cout << dp[n - 1];
    }
    else if(n == 2) cout << wine[0] + wine[1];
    else if(n == 1) cout << wine[0];

    return 0;
}