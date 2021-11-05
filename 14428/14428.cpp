#include <iostream>
#include <vector>
#include <utility>

#define INF 1987654321

using namespace std;
typedef pair<int, int> pii;

class segTree {
    private:
        vector<pii> tree;

    public:
        segTree(int N) {
            tree.resize(N * 4, {INF, INF});
        }

        void update(int node, int start, int end, int idx, int diff) {
            if(start > idx || idx > end) return;

            if(start != end) {
                int mid = (start + end) / 2;
    
                update(node * 2, start, mid, idx, diff);
                update(node * 2 + 1, mid + 1, end, idx, diff);

                tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
            }
            else tree[node] = {diff, idx};
        }

        pii query(int node, int start, int end, int left, int right) {
            if(start > right || end < left) return {INF, INF};

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;
            return min(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    segTree tree(N);

    for(int i = 1; i <= N; ++i) {
        int ai; cin >> ai;
        tree.update(1, 1, N, i, ai);
    }

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int cmd, a, b; cin >> cmd >> a >> b;
        if(cmd == 1) tree.update(1, 1, N, a, b);
        else cout << tree.query(1, 1, N, a, b).second << '\n';
    }    

    return 0;
}