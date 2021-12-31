#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;
typedef pair<int, int> pii;
int ret = 987654321;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int get_low(int bitmask) {
    for(int i = 10; i >= 1; --i) {
        if(bitmask & (1 << i)) return i;
    }
    return 0;
}

void solve(vector<vector<int>>& mp, int bitmask) {
    int count = 0;

    vector<pii> history;
    for(int i = 0; i < 10; ++i) {
        if(bitmask & (1 << (i + 1))) {
            count++;
            history.push_back({0, i});
            mp[0][i] = !mp[0][i];
            for(int j = 0; j < 4; ++j) {
                int ny = dy[j];
                int nx = i + dx[j];

                if(nx < 0 || nx >= 10 || ny < 0 || ny >= 10) continue;
                mp[ny][nx] = !mp[ny][nx];
            }
        }
    }

    for(int i = 1; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            if(mp[i - 1][j]) {
                count++;
                history.push_back({i, j});
                mp[i][j] = !mp[i][j];
                for(int k = 0; k < 4; ++k) {
                    int ny = i + dy[k];
                    int nx = j + dx[k];

                    if(nx < 0 || nx >= 10 || ny < 0 || ny >= 10) continue;
                    mp[ny][nx] = !mp[ny][nx];
                }
            }
        }
    }
    
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            if(mp[i][j] == 1) count = 98765321;
        }
    }

    ret = min(count, ret);

    for(auto& e : history) {
        int y = e.first;
        int x = e.second;

        mp[y][x] = !mp[y][x];
        for(int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if(nx < 0 || nx >= 10 || ny < 0 || ny >= 10) continue;
            mp[ny][nx] = !mp[ny][nx];
        }
    }

    int lowBound = get_low(bitmask);

    for(int i = lowBound + 1; i <= 10; ++i) {
        solve(mp, bitmask | (1 << i));
    }
}

int main() {
    string mp[10];
    for(int i = 0; i < 10; ++i) cin >> mp[i];

    vector<vector<int>> integer_mp(10, vector<int>(10));
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            if(mp[i][j] == 'O') integer_mp[i][j] = 1;
        }
    }

    solve(integer_mp, 0);

    cout << (ret == 987654321 ? -1 : ret);
    return 0;
}