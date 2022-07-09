#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K; cin >> N >> K;
    vector<vector<int>> suffix_count(K + 1, vector<int>(K + 1));
    vector<int> tap(N, -1);

    vector<int> seq(K);
    for(int i = 0; i < K; ++i) cin >> seq[i];

    for(int i = K - 1; i >= 0; --i) {
        for(int n = 1; n <= K; ++n) {
            if(n == seq[i]) suffix_count[i][n] = suffix_count[i + 1][n] + 1;
            else suffix_count[i][n] = suffix_count[i + 1][n];
        }
    }

    int cnt = 0;
    for(int i = 0; i < K; ++i) {
        bool flag = false;
        //이미 꽂혀있는 경우 스킵
        for(int j = 0; j < N; ++j) {
            if(tap[j] == seq[i]) {
                flag = true;
                break;
            }
        }
        if(flag) continue;

        //꽂혀있지 않은 경우
        for(int j = 0; j < N; ++j) {
            if(tap[j] != -1) continue;
            else {
                tap[j] = seq[i];
                flag = true;
                break;
            }
        }

        //꽂았으면 스킵
        if(flag) continue;
        else {
            //그게 아닌 경우
            int idx = -1;
            for(int j = 0; j < N; ++j) {
                if(suffix_count[i][tap[j]] == 0) {
                    idx = j;
                    break;
                }
            }
            
            if(idx != -1) {
                cnt++;
                tap[idx] = seq[i];
            }
            else {
                int loc = -1;
                for(int j = 0; j < N; ++j) {
                    for(int k = i + 1; k < K; ++k) {
                        if(tap[j] == seq[k]) {
                            if(loc < k) {
                                loc = k;
                                idx = j;
                            }
                            break;
                        }
                    }
                }

                cnt++;
                tap[idx] = seq[i];
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}