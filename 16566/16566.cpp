#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K; cin >> N >> M >> K;

    vector<int> data(M);
    vector<bool> is_used(N + 1, false);

    for(int i = 0; i < M; ++i) cin >> data[i];

    sort(data.begin(), data.end());

    for(int i = 0; i < K; ++i) {
        int chulsu; cin >> chulsu;
        int idx = upper_bound(data.begin(), data.end(), chulsu) - data.begin();
        
        while(idx < M - 1 && is_used[data[idx]]) idx++;

        cout << data[idx] << '\n';
        is_used[data[idx]] = true;
    }

    return 0;
}