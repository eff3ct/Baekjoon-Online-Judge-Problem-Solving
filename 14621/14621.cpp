#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

struct edge {
    int u, v, w;
    bool operator<(const edge& x) const {
        return w < x.w;
    }
    bool operator>(const edge& x) const {
        return w > x.w;
    }
};

int find(int a, vector<int>& p) {
    if(a == p[a]) return a;
    else return p[a] = find(p[a], p);
}

void uni(int a, int b, vector<int>& p) {
    int ap = find(a, p);
    int bp = find(b, p);
    
    if(ap == bp) return;
    if(ap < bp) p[bp] = ap;
    else p[ap] = bp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<int> parent(N + 1);
    iota(parent.begin(), parent.end(), 0);

    vector<bool> sex(N + 1, false);
    for(int i = 1; i <= N; ++i) {
        char cmd; cin >> cmd;
        sex[i] = (cmd == 'M');
    }

    priority_queue<edge, vector<edge>, greater<edge>> pq;
    for(int i = 0; i < M; ++i) {
        int u, v, d; cin >> u >> v >> d;
        if(sex[u] == sex[v]) continue;
        pq.push({u, v, d});
    }

    int ret = 0;
    while(!pq.empty()) {
        auto e = pq.top();
        pq.pop();

        if(find(e.u, parent) != find(e.v, parent)) {
            uni(e.u, e.v, parent);
            ret += e.w;
        } 
    }

    for(int i = 1; i <= N; ++i) {
        if(find(i, parent) != find(1, parent)) {
            cout << -1;
            return 0;
        }
    }

    cout << ret;

    return 0;
}