#include <bits/stdc++.h>
#define MAX 100'001

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int N, K; 
ll height[MAX];
ll A[MAX];
ll B[MAX];

const ll INF = 1e18;

class segment_tree {
    private:
        vector<ll> tree;
        vector<ll> lazy;

    public:
        segment_tree() = default;

        segment_tree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        void resize(int N) {
            tree.resize(N * 4);
            tree.resize(N * 4);
        }

        void propagate(int start, int end, int node) {
            if(lazy[node] == 0) return;

            tree[node] += (ll)(end - start + 1) * lazy[node];

            if(start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }

            lazy[node] = 0;
        }

        void update(int start, int end, int node, int left, int right, ll diff) {
            propagate(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] += (ll)(end - start + 1) * diff;

                if(start != end) {
                    lazy[node * 2] += diff;
                    lazy[node * 2 + 1] += diff;
                }

                return;
            }

            int mid = (start + end) / 2;
            update(start, mid, node * 2, left, right, diff);
            update(mid + 1, end, node * 2 + 1, left, right, diff);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        ll query(int start, int end, int node, int left, int right) {
            propagate(start, end, node);

            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

void ternary_search(ll& ans, segment_tree& coeff, segment_tree& val) {
    int l = 1, r = 100'000;
    while(l + 4 < r) {
        int a = (2 * l + r) / 3;
        int b = (l + 2 * r) / 3;

        ll m = coeff.query(1, MAX, 1, a, a);
        ll n = val.query(1, MAX, 1, a, a);

        ll u = coeff.query(1, MAX, 1, b, b);
        ll v = val.query(1, MAX, 1, b, b);

        if(m * a + n > u * b + v) l = a;
        else r = b;
    }

    for(int j = l; j <= r; ++j) {
        ll m = coeff.query(1, MAX, 1, j, j);
        ll n = val.query(1, MAX, 1, j, j);
        ans = min(ans, m * j + n);
    }
}

ll solve() {
    segment_tree coeff(MAX);
    segment_tree val(MAX);

    for(int i = 1; i <= K; ++i) {
        coeff.update(1, MAX, 1, 1, height[i], -B[i]);
        val.update(1, MAX, 1, 1, height[i], B[i] * height[i]);

        coeff.update(1, MAX, 1, height[i] + 1, MAX, A[i]);
        val.update(1, MAX, 1, height[i] + 1, MAX, -A[i] * height[i]);
    }

    ll ret = INF;

    for(int i = K + 1; i <= N + 1; ++i) {
        ternary_search(ret, coeff, val);

        if(i == N + 1) break;

        //front
        coeff.update(1, MAX, 1, 1, height[i], -B[i]);
        val.update(1, MAX, 1, 1, height[i], B[i] * height[i]);

        coeff.update(1, MAX, 1, height[i] + 1, MAX, A[i]);
        val.update(1, MAX, 1, height[i] + 1, MAX, -A[i] * height[i]);

        //back
        int idx = i - K;
        coeff.update(1, MAX, 1, 1, height[idx], B[idx]);
        val.update(1, MAX, 1, 1, height[idx], -B[idx] * height[idx]);

        coeff.update(1, MAX, 1, height[idx] + 1, MAX, -A[idx]);
        val.update(1, MAX, 1, height[idx] + 1, MAX, A[idx] * height[idx]);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;

    for(int i = 1; i <= N; ++i) cin >> height[i];
    for(int i = 1; i <= N; ++i) cin >> A[i];
    for(int i = 1; i <= N; ++i) cin >> B[i];

    cout << solve() << '\n';

    return 0;
}