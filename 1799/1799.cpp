#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> bishop;
int ret;
int N; 

bool check(int x, int y) {
    for(auto& B : bishop) {
        if(y + x == B.second + B.first || y - x == B.second - B.first) return false;
    }
    return true;
}

void solve(vector<vector<int>>& map, int x, int y) {
    ret = max(ret, (int)bishop.size());

    if(x >= N) {
        x = (x & 1) ? 0 : 1;
        y++;
    }

    if(y == N) return;

   
    if(map[y][x] == 1 && check(x, y)) {
        bishop.push_back({x, y});
        solve(map, x + 2, y);
        bishop.pop_back();
    }
    solve(map, x + 2, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    vector<vector<int>> map(N, vector<int>(N));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> map[i][j];
        }
    }

    solve(map, 0, 0);
    int result = ret;

    ret = 0;
    solve(map, 1, 0);
    result += ret;
   
    cout << result;

    return 0;
}