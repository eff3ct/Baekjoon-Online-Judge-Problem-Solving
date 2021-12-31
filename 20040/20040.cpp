#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int find(int a, vector<int>& parent) {
    if(a == parent[a]) return a;
    return parent[a] = find(parent[a], parent);
}

void uni(int a, int b, vector<int>& parent) {
    int aP = find(a, parent);
    int bP = find(b, parent);

    if(aP == bP) return;

    if(aP < bP) parent[bP] = aP;
    else parent[aP] = bP;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0);

    int ret = 0;
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;

        if(find(u, parent) == find(v, parent)) {
            ret = i + 1;
            break;
        }

        uni(u, v, parent);
    }

    cout << ret;

    return 0;
}