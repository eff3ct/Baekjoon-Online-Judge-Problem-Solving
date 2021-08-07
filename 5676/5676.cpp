// https://www.acmicpc.net/problem/5657 //
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

        int init(vector<int>& A, int start, int end, int node) {
            if(start == end) {
                if(A[start] > 0) return tree[node] = 1;
                else if(A[start] < 0) return tree[node] = -1;
                else return tree[node] = 0;
            }

            int mid = (int)(start + end) / 2;

            return tree[node] = init(A, start, mid, node * 2) * init(A, mid + 1, end, node * 2 + 1);
        }

        int getSign(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 1;
            if(left <= start && end <= right) return tree[node];

            int mid = (int)(start + end) / 2;

            return getSign(start, mid, node * 2, left, right) * getSign(mid + 1, end, node * 2 + 1, left, right);
        }

        void update(int start, int end, int idx, int node, int changed) {
            if(idx < start || idx > end) return;

            if(start != end) {
                int mid = (int)(start + end) / 2;
                update(start, mid, idx, node * 2, changed);
                update(mid + 1, end, idx, node * 2 + 1, changed);
            }
            else {
                tree[node] = changed;
                node /= 2;
                while(node > 0) {
                    tree[node] = tree[node * 2] * tree[node * 2 + 1];
                    node /= 2;
                } 
            }
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N, K;

    while(cin >> N >> K) {
        vector<int> A(N);
        for(int i = 0; i < N; ++i) cin >> A[i];

        segTree Tree(N);
        Tree.init(A, 0, N - 1, 1);

        for(int i = 0; i < K; ++i) {
            char cmd; cin >> cmd;
            if(cmd == 'C') {
                int a, b; cin >> a >> b;
                
                int changed;
                if(b > 0) changed = 1;
                else if(b < 0) changed = -1;
                else changed = 0;

                Tree.update(0, N - 1, a - 1, 1, changed);
            }

            else {
                int a, b; cin >> a >> b;
                int sign = Tree.getSign(0, N - 1, 1, a - 1, b - 1);
                
                if(sign > 0) cout << '+';
                else if(sign < 0) cout << '-';
                else cout << 0;
            }
        }
        cout << '\n';
    }

    return 0;
}