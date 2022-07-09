#include <bits/stdc++.h>
#define MAX 50'001

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

vector<int> adj[MAX];
bool vst[MAX];
int rnk[MAX];
int N;

vector<int> dfs_rank(int cur = 1) {
    vector<int> ret;

    for(int& next : adj[cur]) {
        if(vst[next]) continue;
        vst[next] = true;
        vector<int> tmp = dfs_rank(next);
        ret.insert(ret.begin(), tmp.begin(), tmp.end());
    }

    sort(ret.begin(), ret.end());
    int db = -1;
    for(int i = 0; i < (int)ret.size() - 1; ++i) {
        if(ret[i] == ret[i + 1]) db = max(db, ret[i]);
    }
    if(db != -1) {
        for(int i = 1; i <= db; ++i) ret.push_back(i);
    }
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());

    bool flag = false;
    int r = 1; 
    for(auto it = ret.begin(); it != ret.end(); ++it, ++r) {
        if(*it != r) {
            rnk[cur] = r;
            ret.erase(ret.begin(), it);
            ret.insert(ret.begin(), r);
            flag = true;
            break;
        }
    }

    if(!flag) {
        ret = {r};
        rnk[cur] = r;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i = 0; i < N - 1; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vst[1] = true;
    dfs_rank();

    int ans = *max_element(rnk, rnk + MAX);
    cout << ans - 1 << '\n';

    return 0;
}