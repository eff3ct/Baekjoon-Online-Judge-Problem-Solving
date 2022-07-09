#include <bits/stdc++.h>
#define MAX 100'001
#define INF 987654321

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

class segment_tree {
    private:
        vector<ll> tree;
        vector<ll> lazy;

    public:
        segment_tree() = default;

        segment_tree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        void resize(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        void propagate(int start, int end, int node) {
            if(lazy[node] == 0) return;

            tree[node] += (ll)(end - start + 1) * lazy[node];

            if(start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }

            lazy[node] = 0;
        }

        void update(int start, int end, int node, int left, int right, ll diff) {
            propagate(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] += (ll)(end - start + 1) * diff;

                if(start != end) {
                    lazy[node * 2] += diff;
                    lazy[node * 2 + 1] += diff;
                }

                return;
            }

            int mid = (start + end) / 2;

            update(start, mid, node * 2, left, right, diff);
            update(mid + 1, end, node * 2 + 1, left, right, diff);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        ll query(int start, int end, int node, int left, int right) {
            propagate(start, end, node);

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

        void update(int a, int b) {
            while(top_chain[a] != top_chain[b]) {
                if(depth[top_chain[a]] < depth[top_chain[b]]) swap(a, b);
                int v = top_chain[a];
                tree.update(1, MAX, 1, in[v], in[a], 1LL);
                a = parent[v];                
            }

            if(depth[a] > depth[b]) swap(a, b);
            tree.update(1, MAX, 1, in[a] + 1, in[b], 1LL);
        }

        ll query(int a, int b) {
            ll ret = 0;
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
        char cmd;
        int u, v;
        cin >> cmd >> u >> v;
        if(cmd == 'P') hld.update(u, v);
        else cout << hld.query(u, v) << '\n';
    }

    return 0;
}