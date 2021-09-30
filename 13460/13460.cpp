#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;
typedef pair<int, int> pii;

int N, M;
int ret = 11;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void shiftPoint(vector<vector<char>>& map, pii& blue, pii& red, int dir) {
    pii points[2] = {blue, red};
    while(true) {
        bool isMoved = false;
        
        for(int i = 0; i < 2; ++i) {
            int x = points[i].first;
            int y = points[i].second;

            if(map[y][x] == 'O') continue;
            
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if(map[ny][nx] == '.' || map[ny][nx] == 'O') {
                map[y][x] = '.';
                if(map[ny][nx] == '.') map[ny][nx] = (i & 1) ? 'R' : 'B';
                points[i] = {nx, ny};
                isMoved = true;
            }
        }

        if(!isMoved) break;
    }

    blue = points[0];
    red = points[1];
}

void solve(vector<vector<char>>& map, pii blue, pii red, pii& hole, int cnt) {
    if(blue == hole || cnt > 10) return;
    if(red == hole) {
        ret = min(ret, cnt);
        return;
    }

    pii cBlue, cRed;

    for(int i = 0; i < 4; ++i) {
        cBlue = blue, cRed = red;
        shiftPoint(map, cBlue, cRed, i);
        solve(map, cBlue, cRed, hole, cnt + 1);

        map[cBlue.second][cBlue.first] = '.';
        map[cRed.second][cRed.first] = '.';
        map[blue.second][blue.first] = 'B';
        map[red.second][red.first] = 'R';
        map[hole.second][hole.first] = 'O';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;

    pii blue, red, hole;
    vector<vector<char>> map(N, vector<char>(M));
    for(int i = 0; i < N; ++i) {
        string str; cin >> str;
        for(int j = 0; j < M; ++j) {
            map[i][j] = str[j];

            if(map[i][j] == 'B') blue = {j, i};
            else if(map[i][j] == 'R') red = {j, i};
            else if(map[i][j] == 'O') hole = {j, i};
        }
    }

    solve(map, blue, red, hole, 0);

    if(ret != 11) cout << ret;
    else cout << -1;

    return 0;
}