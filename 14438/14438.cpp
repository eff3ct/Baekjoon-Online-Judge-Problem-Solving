// https://www.acmicpc.net/problem/14438 //
#include <iostream>
#include <vector>
#define INF 1987654321

using namespace std;

class segTree {
    private:
        vector<int> tree;

    public: 
        segTree(int N) {
            tree.resize(N * 4);
        }

        int init(vector<int>& A, int start, int end, int node) {
            if(start == end) return tree[node] = A[start];

            int mid = (start + end) / 2;

            return tree[node] = min(init(A, start, mid, node * 2), init(A, mid + 1, end, node * 2 + 1));
        }

        void update(int start, int end, int node, int idx, int change) {
            if(start > idx || end < idx) return;

            if(start == end) {
                tree[node] = change;
                return;
            }

            int mid = (start + end) / 2;
            update(start, mid, node * 2, idx, change);
            update(mid + 1, end, node * 2 + 1, idx, change);
            tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        }

        int query(int start, int end, int node, int left, int right) {
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

    vector<int> A(N + 1);
    for(int i = 1; i <= N; ++i) cin >> A[i];

    segTree Tree(N);
    Tree.init(A, 1, N, 1);

    int M; cin >> M;

    for(int i = 0; i < M; ++i) {
        int cmd, b, c; cin >> cmd >> b >> c;
        if(cmd & 1) Tree.update(1, N, 1, b, c);
        else cout << Tree.query(1, N, 1, b, c) << '\n';
    }   

    return 0;
}