#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>

using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, int> ppii;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void solve(vector<string>& map, pii& start) {
    int N = int(map.size()), M = int(map[0].size());

    vector<vector<bool>> visit(N, vector<bool>(M, false));

    queue<ppii> q;
    visit[start.first][start.second] = true;
    q.push({start, 0});

    int ans = -1;
    bool flag = false;
    while(!q.empty()) {
        int y = q.front().first.first, x = q.front().first.second, dist = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if(nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
            if(visit[ny][nx] || map[ny][nx] == '1') continue;

            if(map[ny][nx] == '0') {
                pii next = {ny, nx};
                visit[ny][nx] = true;
                q.push({next, dist + 1});
            }
            else {
                ans = dist + 1;
                flag = true;
                break;
            }
        }

        if(flag) break;
    }

    if(ans != -1) {
        cout << "TAK\n";
        cout << ans;
    }
    else cout << "NIE\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<string> map(N);
    pii start;
    for(int i = 0; i < N; ++i) {
        cin >> map[i];
        for(int j = 0; j < M; ++j) {
            if(map[i][j] == '2') {
                start = {i, j};
                map[i][j] = '0';
            }
        }
    }

    solve(map, start);

    return 0;
}