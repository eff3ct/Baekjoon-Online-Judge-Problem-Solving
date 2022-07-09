#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll INF = 123456789876LL;

class segment_tree {
    private:
        vector<ll> tree;
        vector<ll> lazy;

    public:
        segment_tree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        void propagate(int start, int end, int node) {
            if(lazy[node] == 0) return;

            tree[node] += lazy[node];

            if(start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }

            lazy[node] = 0;
        }

        void update(int start, int end, int node, int left, int right, ll val) {
            propagate(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] += val;
                
                if(start != end) {
                    lazy[node * 2] += val;
                    lazy[node * 2 + 1] += val;
                }

                return;
            }

            int mid = (start + end) / 2;

            update(start, mid, node * 2, left, right, val);
            update(mid + 1, end, node * 2 + 1, left, right, val);
            tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        }

        ll query(int start, int end, int node, int left, int right) {
            propagate(start, end, node);

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

    string S; cin >> S;
    int N = int(S.size());
    int M; cin >> M;

    segment_tree Tree(N);
    ll s = 0;
    for(int i = 1; i <= N; ++i) {
        s = s + (S[i - 1] == '(' ? 1 : -1);
        Tree.update(1, N, 1, i, i, s);
    }

    ll cnt = 0;

/*     auto f = [&]() {
        for(int i = 1; i <= N; ++i) {
            cout << Tree.query(1, N, 1, i, i) << ' ';
        }
        cout << '\n';
    }; */

    while(M --> 0) {
        int index; cin >> index;
        S[index - 1] = (S[index - 1] == '(' ? ')' : '(');
        Tree.update(1, N, 1, index, N, (S[index - 1] == '(' ? 2 : -2));
        ll val = Tree.query(1, N, 1, 1, N);
        if(S[0] == ')' || Tree.query(1, N, 1, N, N) != 0 || val < 0) continue;
        else cnt++;
    }   

    cout << cnt << '\n';

    return 0;
}