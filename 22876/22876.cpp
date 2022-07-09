#include <bits/stdc++.h>
#define MAX 1'000'001

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ppii = pair<int, pii>;

const ll INF = -1e18;

class segment_tree {
    private:
        vector<pll> tree;

    public:
        segment_tree() = default;

        segment_tree(int N) {
            tree.resize(N * 4);
        }

        void resize(int N) {
            tree.resize(N * 4);
        }

        void update(int start, int end, int node, int idx, ll diff) {
            if(idx < start || end < idx) return;

            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx, diff);
                update(mid + 1, end, node * 2 + 1, idx, diff);

                ll tmp[4] = {tree[node * 2].first, tree[node * 2].second, tree[node * 2 + 1].first, tree[node * 2 + 1].second};
                sort(tmp, tmp + 4, greater<int>());

                tree[node] = {tmp[0], tmp[1]};
            }
            else tree[node] = {tree[node].first + diff, -INF};
        }

        pll query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return {-INF, -INF};

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            pll l = query(start, mid, node * 2, left, right);
            pll r = query(mid + 1, end, node * 2 + 1, left, right);

            ll tmp[4] = {l.first, l.second, r.first, r.second};
            sort(tmp, tmp + 4, greater<ll>());

            return {tmp[0], tmp[1]};
        }
};

ll solve(vector<ll>& x_sum, vector<ll>& y_sum, vector<pll>* x_coord, vector<pll>* y_coord) {
    ll ret = 0;
    //x * 3, y * 3
    vector<ll> tmp_x(x_sum);
    vector<ll> tmp_y(y_sum);
    sort(tmp_x.rbegin(), tmp_x.rend());
    sort(tmp_y.rbegin(), tmp_y.rend());
    ret = max(tmp_x[0] + tmp_x[1] + tmp_x[2], tmp_y[0] + tmp_y[1] + tmp_y[2]);

    //x * 2, y * 1
    segment_tree x_tree(MAX);
    for(int i = 0; i < MAX; ++i) 
        x_tree.update(0, MAX, 1, i, x_sum[i]);
    
    for(int i = 0; i < MAX; ++i) {
        ll val = y_sum[i];
        for(pll& upd_coord : y_coord[i]) 
            x_tree.update(0, MAX, 1, upd_coord.first, -upd_coord.second);

        pll x_max_values = x_tree.query(0, MAX, 1, 0, MAX);
        val += x_max_values.first + x_max_values.second;

        for(pll& upd_coord : y_coord[i]) 
            x_tree.update(0, MAX, 1, upd_coord.first, upd_coord.second);

        ret = max(ret, val);
    }

    //x * 1, y * 2
    segment_tree y_tree(MAX);
    for(int i = 0; i < MAX; ++i) 
        y_tree.update(0, MAX, 1, i, y_sum[i]);
    
    for(int i = 0; i < MAX; ++i) {
        ll val = x_sum[i];
        for(pll& upd_coord : x_coord[i]) 
            y_tree.update(0, MAX, 1, upd_coord.first, -upd_coord.second);

        pll y_max_values = y_tree.query(0, MAX, 1, 0, MAX);
        val += y_max_values.first + y_max_values.second;

        for(pll& upd_coord : x_coord[i]) 
            y_tree.update(0, MAX, 1, upd_coord.first, upd_coord.second);

        ret = max(ret, val);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<ll> x_sum(MAX);
    vector<ll> y_sum(MAX);

    vector<pll> x_coord[MAX];
    vector<pll> y_coord[MAX];

    for(int i = 0; i < N; ++i) {
        ll x, y, v; cin >> x >> y >> v;
        x_sum[x] += v;
        y_sum[y] += v;

        x_coord[x].push_back({y, v});
        y_coord[y].push_back({x, v});
    }

    cout << solve(x_sum, y_sum, x_coord, y_coord) << '\n';

    return 0;
}