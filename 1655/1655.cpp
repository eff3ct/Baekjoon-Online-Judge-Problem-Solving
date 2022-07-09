#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    priority_queue<int> pq_left;
    priority_queue<int, vector<int>, greater<int>> pq_right;

    int N; cin >> N;
    int med; cin >> med;
    pq_left.push(med);
    cout << med << '\n';

    int d[2] = {0, 1};
    for(int i = 0; i < N - 1; ++i) {
        int tmp; cin >> tmp;

        if(tmp <= med) pq_left.push(tmp);
        else pq_right.push(tmp);

        while(pq_left.size() < pq_right.size() + d[i & 1] ) {
            int move = pq_right.top();
            pq_right.pop();
            pq_left.push(move);
        }
        while(pq_left.size() > pq_right.size() + d[i & 1] ) {
            int move = pq_left.top();
            pq_left.pop();
            pq_right.push(move);
        }
        med = pq_left.top();

        cout << med << '\n';
    }

    return 0;
}