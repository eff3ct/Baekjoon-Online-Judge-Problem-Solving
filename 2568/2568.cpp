#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int N; 
void solve(vector<pair<int, int>>& cord) {
    vector<int> lis;
    vector<int> location(500001, -1);

    for(int i = 0; i < N; ++i) {
        int nowElement = cord[i].second;
        int lowBound = lower_bound(lis.begin(), lis.end(), nowElement) - lis.begin();
        if(lowBound == (int)lis.size()) {
            lis.push_back(nowElement);
            location[nowElement] = (int)lis.size() - 1;
        }
        else {
            lis[lowBound] = nowElement;
            location[nowElement] = lowBound;
        }
    }

    int nowIdx = lis.size() - 1;
    vector<int> lisElement;
    for(int i = 500000; i >= 0; --i) {
        if(nowIdx == -1) break;

        if(nowIdx == location[i]) {
            lisElement.push_back(i);
            nowIdx--;
        }
    }

    reverse(lisElement.begin(), lisElement.end());

    int curIdx = 0;
    vector<int> ret;
    for(int i = 0; i < N; ++i) {
        if(curIdx != (int)lisElement.size()) {
            if(lisElement[curIdx] != cord[i].second) ret.push_back(cord[i].first);
            else curIdx++;
        }
        else ret.push_back(cord[i].first);
    }

    cout << ret.size() << '\n';
    for(auto& element : ret) cout << element << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    vector<pair<int, int>> cord(N);
    for(int i = 0; i < N; ++i) cin >> cord[i].first >> cord[i].second;
    sort(cord.begin(), cord.end());

    solve(cord);

    return 0;
}