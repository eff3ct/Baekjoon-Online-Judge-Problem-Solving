// https://www.acmicpc.net/problem/11660 //
#include <iostream>
#include <vector>

using namespace std;

vector<int> map[1025];
int dp[1025][1025];

void solve(int x1, int y1, int x2, int y2) {
    cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    
    for(int x = 1; x <= N; ++x) {
        map[x].push_back(-1);
        for(int y = 1; y <= N; ++y) {
            int tmp; cin >> tmp;
            map[x].push_back(tmp);
        }
    }

    for(int i = 0; i <= N; ++i) {
        dp[i][0] = 0;
        dp[0][i] = 0;
    }

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            int summation = 0;
            for(int n = 1; n <= i; ++n) {
                summation += map[n][j];
            }
            dp[i][j] = dp[i][j - 1] + summation;
        }
    }

    for(int i = 0; i < M; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        solve(x1, y1, x2, y2);
    }

    return 0;
}