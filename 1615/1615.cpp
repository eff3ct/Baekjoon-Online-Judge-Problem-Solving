// https://www.acmicpc.net/problem/1615 //
#include <iostream>
#include <utility>
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

        ll query(int start, int end, int node, int left, int right) {
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

    int N, M;
    cin >> N >> M;

    segTree Tree(N);

    vector<pair<int, int>> seq(M);
    for(int i = 0; i < M; ++i) cin >> seq[i].first >> seq[i].second;

    sort(seq.begin(), seq.end());

    ll ret = 0;
    for(int i = 0; i < M; ++i) {
        int x = seq[i].second;
        ret += Tree.query(1, N, 1, x + 1, N);
        Tree.update(1, N, 1, x);
    }

    cout << ret;

    return 0;
}