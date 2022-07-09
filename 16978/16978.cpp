#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pil = pair<int, ll>;

class segment_tree {
    private:
        vector<ll> tree;

    public:
        segment_tree(int N) {
            tree.resize(N * 4);
        }

        void update(int start, int end, int node, int idx, ll val) {
            if(idx < start || end < idx) return;

            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx, val);
                update(mid + 1, end, node * 2 + 1, idx, val);
                tree[node] = tree[node * 2] + tree[node * 2 + 1];
            }
            else tree[node] = val;
        }

        ll query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

struct query {
    int idx, k, i, j;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    segment_tree tree(N);
    for(int i = 1; i <= N; ++i) {
        ll x; cin >> x;
        tree.update(1, N, 1, i, x);
    }

    int M; cin >> M;
    vector<pil> change_query;
    vector<query> sum_query;
    vector<ll> ans;

    int cnt = 0;
    for(int i = 0; i < M; ++i) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            pil q; cin >> q.first >> q.second;
            change_query.push_back(q);
        }
        else {
            query q; cin >> q.k >> q.i >> q.j;
            q.idx = cnt++;
            sum_query.push_back(q);
        }
    }

    ans.resize(cnt);

    sort(sum_query.begin(), sum_query.end(), [&](const query& a, const query& b) {
        return a.k < b.k;
    });

    int prev = 0;
    for(int t = 0; t < (int)sum_query.size(); ++t) {
        int now = sum_query[t].k;
        for(int x = prev + 1; x <= now; ++x) {
            tree.update(1, N, 1, change_query[x - 1].first, change_query[x - 1].second);
            prev = now;
        }
        ans[sum_query[t].idx] = tree.query(1, N, 1, sum_query[t].i, sum_query[t].j);
    }

    for(int i = 0; i < (int)ans.size(); ++i) cout << ans[i] << '\n';

    return 0; 
}