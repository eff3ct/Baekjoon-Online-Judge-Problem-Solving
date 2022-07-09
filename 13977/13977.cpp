#include <bits/stdc++.h>
#define MAX 4'000'001

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

const ll MOD = 1e9 + 7;

ll mod_pow(ll x, ll n) {
    if(n == 0) return 1;
    if(n & 1) return ((x % MOD) * (mod_pow(x, n - 1) % MOD)) % MOD;
    else {
        ll tmp = mod_pow(x, n / 2) % MOD;
        return (tmp * tmp) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll factorial[MAX];
    int M; cin >> M;
    factorial[0] = 1;
    for(int i = 1; i < MAX; ++i) factorial[i] = ((factorial[i - 1] % MOD) * (i % MOD)) % MOD;

    while(M --> 0) {
        ll N, K; cin >> N >> K;
        ll x = factorial[N] % MOD;
        x = (x % MOD) * (mod_pow(factorial[K], MOD - 2) % MOD);
        x %= MOD;

        x = (x % MOD) * (mod_pow(factorial[N - K], MOD - 2) % MOD);
        x %= MOD;
        cout << x << '\n';
    }

    return 0;
}