// https://www.acmicpc.net/problem/2517 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class segTree {
    private:
        vector<int> tree;
    
    public:
        segTree(int N) {
            tree.resize(N * 4);
        }

        int query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right)
            + query(mid + 1, end, node * 2 + 1, left, right);
        }

        void update(int start, int end, int node, int idx) {
            if(idx < start || idx > end) return;

            tree[node] += 1;

            int mid = (start + end) / 2;

            if(start != end) {
                update(start, mid, node * 2, idx);
                update(mid + 1, end, node * 2 + 1, idx);
            }
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    segTree Tree(N);

    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    vector<int> sortedSeq(seq);
    sort(sortedSeq.begin(), sortedSeq.end());

    for(int i = 0; i < N; ++i) {
        int x = 1 + lower_bound(sortedSeq.begin(), sortedSeq.end(), seq[i]) - sortedSeq.begin();
        cout << 1 + Tree.query(1, N, 1, x + 1, N) << '\n';
        Tree.update(1, N, 1, x);
    }

    return 0;
}