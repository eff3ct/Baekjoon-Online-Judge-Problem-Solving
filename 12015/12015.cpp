// https://www.acmicpc.net/problem/12015 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class segTree {
    private:
        vector<int> tree;

    public:
        segTree(int N) {
            tree.resize(N + 1);
        }

        void update(int start, int end, int node, int idx, int value) {
            if(idx < start || idx > end) return;

            int mid = (start + end) / 2;

            if(start != end) {
                update(start, mid, node * 2, idx, value);
                update(mid + 1, end, node * 2 + 1, idx, value);
                tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
            }
            else tree[node] = value;
        }

        int query(int start, int end, int node, int left, int right) {
            if(right < start || left > end) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;
            return max(query(start, mid, node * 2, left, right), 
            query(mid + 1, end, node * 2 + 1, left, right));
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    
    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    int maxEle = *max_element(A.begin(), A.end());
    segTree Tree(4000000);

    int res = 0;

    for(int i = 0; i < N; ++i) {
        int current = Tree.query(1, maxEle, 1, 1, A[i] - 1);
        res = max(res, current + 1);
        Tree.update(1, maxEle, 1, A[i], current + 1);
    }

    cout << res;

    return 0;
}