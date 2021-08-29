#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximum = 0;

void doVisit(vector<bool> (&visit)[2], int n, int i, int j, bool status, vector<pair<int, int>>& changed) {
    if(status == true) {
        visit[i][j] = status;
        changed.push_back({i, j});
        if(j >= 1) {
            if(visit[i][j - 1] != status) {
                visit[i][j - 1] = status;
                changed.push_back({i, j - 1});
            }   
        }
        if(j < (n - 1)) {
            if(visit[i][j + 1] != status) {
                visit[i][j + 1] = status;
                changed.push_back({i, j + 1});
            }
        }
        if(i == 0) {
            if(visit[i + 1][j] != status) {
                visit[i + 1][j] = status;
                changed.push_back({i + 1, j});
            }
        }
        if(i == 1) {
            if(visit[i - 1][j] != status) {
                visit[i - 1][j] = status;
                changed.push_back({i - 1, j});
            }
        }
    }
    else {
        for(int i = 0; i < changed.size(); ++i) {
            int y = changed[i].first, x = changed[i].second;
            visit[y][x] = status;
        }
    }
    
}

void solve(vector<int> (&sticker)[2], vector<bool> (&visit)[2], int curSum, int& n) {
    maximum = max(maximum, curSum);
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < n; ++j) {
            if(!visit[i][j]) {
                vector<pair<int, int>> changed;
                
                curSum += sticker[i][j];
                doVisit(visit, n, i, j, true, changed);

                solve(sticker, visit, curSum, n);

                curSum -= sticker[i][j];
                doVisit(visit, n, i, j, false, changed);
            }   
        }
    }
}

int main() {
    int T; cin >> T;
    for(int testCase = 0; testCase < T; ++testCase) {
        int n; cin >> n;

        vector<int> sticker[2];
        vector<bool> visit[2];

        for(int i = 0; i < n; ++i) {
            int x; cin >> x;
            sticker[0].push_back(x);
            visit[0].push_back(false);
        }
        for(int i = 0; i < n; ++i) {
            int x; cin >> x;
            sticker[1].push_back(x);
            visit[1].push_back(false);
        }

        maximum = 0;
        solve(sticker, visit, 0, n);
        cout << maximum << "\n";
    }
    return 0;
}