// https://www.acmicpc.net/problem/14427 //
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class segTree {
    private:
        vector<ll> tree;

    public:
        segTree(int N) {
            tree.resize(N * 4);
        }

        ll init(vector<ll>& A, int start, int end, int node) {
            if(start == end) return tree[node] = start;

            int mid = (int)(start + end) / 2;

            ll left = init(A, start, mid, node * 2);
            ll right = init(A, mid + 1, end, node * 2 + 1);

            if(A[left] > A[right]) return tree[node] = right;
            else if(A[left] < A[right]) return tree[node] = left;
            else return tree[node] = min(left, right);
        }

        ll minIdx(vector<ll>& A, int start, int end, int left, int right, int node) {
            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (int)(start + end) / 2;

            ll L = minIdx(A, start, mid, left, right, node * 2);
            ll R = minIdx(A, mid + 1, end, left, right, node * 2 + 1);

            if(A[L] > A[R]) return R;
            else if(A[L] < A[R]) return L;
            else return min(L, R);
        }

        void update(vector<ll>& A, int start, int end, int idx, int node) {
            if(idx < start || idx > end) return;

            if(start != end) {
                int mid = (int)(start + end) / 2;
                update(A, start, mid, idx, node * 2);
                update(A, mid + 1, end, idx, node * 2 + 1);

                if(A[tree[node * 2]] > A[tree[node * 2 + 1]]) tree[node] = tree[node * 2 + 1];
                else if(A[tree[node * 2] < A[tree[node * 2 + 1]]]) tree[node] = tree[node * 2];
                else tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
            }
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<ll> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    segTree Tree(N);
    Tree.init(A, 0, N - 1, 1);

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            int a, b; cin >> a >> b;
            A[a - 1] = b;
            Tree.update(A, 0, N - 1, a - 1, 1);
        }
        else cout << Tree.minIdx(A, 0, N - 1, 0, N - 1, 1) + 1 << '\n';
    }

    return 0;
}