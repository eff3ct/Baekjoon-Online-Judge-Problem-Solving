#include <bits/stdc++.h>
#define MAX 501010

using namespace std;
using ll = unsigned int;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

class segment_tree {
    private:
        vector<ll> tree;
        vector<ll> lazy_add;
        vector<ll> lazy_prod;

    public:
        segment_tree() = default;

        segment_tree(int N) {
            tree.resize(N * 4);
            lazy_add.resize(N * 4);
            lazy_prod.resize(N * 4, 1);
        }

        void resize(int N) {
            tree.resize(N * 4);
            lazy_add.resize(N * 4);
            lazy_prod.resize(N * 4, 1);
        }

        void propagate_add(int start, int end, int node) {
            if(lazy_add[node] == 0) return;

            tree[node] += (ll)(end - start + 1) * lazy_add[node];

            if(start != end) {
                lazy_add[node * 2] += lazy_add[node];
                lazy_add[node * 2 + 1] += lazy_add[node];
            }

            lazy_add[node] = 0;
        }

        void propagate_prod(int start, int end, int node) {
            if(lazy_prod[node] == 1) return;

            tree[node] *= lazy_prod[node];

            if(start != end) {
                lazy_prod[node * 2] *= lazy_prod[node];
                lazy_prod[node * 2 + 1] *= lazy_prod[node];
                lazy_add[node * 2] *= lazy_prod[node];
                lazy_add[node * 2 + 1] *= lazy_prod[node];
            }

            lazy_prod[node] = 1;
        }

        void update_plus(int start, int end, int node, int left, int right, ll diff) {
            propagate_prod(start, end, node);
            propagate_add(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] += (ll)(end - start + 1) * diff;

                if(start != end) {
                    lazy_add[node * 2] += diff;
                    lazy_add[node * 2 + 1] += diff;
                }

                return;
            }

            int mid = (start + end) / 2;

            update_plus(start, mid, node * 2, left, right, diff);
            update_plus(mid + 1, end, node * 2 + 1, left, right, diff);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        void update_product(int start, int end, int node, int left, int right, ll v) {
            propagate_prod(start, end, node);
            propagate_add(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] *= v;

                if(start != end) {
                    lazy_prod[node * 2] *= v;
                    lazy_prod[node * 2 + 1] *= v;
                    lazy_add[node * 2] *= v;
                    lazy_add[node * 2 + 1] *= v;
                }

                return;
            }

            int mid = (start + end) / 2;

            update_product(start, mid, node * 2, left, right, v);
            update_product(mid + 1, end, node * 2 + 1, left, right, v);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        ll query(int start, int end, int node, int left, int right) {
            propagate_prod(start, end, node);
            propagate_add(start, end, node);

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

            for(int i = 0; i < N - 1; ++i) {
                int u, v; cin >> u >> v;
                adj[u].push_back(v);
                adj[v].push_back(u);
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

        void update_subtree_plus(int x, ll v) {
            tree.update_plus(1, MAX, 1, in[x], out[x], v);
        }

        void update_path_plus(int x, int y, ll v) {
            while(top_chain[x] != top_chain[y]) {
                if(depth[top_chain[x]] < depth[top_chain[y]]) swap(x, y);
                int k = top_chain[x];
                tree.update_plus(1, MAX, 1, in[k], in[x], v);
                x = parent[k];
            }

            if(depth[x] > depth[y]) swap(x, y);
            tree.update_plus(1, MAX, 1, in[x], in[y], v);
        }

        void update_subtree_product(int x, ll v) {
            tree.update_product(1, MAX, 1, in[x], out[x], v);
        }

        void update_path_product(int x, int y, ll v) {
            while(top_chain[x] != top_chain[y]) {
                if(depth[top_chain[x]] < depth[top_chain[y]]) swap(x, y);
                int k = top_chain[x];
                tree.update_product(1, MAX, 1, in[k], in[x], v);
                x = parent[k];
            }

            if(depth[x] > depth[y]) swap(x, y);
            tree.update_product(1, MAX, 1, in[x], in[y], v);
        }

        ll query_path(int a, int b) {
            ll ret = 0;
            while(top_chain[a] != top_chain[b]) {
                if(depth[top_chain[a]] < depth[top_chain[b]]) swap(a, b);
                int v = top_chain[a];
                ret += tree.query(1, MAX, 1, in[v], in[a]);
                a = parent[v];                
            }

            if(depth[a] > depth[b]) swap(a, b);
            ret += tree.query(1, MAX, 1, in[a], in[b]);

            return ret;
        }

        ll query_subtree(int x) {
            return tree.query(1, MAX, 1, in[x], out[x]);
        }

        void print() {
            cout << "\n\n";
            cout << in[1] << ' ' << out[1] << '\n';
            cout << "??";
            for(int i = 1; i <= 5; ++i) {
                cout << tree.query(1, MAX, 1, in[i], in[i]) << '\n';
            }
            cout << "??\n\n";
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    heavy_light_decomposition hld;
    hld.init();

    while(hld.Q --> 0) {
        int cmd; cin >> cmd;
        ll x, y, v;
        switch(cmd) {
            case 1:
                cin >> x >> v;
                hld.update_subtree_plus(x, v);
                break;
            case 2:
                cin >> x >> y >> v;
                hld.update_path_plus(x, y, v);
                break;
            case 3:
                cin >> x >> v;
                hld.update_subtree_product(x, v);
                break;
            case 4:
                cin >> x >> y >> v;
                hld.update_path_product(x, y, v);
                break;
            case 5:
                cin >> x;
                cout << hld.query_subtree(x) << '\n';
                break;
            case 6:
                ll x, y; cin >> x >> y;
                cout << hld.query_path(x, y) << '\n';
                break;
        }
    }

    return 0;
}