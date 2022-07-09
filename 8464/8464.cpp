#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll mobius[1010101];

void get_mobius() {
    mobius[1] = 1;
    for(int i = 1; i < 1010101; ++i) {
        for(int j = 2 * i; j < 1010101; j += i) {
            mobius[j] -= mobius[i];
        }
    }
}

ll solve(ll K) {
    ll left = 0, right = 1e11;

    while(left + 1 < right) {
        ll mid = (left + right) / 2;

        ll cnt = 0;
        for(ll i = 1; i * i <= mid; ++i) cnt += mobius[i] * (mid / (i * i));
        
        cnt = mid - cnt;

        if(cnt >= K) right = mid;
        else left = mid;
    }

    return right;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll K; cin >> K;
    
    get_mobius();
    cout << solve(K) << '\n';

    return 0;
}