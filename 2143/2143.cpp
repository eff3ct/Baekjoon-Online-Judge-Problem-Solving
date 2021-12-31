#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
    ll T; cin >> T;

    int n; cin >> n;
    vector<ll> vec_n(n);
    for(int i = 0; i < n; ++i) cin >> vec_n[i];

    int m; cin >> m;
    vector<ll> vec_m(m);
    for(int i = 0; i < m; ++i) cin >> vec_m[i];

    vector<ll> partial_sum_n(n * (n + 1) / 2);
    vector<ll> partial_sum_m(m * (m + 1) / 2);

    int idx = 0;
    for(int i = 0; i < n; ++i) {
        ll tmp = 0;
        for(int j = i; j < n; ++j) {
            tmp += vec_n[j];
            partial_sum_n[idx] = tmp;
            idx++;
        }
    }

    idx = 0;
    for(int i = 0; i < m; ++i) {
        ll tmp = 0;
        for(int j = i; j < m; ++j) {
            tmp += vec_m[j];
            partial_sum_m[idx] = tmp;
            idx++;
        }
    }

    sort(partial_sum_m.begin(), partial_sum_m.end());

    ll ret = 0;
    for(int i = 0; i < n * (n + 1) / 2; ++i) {
        ll lb = lower_bound(partial_sum_m.begin(), partial_sum_m.end(), T - partial_sum_n[i]) - partial_sum_m.begin();
        ll ub = upper_bound(partial_sum_m.begin(), partial_sum_m.end(), T - partial_sum_n[i]) - partial_sum_m.begin();
        ret += ub - lb;
    }
    
    cout << ret;

    return 0;
}