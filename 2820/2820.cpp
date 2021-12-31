#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> subCount;

class segTree {
    private:
        vector<int> tree;
        vector<int> lazy;

    public:
        segTree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }        

        void propagate(int start, int end, int node) {
            if(lazy[node] == 0) return;

            tree[node] += (end - start + 1) * lazy[node];

            if(start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }

            lazy[node] = 0;
        }

        void updateRange(int start, int end, int node, int left, int right, int diff) {
            propagate(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                lazy[node] = diff;
                propagate(start, end, node);
                return;
            }

            int mid = (start + end) / 2;
            updateRange(start, mid, node * 2, left, right, diff);
            updateRange(mid + 1, end, node * 2 + 1, left, right, diff);

            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        int query(int start, int end, int node, int left, int right) {
            propagate(start, end, node);

            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) 
            + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

void DFS(int node, vector<vector<int>>& adj) {
    static int id = 0;

    subCount[node].first = ++id;

    for(auto& element : adj[node]) DFS(element, adj);

    subCount[node].second = id;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, M; cin >> N >> M;

    subCount.resize(N + 1);

    vector<vector<int>> adj(N + 1);
    vector<int> seq(N + 1);

    cin >> seq[1];
    for(int i = 2; i <= N; ++i) {
        cin >> seq[i];
        
        int parent; cin >> parent;
        adj[parent].push_back(i);
    }

    DFS(1, adj);

    segTree Tree(N);
    for(int i = 1; i <= N; ++i) {
        Tree.updateRange(1, N, 1, subCount[i].first, subCount[i].first, seq[i]);
    }

    for(int i = 0; i < M; ++i) {
        char cmd; cin >> cmd;
        if(cmd == 'p') {
            int a, diff; cin >> a >> diff;
            if(subCount[a].first != subCount[a].second)
                Tree.updateRange(1, N, 1, subCount[a].first + 1, subCount[a].second, diff);
        }
        else {
            int a; cin >> a;
            cout << Tree.query(1, N, 1, subCount[a].first, subCount[a].first) << '\n';
        }
    }

    return 0;
}