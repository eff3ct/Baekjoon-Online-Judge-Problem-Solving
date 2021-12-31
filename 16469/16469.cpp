#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>
#define INF 100000000

using namespace std;
typedef pair<int, int> pii;

int R, C; 
vector<vector<char>> mp;

void init(vector<vector<int>>& a) {
    for(int i = 0; i < R; ++i) fill(a[i].begin(), a[i].end(), INF);
}

void init(vector<vector<bool>>& a) {
    for(int i = 0; i < R; ++i) fill(a[i].begin(), a[i].end(), false);
}

void addVec(vector<vector<int>>& dest, vector<vector<int>>& del) {
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            dest[i][j] = max(dest[i][j], del[i][j]);
        }
    }
}

void solve(pii& a, pii& b, pii& c) {
    vector<vector<bool>> visit(R, vector<bool>(C, false));
    vector<vector<int>> dist(R, vector<int>(C, INF)); 
    vector<vector<int>> total_dist(R, vector<int>(C, 0)); 

    queue<pii> q;

    int dx[4] = { 1, 0, -1, 0 };
    int dy[4] = { 0, 1, 0, -1 };

    pii abc[3] = {a, b, c};

    for(int i = 0; i < 3; ++i) {
        init(visit);
        init(dist);

        visit[abc[i].first - 1][abc[i].second - 1] = true;
        dist[abc[i].first - 1][abc[i].second - 1] = 0;
        q.push({abc[i].first - 1, abc[i].second - 1});

        while(!q.empty()) {
            pii now = q.front();
            q.pop();

            for(int i = 0; i < 4; ++i) {
                pii next = { now.first + dy[i], now.second + dx[i] };
                if(next.first < 0 || next.first >= R || next.second < 0 || next.second >= C) continue;
                if(mp[next.first][next.second] == '1') continue;
                if(visit[next.first][next.second]) continue;
                
                visit[next.first][next.second] = true;
                dist[next.first][next.second] = dist[now.first][now.second] + 1;
                q.push(next);
            }
        }

        addVec(total_dist, dist);
    }
    
    int ret = INF;
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(total_dist[i][j] >= INF) continue;
            ret = min(ret, total_dist[i][j]);
        }
    }

    int cnt = 0;
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            if(total_dist[i][j] == ret) cnt++;
        }
    }

    if(ret == INF) cout << -1;
    else cout << ret << '\n' << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> R >> C;

    mp.resize(R, vector<char>(C));

    for(int i = 0; i < R; ++i) {
        string str; cin >> str;
        for(int j = 0; j < C; ++j) {
            mp[i][j] = str[j];
        }
    }

    pii swings, changmo, nuksal;
    cin >> nuksal.first >> nuksal.second >> swings.first >> swings.second >> changmo.first >> changmo.second;

    solve(nuksal, swings, changmo);

    return 0;
}