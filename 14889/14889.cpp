#include <bits/stdc++.h>

using namespace std;

int ret = 987654321;
vector<vector<int>> v;
int N; 

void solve(int cnt, int now, vector<bool>& picked) {
    if(cnt == N / 2) {
        vector<int> temp_1, temp_2;
        for(int i = 0; i < N; ++i) {
            if(picked[i]) temp_1.push_back(i);
            else temp_2.push_back(i);
        }

        int s1 = 0;
        int s2 = 0;
        for(int i = 0; i < N / 2; ++i) {
            for(int j = i + 1; j < N / 2; ++j) {
                s1 += v[temp_1[i]][temp_1[j]] + v[temp_1[j]][temp_1[i]];
                s2 += v[temp_2[i]][temp_2[j]] + v[temp_2[j]][temp_2[i]];
            }
        }

        ret = min(ret, abs(s1 - s2));
        return;
    }

    for(int i = now + 1; i < N; ++i) {
        picked[i] = true;
        solve(cnt + 1, i, picked);
        picked[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    v.resize(N, vector<int>(N));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> v[i][j];
        }
    }

    vector<bool> picked(N, false);
    solve(0, -1, picked);

    cout << ret << '\n';

    return 0;
}