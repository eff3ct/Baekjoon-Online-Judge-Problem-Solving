#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
    int N; cin >> N;
    priority_queue<ll, vector<ll>, greater<ll>> pq;

    for(int i = 0; i < N; ++i) {
        ll cost; cin >> cost;
        pq.push(cost);
    }

    ll ret = 0;
    while(pq.size() != 1) {
        ll temp = pq.top();
        pq.pop();
        temp += pq.top();
        pq.pop();

        ret += temp;

        pq.push(temp);
    }

    cout << ret;

    return 0;
}