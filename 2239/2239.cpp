#include <iostream>
#include <vector>

using namespace std;

bool isEnd = false;

bool isOverlapped(int x, int y, vector<vector<int>>& map) {
    bool check[10] = { false, };
    for(int i = 0; i < 9; ++i) {
        if(map[y][i]) {
            if(check[map[y][i]]) return true;
            check[map[y][i]] = true;
        }
    }

    fill(check, check + 10, false);
    for(int i = 0; i < 9; ++i) {
        if(map[i][x]) {
            if(check[map[i][x]]) return true;
            check[map[i][x]] = true;
        }
    }

    fill(check, check + 10, false);
    int segX = x / 3;
    int segY = y / 3;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(map[3 * segY + i][3 * segX + j]) {
                if(check[map[3 * segY + i][3 * segX + j]]) return true;
                check[map[3 * segY + i][3 * segX + j]] = true;
            }
        }
    }

    return false;
}

void solve(int x, int y, vector<vector<int>>& map) {
    if(isEnd) return;

    if(x >= 9) {
        x = 0;
        y += 1;
    }

    if(x == 0 && y == 9) {
        isEnd = true;
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                cout << map[i][j];
            }
            cout << '\n';
        }
        return;
    }

    if(map[y][x] == 0) {
        for(int num = 1; num <= 9; ++num) {
            map[y][x] = num;
            if(!isOverlapped(x, y, map)) solve(x + 1, y, map);
            map[y][x] = 0;
        }
    }
    else solve(x + 1, y, map);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str[9];
    for(int i = 0; i < 9; ++i) cin >> str[i];

    vector<vector<int>> map(9, vector<int>(9));
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            map[i][j] = str[i][j] - '0';
        }
    }

    solve(0, 0, map);

    return 0;
}