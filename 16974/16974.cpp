#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

class segment_tree {
    private:
        vector<ll> tree;
    
    public:
        segment_tree(int N) {
            tree.resize(N * 4);
        }

        void update(int start, int end, int node, int idx, ll diff) {
            
        }

        ll query(int start, int end, int node, int left, int right) {

        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    return 0;
}