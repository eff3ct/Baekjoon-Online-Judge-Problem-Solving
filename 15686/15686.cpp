// https://www.acmicpc.net/problem/15686 //
#include <iostream>
#include <vector>
#include <cmath>
#define INF 987654321

using namespace std;

int ret = INF;

void solve(int idx, vector<pair<int, int>>& chosenChicken, vector<pair<int, int>>& chicken, vector<pair<int, int>>& house, int& M) {
    if(chosenChicken.size() == M) {
        int chickenDist = 0;
        for(auto& element : house) {
            int hy = element.first;
            int hx = element.second;

            int minimum = abs(hx - chosenChicken[0].second) + abs(hy - chosenChicken[0].first);
            for(auto& c : chosenChicken) {
                int cy = c.first;
                int cx = c.second;

                minimum = min(minimum, abs(hx - cx) + abs(hy - cy));
            }

            chickenDist += minimum;
        }
        ret = min(ret, chickenDist);
        return;
    }

    for(int i = idx; i < chicken.size(); ++i) {
        chosenChicken.push_back(chicken[i]);
        solve(i + 1, chosenChicken, chicken, house, M);
        chosenChicken.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<pair<int, int>> house;
    vector<pair<int, int>> chicken;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            int x; cin >> x;
            if(x == 1) house.push_back({i, j});
            else if(x == 2) chicken.push_back({i, j});
        }
    }

    vector<pair<int, int>> chosenChicken;
    solve(0, chosenChicken, chicken, house, M);

    cout << ret;
    return 0;
}