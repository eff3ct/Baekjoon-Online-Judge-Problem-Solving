#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int main() {
    ll H, x; cin >> H >> x;

    ll ret = 0;
    ll x_0 = x;
    for(int i = 0; i < H; ++i) {
        ll k; cin >> k;
        ret += (k % MOD) * (x % MOD);
        x *= x_0;
        ret %= MOD;
        x %= MOD;
    }

    cout << ret % MOD;
}