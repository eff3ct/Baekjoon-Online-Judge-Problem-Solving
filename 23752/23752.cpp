#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll mod_pow(ll x, ll n, const ll& mod) {
    if(n == 0) return 1 % mod;
    if(n & 1) return ((x % mod) * (mod_pow(x, n - 1, mod) % mod)) % mod;
    else {
        ll tmp = mod_pow(x, n / 2, mod) % mod;
        return (tmp * tmp) % mod;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll N, Q, P; cin >> N >> Q >> P;
    while(Q --> 0) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            ll x, y, z; cin >> x >> y >> z;
            if(P < x || P > y || x == y) continue;
            if(((y - x + 1) % 2) == 0) y--;
            if(P > y) continue;
            ll length = (y - x + 1);
            P = x + (((P - x) % length) * (mod_pow(2, z, length) % length)) % length;
        }
        else {
            ll x; cin >> x;
            if(P > x) P -= x;
            else P += N - x;
        }
    }

    cout << P << '\n';

    return 0;
}