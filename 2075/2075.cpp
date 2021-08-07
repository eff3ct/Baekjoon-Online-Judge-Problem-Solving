// https://www.acmicpc.net/problem/2075 //
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int tmp; cin >> tmp;
            pq.push(tmp);
            if(pq.size() > N) pq.pop();
        }
    }

    cout << pq.top();

    return 0;
}