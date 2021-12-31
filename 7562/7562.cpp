#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;
typedef pair<int, int> pii;

int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

void solve(int I, pii& S, pii& E) {
    vector<vector<bool>> visit(I, vector<bool>(I));
    vector<vector<int>> dist(I, vector<int>(I));
    queue<pii> q;

    visit[S.second][S.first] = true;
    q.push(S);

    while(!q.empty()) {
        pii nowCoord = q.front();
        q.pop();

        for(int i = 0; i < 8; ++i) {
            pii nextCoord = {nowCoord.first + dx[i], nowCoord.second + dy[i]};

            if(nextCoord.first < 0 || nextCoord.first >= I || nextCoord.second < 0 || nextCoord.second >= I) continue;
            if(visit[nextCoord.second][nextCoord.first]) continue;

            dist[nextCoord.second][nextCoord.first] = dist[nowCoord.second][nowCoord.first] + 1;
            visit[nextCoord.second][nextCoord.first] = true;

            q.push(nextCoord);
        }
    }

    cout << dist[E.second][E.first] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    while(T --> 0) {
        int I; cin >> I;
        pii S, E; 
        
        cin >> S.first >> S.second;
        cin >> E.first >> E.second;

        solve(I, S, E);
    }

    return 0;
}