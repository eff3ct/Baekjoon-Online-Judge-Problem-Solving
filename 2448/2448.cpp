// https://www.acmicpc.net/problem/2448 //
#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> baseTriangle =
{
    {' ', ' ', '*', ' ', ' '},
    {' ', '*', ' ', '*', ' '},
    {'*', '*', '*', '*', '*'} 
};

void solve(int N, int x, int y, vector<vector<char>>& map) {
    if(N == 3) {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 5; ++j) {
                map[y + i][x - 2 + j] = baseTriangle[i][j];
            }
        }
        return;
    }

    solve(N / 2, x, y, map);
    solve(N / 2, x - N / 2, y + N / 2, map);
    solve(N / 2, x + N / 2, y + N / 2, map); 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<vector<char>> map(N, vector<char>(2 * N - 1, ' '));

    solve(N, N - 1, 0, map);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < 2 * N - 1; ++j) {
            cout << map[i][j];
        }
        cout << '\n';
    }

    return 0;
}