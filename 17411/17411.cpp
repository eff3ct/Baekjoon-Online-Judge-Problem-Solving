#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#define MOD 1000000007

using namespace std;
typedef pair<int, int> pii;

pii comp(const pii& A, const pii& B) {
    if(A.first == B.first) return {A.first, (A.second + B.second) % MOD}; //if length is same, return summation
    else return A < B ? B : A; //return longer one
}

class segTree {
    private:
        vector<pii> tree;

    public:
        segTree(int N) {
            tree.resize(N * 4);
        }

        void update(int start, int end, int node, int idx, pii val) {
            if(start > idx || idx > end) return;

            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx, val);
                update(mid + 1, end, node * 2 + 1, idx, val);
                tree[node] = comp(tree[node * 2], tree[node * 2 + 1]);
            }
            else tree[node] = comp(tree[node], val);
        }

        pii query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return {0, 0};

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return comp(query(start, mid, node * 2, left, right), query(mid + 1, end, node * 2 + 1, left, right));
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];
    vector<int> order(seq);
    sort(order.begin(), order.end());
    order.erase(unique(order.begin(), order.end()), order.end()); //delete overlapped number
    
    segTree Tree(N);

    Tree.update(0, N, 1, 0, {0, 1});
    for(int i = 0; i < N; ++i) {
        int now = lower_bound(order.begin(), order.end(), seq[i]) - order.begin() + 1;
        pii x = Tree.query(0, N, 1, 0, now - 1);
        x.first++;
        Tree.update(0, N, 1, now, x);
    }

    pii ret = Tree.query(0, N, 1, 0, N);

    cout << ret.first << " " << ret.second;

    return 0;
}