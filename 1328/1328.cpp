#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
typedef long long ll;

ll dp[101][101][101];
ll MOD = 1e9 + 7;

ll count(int N, int L, int R) {
    //base case
    if(N == 1 && L == 1 && R == 1) return 1;
    else if(N == 0) return 0;

    ll& ret = dp[N][L][R];

    if(ret != -1) return ret;

    return ret = (count(N - 1, L, R) * (N - 2) % MOD + count(N - 1, L - 1, R) % MOD + count(N - 1, L, R - 1) % MOD) % MOD;
}

int main() {
    int N, L, R; cin >> N >> L >> R;

    for(int i = 0; i <= 100; ++i) {
        for(int j = 0; j <= 100; ++j) {
            memset(dp[i][j], -1, 101 * sizeof(ll));
        }
    }

    cout << count(N, L, R) % MOD << '\n';

    return 0;
}