//#pragma GCC optimize ("Ofast")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,avx,avx2")

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ordered_set pbds_set;
    int N; cin >> N;
    while(N --> 0) {
        int T, X; cin >> T >> X;
        if(T == 1) pbds_set.insert(X);
        else {
            auto it = pbds_set.find_by_order(X - 1);
            cout << *it << '\n';
            pbds_set.erase(it);
        }
    }

    return 0;
}