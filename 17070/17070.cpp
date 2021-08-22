// https://www.acmicpc.net/problem/17070 //
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> map;
int N;

bool isNotWall(int x, int y) {
    if(x < 0 || x >= N || y < 0 || y >= N) return false;
    if(map[y][x] == 1) return false;
    else return true;
}

bool isValid(int x, int y) {
    if(0 <= x && x < N && 0 <= y && y < N) return true;
    else return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    map.resize(N);
    for(int i = 0; i < N; ++i) map[i].resize(N);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> map[i][j];
        }
    }

    vector<vector<vector<int>>> dp(3, vector<vector<int>>(N, vector<int>(N))); //dp[status][y][x]
    dp[2][0][1] = 1; //base
    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < N; ++x) {
            for(int k = 0; k < 3; ++k) {
                if(k == 0 && isNotWall(x, y) && isValid(x, y - 1)) 
                    dp[0][y][x] = dp[0][y - 1][x] + dp[1][y - 1][x] ;

                else if(k == 1 && isNotWall(x, y) && isNotWall(x - 1, y) && isNotWall(x, y - 1) && isValid(x - 1, y - 1))
                    dp[1][y][x] = dp[0][y - 1][x-1] + dp[1][y - 1][x - 1] + dp[2][y - 1][x-1];

                else if(k == 2 && isNotWall(x, y) && isValid(x - 1, y)) {
                    if(x == 1 && y == 0) continue; //skip base
                    dp[2][y][x] = dp[1][y][x - 1] + dp[2][y][x - 1];
                }
            }
        }
    }

    cout << dp[0][N - 1][N - 1] + dp[1][N - 1][N - 1] + dp[2][N - 1][N - 1];

    return 0;
}