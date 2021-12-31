#include <iostream>
#include <utility>
#include <vector>

using namespace std;

bool isSite(vector<pair<int, int>>& site, int x, int y) {
    for(auto& coord : site) if(coord.first - 1 == x && coord.second - 1 == y) return true;
    return false;
}

int main() {
    int a, b; cin >> a >> b;

    int n; cin >> n;
    vector<pair<int, int>> site(n);
    for(int i = 0; i < n; ++i) cin >> site[i].first >> site[i].second;

    vector<vector<int>> dp(a, vector<int>(b));

    dp[0][0] = 1;
    for(int y = 0; y < b; ++y) {
        for(int x = 0; x < a; ++x) {
            if(isSite(site, x, y)) continue;

            if(x == 0 && y > 0) dp[x][y] = dp[x][y - 1];
            else if(x > 0 && y == 0) dp[x][y] = dp[x - 1][y];
            else if(x > 0 && y > 0) dp[x][y] = dp[x - 1][y] + dp[x][y - 1];
        }
    }

    cout << dp[a - 1][b - 1];

    return 0;
}