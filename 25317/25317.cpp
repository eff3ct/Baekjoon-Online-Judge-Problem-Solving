#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

#define ordered_set tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    set<ll> roots;
    ordered_set pbds_set;

    int k = 1;
    int Q; cin >> Q;
    while(Q --> 0) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            ll a, b; cin >> a >> b;
            if(a == 0 && b == 0) k = 0;
            else if(a == 0) k *= (b > 0 ? 1 : -1);
            else {
                k *= (a > 0 ? 1 : -1);
                pbds_set.insert(floor((long double)b / (long double)a));
                if(b % a == 0) roots.insert(b / a);
            }
        }
        else {
            ll c; cin >> c;
            if(roots.find(-c) != roots.end()) {
                cout << "0\n";
                continue;
            }

            ll x = k;
            ll cnt = pbds_set.order_of_key(-c);
            if(cnt & 1) x *= -1;
            
            if(x == 0) cout << "0\n";
            else if(x == 1) cout << "+\n";
            else cout << "-\n";
        }
    }

    return 0;
}