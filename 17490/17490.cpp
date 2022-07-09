#include <bits/stdc++.h>
#define MAX 1'010'101

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int parent[MAX];
ll cost[MAX];
ll N, M, K; 
const ll INF = 1e18;

int find(int a) {
    if(a == parent[a]) return a;
    else return parent[a] = find(parent[a]);
}

void uni(int a, int b) {
    int a_p = find(a);
    int b_p = find(b);

    if(a_p == b_p) return;

    if(a_p < b_p) {
        parent[b_p] = a_p;
        cost[a_p] = min(cost[a_p], cost[b_p]);
    }
    else {
        parent[a_p] = b_p;
        cost[b_p] = min(cost[a_p], cost[b_p]);
    }
}

string solve() {
    ll c = 0;

    for(int i = 1; i <= N; ++i) {
        if(find(i) != find(N + 1)) {
            c += cost[find(i)];
            uni(i, N + 1);
        }
    }

    if(c <= K) return "YES";
    else return "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    iota(parent, parent + MAX, 0);
    fill(cost, cost + MAX, INF);

    cin >> N >> M >> K;
    for(int i = 1; i <= N; ++i) cin >> cost[i];

    bool is_connected[MAX];
    fill(is_connected, is_connected + MAX, true);
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        if(a > b) swap(a, b);
        if(a + 1 != b) is_connected[N] = false;
        else is_connected[(a + b) / 2] = false;
    }

    if(M <= 1) {
        cout << "YES\n";
        return 0;
    }

    for(int i = 1; i < N; ++i) if(is_connected[i]) uni(i, i + 1);
    if(is_connected[N]) uni(1, N);

    cout << solve() << '\n';

    return 0;
}