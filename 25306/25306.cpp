#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll f(ll x) {
    ll c = (1LL << 62LL);

    ll ret = 0;
    while(c > 2) {
        ll r = (x % c);
        ll cnt = max(0LL, r - c / 2 + 1);
        if(cnt & 1) ret ^= 1;
        ret <<= 1;
        c >>= 1;
    }
    
    if(x % 4 == 1 || x % 4 == 2) ret ^= 1;

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll A, B; cin >> A >> B;
    ll ans = f(A - 1) ^ f(B);
    cout << ans << '\n';

    return 0;
}