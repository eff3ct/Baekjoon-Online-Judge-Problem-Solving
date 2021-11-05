#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

#define MAX 100000

using namespace std;

int main() {
    int m, n, k; cin >> m >> n >> k;

    vector<vector<int>> treasures(MAX + 1);
    for(int i = 0; i < k; ++i) {
        int y, x; cin >> y >> x;
        treasures[x].push_back(y);
    }

    for(int i = 1; i <= MAX; ++i) {
        if(!treasures[i].empty()) sort(treasures[i].begin(), treasures[i].end());
    }

    int ret = 0;
    while(k) {
        ret++;
        int cur = 0;

        for(int i = 1; i <= n; ++i) {
            if(treasures[i].empty()) continue;

            for(int idx = 0; idx < (int)treasures[i].size(); idx++) { 
                if(treasures[i][idx] >= cur) {
                    cur = treasures[i][idx];
                    treasures[i].erase(treasures[i].begin() + idx--);
                    k--;
                }
            }
        }
    }

    cout << ret << '\n';

    return 0;
}