#include <iostream>
#include <vector>
#include <utility>

using namespace std;
typedef pair<pair<int, int>, int> ppiii;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};

int catch_shark(int col, int max_row, vector<vector<vector<ppiii>>>& shark_info) {
    int ret = 0;
    for(int i = 0; i < max_row; ++i) {
        if(!shark_info[i][col].empty()) {
            ret = shark_info[i][col].front().second;
            shark_info[i][col].pop_back();
            break;
        }
    }
    return ret;
}

void update_shark(int R, int C, vector<vector<vector<ppiii>>>& shark_info) {
    vector<pair<pair<int, int>, ppiii>> temp;
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(!shark_info[i][j].empty()) {
                temp.push_back({{i, j} ,shark_info[i][j].front()});
                shark_info[i][j].pop_back();
            }
        }
    }

    for(auto& e : temp) {
        int speed = e.second.first.first;
        int dir = e.second.first.second;
        int size = e.second.second;

        int y = e.first.first;
        int x = e.first.second;

        int ny = y + speed * dy[dir];
        int nx = x + speed * dx[dir];

        int cnt = 0;
        while(ny < 0 || ny >= R) {
            cnt = (cnt + 1) % 2;
            if(ny < 0) ny *= -1;
            else if(ny >= R) ny = 2 * R - 2 - ny;
        }

        while(nx < 0 || nx >= C) {
            cnt = (cnt + 1) % 2;
            if(nx < 0) nx *= -1;
            else if(nx >= C) nx = 2 * C - 2 - nx;
        }

        if(cnt == 1) {
            switch(dir) {
                case 0:
                    dir = 1;
                    break;
                case 1:
                    dir = 0;
                    break;
                case 2:
                    dir = 3;
                    break;
                case 3:
                    dir = 2;
                    break;   
            }
        }

        if(shark_info[ny][nx].empty())
            shark_info[ny][nx].push_back({{speed, dir}, size});
        else {
            if(shark_info[ny][nx].front().second > size) continue;
            else {
                shark_info[ny][nx].pop_back();
                shark_info[ny][nx].push_back({{speed, dir}, size});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int R, C, M; cin >> R >> C >> M;

    vector<vector<vector<ppiii>>> shark_info(R, vector<vector<ppiii>>(C));

    for(int i = 0; i < M; ++i) {
        int r, c, s, d, z; cin >> r >> c >> s >> d >> z;
        ppiii data = {{s, d - 1}, z};
        shark_info[r - 1][c - 1].push_back(data); //speed, direction, size
    }

    int cnt = 0;

    for(int i = 0; i < C; ++i) {
        cnt += catch_shark(i, R, shark_info);
        update_shark(R, C, shark_info);
    }

    cout << cnt;

    return 0;
}