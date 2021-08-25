#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

class segTree {
    private:
        vector<ll> tree;
    
    public:
        segTree(int N) {
            tree.resize(N * 4);
        }

        int query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;
            return query(start, mid, node * 2, left, right) + query(mid + 1, end, node * 2 + 1, left, right);
        }

        void update(int start, int end, int node, int idx) {
            if(start > idx || end < idx) return;

            tree[node] += 1;

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

    int N; cin >> N;
    segTree Tree(N);

    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    vector<int> ori(seq);
    sort(seq.begin(), seq.end());

    ll ret = 0;
    for(int i = 0; i < N; ++i) {
        int compressed = lower_bound(seq.begin(), seq.end(), ori[i]) - seq.begin();
        ret += Tree.query(0, N - 1, 1, compressed + 1, N - 1);
        Tree.update(0, N - 1, 1, compressed);
    }

    cout << ret;
    return 0;
}