#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
typedef long long ll;

int N, K;

void solve(vector<pair<int, int>>& jewelry, vector<int>& backpack) {
    ll ret = 0;
    priority_queue<int> pq;
    
    sort(jewelry.begin(), jewelry.end());
    sort(backpack.begin(), backpack.end());

    int idx = 0;
    for(int i = 0; i < K; ++i) {
        while(idx < N && jewelry[idx].first <= backpack[i]) pq.push(jewelry[idx++].second);

        if(!pq.empty()) {
            ret += (ll)pq.top();
            pq.pop();
        }        
    }

    cout << ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> K;

    vector<pair<int, int>> jewelry(N); //weight cost
    for(int i = 0; i < N; ++i) cin >> jewelry[i].first >> jewelry[i].second;

    vector<int> backpack(K);
    for(int i = 0; i < K; ++i) cin >> backpack[i];

    solve(jewelry, backpack);

    return 0;
}