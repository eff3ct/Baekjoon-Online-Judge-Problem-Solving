#include <bits/stdc++.h>
#define MAX 200'001

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
            else tree[node] += val;
        }

        ll query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

vector<int> adj[MAX];
bool vst[MAX];
int in[MAX], out[MAX];
int group_cnt;
ll depth[MAX];

void DFS(int cur = 1, ll d = 1) {
    in[cur] = ++group_cnt;
    depth[cur] = d;
    for(auto& next : adj[cur]) {
        if(vst[next]) continue;
        vst[next] = true;
        DFS(next, d + 1);
    }
    out[cur] = group_cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, C; cin >> N >> C;
    for(int i = 0; i < N - 1; ++i) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vst[C] = true;
    DFS(C);

    segment_tree tree(N);

    int Q; cin >> Q;
    for(int i = 0; i < Q; ++i) {
        int cmd, A; cin >> cmd >> A;
        if(cmd == 1) tree.update(1, N, 1, in[A], 1);
        else cout << tree.query(1, N, 1, in[A], out[A]) * depth[A] << '\n';
    }

    return 0;
}