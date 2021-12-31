#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int find(int a, vector<int>& parent) {
    if(a == parent[a]) return a;
    else return parent[a] = find(parent[a], parent);
}

void uni(int a, int b, vector<int>& parent) {
    int a_parent = find(a, parent);
    int b_parent = find(b, parent);

    if(a_parent == b_parent) return;
    
    if(a_parent < b_parent) parent[b_parent] = a_parent;
    else parent[a_parent] = b_parent;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int G, P; cin >> G >> P;

    vector<int> parent(G + 1);
    iota(parent.begin(), parent.end(), 0);

    vector<bool> visit(G + 1, false);

    vector<int> plane(P);
    for(int& e : plane) cin >> e;

    int cnt = 0;
    for(int i = 0; i < P; ++i) {
        int x = find(plane[i], parent);
        if(visit[x] || x == 0) break;
        visit[x] = true;
        cnt++;
        uni(x, x - 1, parent);
    }

    cout << cnt;

    return 0;
}