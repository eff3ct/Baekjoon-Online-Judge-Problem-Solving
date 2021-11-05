#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void pushNumbers(vector<vector<int>>& map, int dir) {
    int n = (int)map.size();

    if(dir == 0) {
        for(int i = 0; i < n; ++i) {
            vector<int> row;
            for(int j = 0; j < n; ++j) {
                if(map[i][j]) row.push_back(map[i][j]);
            }
            
            int idx = n - 1;
            for(int k = (int)row.size() - 1; k >= 0; --k) {
                map[i][idx--] = row[k];
            }

            for(int x = idx; x >= 0; --x) {
                map[i][x] = 0;
            }
        }
    }
    else if(dir == 1) {
        for(int j = 0; j < n; ++j) {
            vector<int> column;
            for(int i = 0; i < n; ++i) {
                if(map[i][j]) column.push_back(map[i][j]);
            }

            int idx = n - 1;
            for(int k = (int)column.size() - 1; k >= 0; --k) {
                map[idx--][j] = column[k];
            }

            for(int x = idx; x >= 0; --x) {
                map[x][j] = 0;
            }
        }
    }
    else if(dir == 2) {
        for(int i = 0; i < n; ++i) {
            vector<int> row;
            for(int j = 0; j < n; ++j) {
                if(map[i][j]) row.push_back(map[i][j]);
            }

            int idx = 0;
            for(int k = 0; k < (int)row.size(); ++k) {
                map[i][idx++] = row[k];
            }

            for(int x = idx; x < n; ++x) {
                map[i][x] = 0;
            }
        }
    }
    else {
        for(int j = 0; j < n; ++j) {
            vector<int> column;
            for(int i = 0; i < n; ++i) {
                if(map[i][j]) column.push_back(map[i][j]);
            }

            int idx = 0;
            for(int k = 0; k < (int)column.size(); ++k) {
                map[idx++][j] = column[k];
            }

            for(int x = idx; x < n; ++x) {
                map[x][j] = 0;
            }
        }
    }

}

void updateMap(vector<vector<int>>& map, int dir) {
    vector<vector<int>> ret(map);
    int n = (int)map.size();

    if(dir == 0) { //-->
        pushNumbers(map, dir);

        for(int i = 0; i < n; ++i) {
            for(int j = n - 1; j > 0; --j) {
                if(map[i][j] == map[i][j - 1]) {
                    map[i][j] *= 2;
                    map[i][j - 1] = 0;
                }
            }
        }

        pushNumbers(map, dir);
    }
    else if(dir == 1) { // downward
        pushNumbers(map, dir);
        
        for(int j = 0; j < n; ++j) {
            for(int i = n - 1; i > 0; --i) {
                if(map[i][j] == map[i - 1][j]) {
                    map[i][j] *= 2;
                    map[i - 1][j] = 0;
                }
            }
        }

        pushNumbers(map, dir);
    }
    else if(dir == 2) { // <--
        pushNumbers(map, dir);

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n - 1; ++j) {
                if(map[i][j] == map[i][j + 1]) {
                    map[i][j] *= 2;
                    map[i][j + 1] = 0;
                }
            }
        }

        pushNumbers(map, dir);
    }
    else { // upwards
        pushNumbers(map, dir);

        for(int j = 0; j < n; ++j) {
            for(int i = 0; i < n - 1; ++i) {
                if(map[i][j] == map[i + 1][j]) {
                    map[i][j] *= 2;
                    map[i + 1][j] = 0;
                }
            }
        }

        pushNumbers(map, dir);
    }
}

int solve(int dir, int cnt, vector<vector<int>> map) {
    if(cnt == 5) {
        int M = 0;
        for(int i = 0; i < (int)map.size(); ++i) {
            for(int j = 0; j < (int)map.size(); ++j) {
                M = max(M, map[i][j]);
            }
        }

        return M;
    }

    updateMap(map, dir);

    return max({solve(0, cnt + 1, map),
                solve(1, cnt + 1, map),
                solve(2, cnt + 1, map),
                solve(3, cnt + 1, map)});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    
    vector<vector<int>> map(N, vector<int>(N));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> map[i][j];
        }
    }

    int ret = max({solve(0, 0, map),
                solve(1, 0, map),
                solve(2, 0, map),
                solve(3, 0, map)});

    cout << ret;           

    return 0;
}