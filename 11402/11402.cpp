#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

/* 

Lukas Theorem

nCk is congruent to product i = 0 to m (n_i)C(k_i) about mod p

where,
n = n_m*p^m + n_(m - 1)*p^(m - 1) + ... + n_0
k = k_m*p^m + k_(m - 1)*p^(m - 1) + ... + k_0

*/

ll combination(ll N, ll K, ll M, vector<vector<ll>>& dp) {
    if(N < K) return 0;

    ll& ret = dp[N][K];

    if(ret != -1) return ret;
    if(N == K || K == 0) return ret = 1; //base case

    return ret = (combination(N - 1, K - 1, M, dp) + combination(N - 1, K, M, dp)) % M;
}

int main() {
    ll N, K, M; cin >> N >> K >> M;

    vector<vector<ll>> dp(M + 1, vector<ll>(M + 1, -1));

    ll ret = 1;
    while(N || K) {
        ret = (ret * combination(N % M, K % M, M, dp)) % M;
        N /= M; K /= M;
    }

    cout << ret % M;

    return 0;
}