#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;

map<ll, ll> dp;

ll solve(ll N, ll P, ll Q) {
    if(dp.find(N) != dp.end()) return dp[N];
    
    ll value = solve(N / P, P, Q) + solve(N / Q, P, Q);
    dp.insert({N, value});

    return value;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll N, P, Q; cin >> N >> P >> Q;
    dp.insert({0, 1});
    cout << solve(N, P, Q);
    return 0;
}