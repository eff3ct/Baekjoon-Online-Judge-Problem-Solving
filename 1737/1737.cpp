#include <iostream>
#include <cmath>
#include <map>

typedef long long ll;
using namespace std;

const double PI = acos(-1);
const ll MOD = 1e18;
map<double, ll> dp;

ll solve(double n) {
    if(0 <= n && n <= PI) return 1;

    if(dp[n] != 0) return dp[n];

    else return dp[n] = (solve(n - 1) + solve(n - PI)) % MOD;
}

int main() {
    int n; cin >> n;

    cout << solve(n) % MOD;

    return 0;
}