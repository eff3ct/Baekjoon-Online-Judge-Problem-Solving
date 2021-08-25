// https://www.acmicpc.net/problem/1280 //
#include <iostream>
#include <vector>
#include <algorithm>
#define MOD 1000000007LL

using namespace std;
typedef long long ll;

class segTree {
    private:
        vector<ll> cntTree;
        vector<ll> valTree;
    
    public:
        segTree(int N) {
            cntTree.resize(N * 4);
            valTree.resize(N * 4);
        }

        ll cntQuery(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return cntTree[node];

            int mid = (start + end) / 2;
            return cntQuery(start, mid, node * 2, left, right) + cntQuery(mid + 1, end, node * 2 + 1, left, right);
        }

        void cntUpdate(int start, int end, int node, int idx) {
            if(start > idx || end < idx) return;

            cntTree[node] += 1;

            if(start != end) {
                int mid = (start + end) / 2;
                cntUpdate(start, mid, node * 2, idx);
                cntUpdate(mid + 1, end, node * 2 + 1, idx);
            }
        }

        ll valQuery(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return valTree[node];

            int mid = (start + end) / 2;
            return valQuery(start, mid, node * 2, left, right) + valQuery(mid + 1, end, node * 2 + 1, left, right);
        }

        void valUpdate(int start, int end, int node, int idx, ll diff) {
            if(start > idx || end < idx) return;

            valTree[node] += diff;

            if(start != end) {
                int mid = (start + end) / 2;
                valUpdate(start, mid, node * 2, idx, diff);
                valUpdate(mid + 1, end, node * 2 + 1, idx, diff);
            }
        } 
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    const int maxValue = 200000;

    segTree Tree(maxValue);

    int N; cin >> N;

    ll ret = 1;
    ll now; cin >> now;
    Tree.cntUpdate(0, maxValue, 1, now);
    Tree.valUpdate(0, maxValue, 1, now, now);
    for(int i = 0; i < N - 1; ++i) {
        cin >> now;
        ll a = Tree.cntQuery(0, maxValue, 1, 0, now);
        ll b = Tree.cntQuery(0, maxValue, 1, now + 1, maxValue);
        ll aSum = Tree.valQuery(0, maxValue, 1, 0, now);
        ll bSum = Tree.valQuery(0, maxValue, 1, now + 1, maxValue);

        ll x = a * now - aSum + bSum - b * now;

        ret = ((x % MOD) * ret) % MOD;

        Tree.cntUpdate(0, maxValue, 1, now);
        Tree.valUpdate(0, maxValue, 1, now, now);
    }

    cout << ret;
    return 0;
}