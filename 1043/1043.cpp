// https://www.acmicpc.net/problem/1043 //
#include <iostream>
#include <vector>

using namespace std;

int find(vector<int>& parent, int a) {
    if(parent[a] == a) return a;
    else return parent[a] = find(parent, parent[a]);
}

void uni(vector<int>& parent, int a, int b) {
    int aP = find(parent, a);
    int bP = find(parent, b);

    if(aP == bP) return;

    if(aP > bP) parent[aP] = bP;
    else parent[bP] = aP;
}

int main() {
    int N, M; cin >> N >> M;

    vector<int> partyCounter(N + 1);
    vector<int> parent(N + 1);
    for(int i = 1; i <= N; ++i) parent[i] = i;
    
    int K; cin >> K;
    vector<int> truth(K);
    for(int i = 0; i < K; ++i) {
        cin >> truth[i];
        if(i != 0) uni(parent, truth[i - 1], truth[i]);
    }

    for(int i = 0; i < M; ++i) {
        int cnt; cin >> cnt;
        vector<int> party(cnt);
        for(int j = 0; j < cnt; ++j) {
            cin >> party[j];
            if(j != 0) uni(parent, party[j - 1], party[j]);
        }
        partyCounter[find(parent, party[0])] += 1;
    }

    int res = 0;
    for(int i = 1; i <= N; ++i) {
        if(truth.size() && find(parent, truth[0]) == find(parent, i)) continue;
        else res += partyCounter[i];
    }

    cout << res;

    return 0;
}