#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vector<pii> seq(n);
    for(int i = 0; i < n; ++i) {
        cin >> seq[i].first;
        seq[i].second = i;
    }

    sort(seq.begin(), seq.end());

    vector<pii> ret(seq);
    
    int val = n;
    for(int i = n; i > 0; --i) {
        pii x = {i, -1};
        auto lb = lower_bound(seq.begin(), seq.end(), x);
        if(lb == seq.end()) continue;
        else {
            int idx = lb - seq.begin();
            for(int i = idx; i < n; ++i) {
                ret[i].first = val--;
                if(i == n - 1 || seq[i].first != seq[i + 1].first) break;
            }
        }
    }

    sort(ret.begin(), ret.end(), [&](const pii& a, const pii& b) {
        return a.second < b.second;
    });

    for(int i = 0; i < n; ++i) 
        cout << ret[i].first << ' ';

    return 0;
}