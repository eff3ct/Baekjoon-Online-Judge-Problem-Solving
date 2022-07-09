#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ppll = pair<ll, pair<ll, ll>>;

const ll INF = 123456789876LL;

class segment_tree {
    private:
        vector<ll> tree;

    public:
        segment_tree(int N) {
            tree.resize(N * 4);
        }

        void update(int start, int end, int node, int idx, ll val) {
            if(start > idx || idx > end) return;
            
            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx, val);
                update(mid + 1, end, node * 2 + 1, idx, val);
                tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
            }
            else tree[node] = val;
        }

        ll query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return INF;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;
            return min(query(start, mid, node * 2, left, right), query(mid + 1, end, node * 2 + 1, left, right));
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<ppll> seq(N + 1);

    for(int i = 1; i <= N; ++i) {
        int x; cin >> x;
        seq[x].first = i;
    }
    for(int i = 1; i <= N; ++i) {
        int x; cin >> x;
        seq[x].second.first = i;
    }
    for(int i = 1; i <= N; ++i) {
        int x; cin >> x;
        seq[x].second.second = i;
    }

    sort(seq.begin() + 1, seq.end());

    segment_tree Tree(N);
    for(int i = 1; i <= N; ++i) Tree.update(1, N, 1, i, INF);

    ll ans = 0;
    for(int i = 1; i <= N; ++i) {
        ll idx = seq[i].second.first;
        ll upd = seq[i].second.second;

        Tree.update(1, N, 1, idx, upd);
        if(Tree.query(1, N, 1, 1, idx - 1) > upd) ans++;
    }

    cout << ans << '\n';

    return 0;
}