#include <bits/stdc++.h>
#define MAX 100'001

using namespace std;
typedef long long ll;

class segment_tree {
    private:
        vector<ll> tree;
        vector<ll> lazy;

    public:
        segment_tree(int N) {
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

int group_cnt;
int in[MAX];
int out[MAX];
vector<int> adj[MAX];

void DFS(int cur = 1) {
    in[cur] = ++group_cnt;
    for(auto& next : adj[cur]) {
        DFS(next);
    }
    out[cur] = group_cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    int x; cin >> x;
    for(int i = 2; i <= N; ++i) {
        cin >> x;
        adj[x].push_back(i);
    }

    segment_tree tree(N);

    DFS();

    while(M --> 0) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            ll i, w; cin >> i >> w;
            tree.update(1, N, 1, in[i], out[i], w);
        }
        else {
            ll i; cin >> i;
            cout << tree.query(1, N, 1, in[i], in[i]) << '\n';
        }
    }

    return 0;
}