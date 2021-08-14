// https://www.acmicpc.net/problem/3653 //
#include <iostream>
#include <vector>

using namespace std;

class segTree {
    private:
        vector<int> tree;

    public:
        segTree(int N) {
            tree.resize(N * 4);
        }

        int init(int start, int end, int node) {
            if(start == end) return tree[node] = 1;

            int mid = (start + end) / 2;

            return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
        }

        int query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right)
            + query(mid + 1, end, node * 2 + 1, left, right);
        }

        void update(int start, int end, int node, int idx) {
            if(start > idx || end < idx) return;

            tree[node] -= 1;

            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx);
                update(mid + 1, end, node * 2 + 1, idx);
            }
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    while(T--) {
        int n, m; cin >> n >> m;

        segTree Tree(n + m);
        Tree.init(1, n + m, 1);
        int lb = m + 1;

        vector<int> loc(n + 1);
        for(int i = 1; i <= n; ++i) loc[i] = m + i;

        vector<int> res;
        for(int i = 0; i < m; ++i) {
            int dvd; cin >> dvd;
            res.push_back(Tree.query(1, n + m, 1, lb, loc[dvd] - 1));
            Tree.update(1, n + m, 1, loc[dvd]);
            loc[dvd] = --lb;
        }

        for(auto& element : res) cout << element << " ";
        cout << '\n';
    }

    return 0;
}