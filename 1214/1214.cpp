#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    register ll D, P, Q; cin >> D >> P >> Q;
    if(P < Q) swap(P, Q);
    register ll ret = INT_MAX;

    for(register ll i = 0; i <= ceil((double)D / P) + 1; ++i) {
        register ll r = D - P * i;
        if(r <= 0) {
            if(ret == P * i) break;
            ret = min(ret, P * i); 
        }
        else {
            if(ret == P * i + Q * (ll)ceil((double)r / Q)) break;
            ret = min(ret, P * i + Q * (ll)ceil((double)r / Q));
        }
    }

    cout << ret << '\n';

    return 0;
}