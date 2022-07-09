#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long ll;

vector<ll> prime_list = { 2, 7, 61 };

ll pow_mod(ll a, ll b, ll M) {
    if(b == 0) return 1;

    ll temp = pow_mod(a, b / 2, M);

    if(b & 1) return (((temp % M) * (temp % M)) % M * (a % M)) % M;
    else return ((temp % M) * (temp % M)) % M;
}

bool miller_rabin(ll x) {
    if(x < 2) return false;

    bool ret = true;
    for(auto& p : prime_list) {
        if(x == p) return true;
        ll k = x - 1;
        while(true) {
            ll val = pow_mod(p, k, x) % x;
            if(val == x - 1) {
                ret = true;
                break;
            }

            if(k & 1) {
                ret = (val == 1 || val == x - 1);
                break;
            }
        
            k /= 2;
        }

        if(!ret) break;
    }

    return ret;
}

int main() {
    int N; cin >> N;

    int cnt = 0;
    while(N --> 0) {
        ll A; cin >> A;
        if(miller_rabin(2 * A + 1)) cnt++;
    }

    cout << cnt;

    return 0;
}