#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

vector<ll> prefix_sum;

ll count(ll N) {
    ll ret = N & 1;
    
    ll idx = 54;
    while(idx > 0) {
        if(N & (1LL << idx)) {
            ret += prefix_sum[idx - 1] + (N - (1LL << idx)) + 1;
            N -= 1LL << idx;
        }
        idx--;
    }

    return ret;
}

int main() {
    ll A, B; cin >> A >> B;

    prefix_sum.resize(55);

    prefix_sum[0] = 1;
    for(ll i = 1; i <= 54; ++i) prefix_sum[i] = prefix_sum[i - 1] * 2 + (1LL << i);

    cout << count(B) - count(A - 1);
    
    return 0;
}