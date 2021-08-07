// https://www.acmicpc.net/problem/1806 //
#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;

void solve(vector<int>& number, int& N, int& S) {
    int nowSum = 0, low = 0, high = 0, res = INF;
    while(true) {
        if(nowSum >= S) nowSum -= number[low++];
        else if(nowSum < S && high == number.size()) break;
        else nowSum += number[high++];

        if(nowSum >= S) res = min(res, high - low);
    }

    if(res == INF) cout << 0;
    else cout << res;
}

int main() {
    int N, S; cin >> N >> S;

    vector<int> seq(100001, 0);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    solve(seq, N, S);

    return 0;
}
