#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD = 20200429LL;

ll power(ll a, ll b) {
    if(b == 0) return 1;

    if(b & 1) return ((a % MOD) * (power(a, b - 1) % MOD)) % MOD;
    else {
        ll tmp = power(a, b / 2) % MOD;
        return (tmp * tmp) % MOD;
    }
}

int main() {
    int idx = -1;
    int gap = MOD - 1;
    for(ll i = 60; i <= 128; ++i) {
        ll n_gap = 20200402 - power(i, 814);
        if(n_gap >= 0 && n_gap < gap) {
            idx = i;
            gap = n_gap;
        }
    }
    cout << gap << '\n';
    printf("%c\n", idx);
    cout << idx << '\n';

    return 0;
}