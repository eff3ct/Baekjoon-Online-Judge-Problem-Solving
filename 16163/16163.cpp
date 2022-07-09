#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll solve(string& str) {
    vector<int> dp(str.size(), 0);
    int r = 0, p = 0;
    for(int i = 0; i < (int)str.length(); ++i) {
        if(i <= r) dp[i] = min(dp[2 * p - i], r - i);
        else dp[i] = 0;

        while(i - dp[i] - 1 >= 0 && i + dp[i] + 1 < (int)str.length() 
        && str[i - dp[i] - 1] == str[i + dp[i] + 1]) dp[i]++;

        if(r < i + dp[i]) {
            r = i + dp[i];
            p = i;
        }
    }

    ll ret = 0;
    for(int i = 0; i < (int)dp.size(); ++i) ret += (ll)(dp[i] + 1) / 2LL;
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string S; cin >> S;
    string X = "@";
    for(int i = 0; i < (int)S.length(); ++i) {
        X += S[i], X += "@";
    }

    cout << solve(X) << '\n';

    return 0;
}