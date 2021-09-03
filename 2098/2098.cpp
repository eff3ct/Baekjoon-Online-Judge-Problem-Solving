#include <iostream>
#include <vector>
#include <algorithm>
#define INF 987654321

using namespace std;

int N; 
int solve(int nowNode, int visit, vector<vector<int>>& dist, vector<vector<int>>& dp) {
    if(visit == ((1 << N) - 1)) {
        if(dist[nowNode][0] != 0) return dist[nowNode][0];
        else return INF;
    }

    if(dp[nowNode][visit] != -1) return dp[nowNode][visit];
    dp[nowNode][visit] = INF;

    for(int nextNode = 0; nextNode < N; ++nextNode) {
        if(visit & (1 << nextNode)) continue;
        if(dist[nowNode][nextNode] == 0) continue;
        dp[nowNode][visit] = min(dp[nowNode][visit], dist[nowNode][nextNode] + solve(nextNode, (visit | (1 << nextNode)), dist, dp));
    }

    return dp[nowNode][visit];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    vector<vector<int>> dist(N, vector<int>(N));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> dist[i][j];
        }
    }

    vector<vector<int>> dp(N, vector<int>(1 << N, -1));
    cout << solve(0, 1, dist, dp);

    return 0;
}