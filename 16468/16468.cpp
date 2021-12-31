#include <iostream>
#include <vector>
#define MOD 100030001LL

typedef long long ll;
using namespace std;

vector<vector<ll>> dp;

ll tree(int height, int count) {
    if(count == 0) return 1;
    if(height == 0) return 0;

    ll& ret = dp[height][count];

    if(ret != -1) return ret;

    ret = 0;
    for(int i = 0; i <= count - 1; ++i) {
        ret += tree(height - 1, i) * tree(height - 1, count - 1 - i);
        ret %= MOD;
    }

    return ret;
}

int main() {
    int N, L; cin >> N >> L;

    dp.resize(301, vector<ll>(301, -1));

    cout << (tree(L, N) - tree(L - 1, N) + MOD) % MOD << '\n';

    return 0;
}