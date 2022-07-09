#include <bits/stdc++.h>
#define MAX 202020

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

class segment_tree {
    private:
        vector<ll> tree;

    public:
        segment_tree() = default;

        segment_tree(int N) {
            tree.resize(N * 4);
        }

        void resize(int N) {
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

class heavy_light_decomposition {
    private:
        int group_cnt;
        int tree_size[MAX], depth[MAX], parent[MAX], top_chain[MAX], in[MAX], out[MAX];
        bool visit[MAX];
        vector<int> child[MAX];
        vector<int> adj[MAX];
        segment_tree tree;

    public:
        int Q;
        void init() {
            group_cnt = 0;

            int N; cin >> N >> Q;
            tree.resize(MAX);

            for(int i = 1; i <= N - 1; ++i) {
                int a; cin >> a;
                adj[i + 1].push_back(a);
                adj[a].push_back(i + 1);
            }

            dfs_child_set();
            dfs_size();
            dfs_grouping();
        }

        void dfs_child_set(int v = 1) {
            visit[v] = true;
            for(auto& next : adj[v]) {
                if(visit[next]) continue;
                visit[next] = true;
                child[v].push_back(next);
                dfs_child_set(next);
            }
        }

        void dfs_size(int v = 1) {
            tree_size[v] = 1;
            for(auto& next : child[v]) {
                depth[next] = depth[v] + 1;
                parent[next] = v;

                dfs_size(next);
                tree_size[v] += tree_size[next];
                if(tree_size[next] > tree_size[child[v][0]]) swap(child[v][0], next);
            }
        }

        void dfs_grouping(int v = 1) {
            in[v] = ++group_cnt;
            for(auto& next : child[v]) {
                top_chain[next] = (next == child[v][0] ? top_chain[v] : next);
                dfs_grouping(next);
            }
            out[v] = group_cnt;
        }

        void update(int v, int w) {
            tree.update(1, MAX, 1, in[v], w);
        }

        int query(int a, int b) {
            int ret = 0;
            while(top_chain[a] != top_chain[b]) {
                if(depth[top_chain[a]] < depth[top_chain[b]]) swap(a, b);
                int v = top_chain[a];
                ret += tree.query(1, MAX, 1, in[v], in[a]);
                a = parent[v];                
            }

            if(depth[a] > depth[b]) swap(a, b);
            ret += tree.query(1, MAX, 1, in[a] + 1, in[b]);

            return ret;
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    heavy_light_decomposition hld;
    hld.init();

    while(hld.Q --> 0) {
        int b, c, d; cin >> b >> c >> d;
        if(d == 0) {
            ll q = hld.query(b, c);
            if(q == 0) cout << "YES\n";
            else cout << "NO\n";
        }
        else {
            ll q = hld.query(b, c);
            if(q == 0) {
                cout << "YES\n";
                hld.update(b, -1);
            }
            else {
                cout << "NO\n";
                hld.update(c, -1);
            }
        }
    }

    return 0;
}