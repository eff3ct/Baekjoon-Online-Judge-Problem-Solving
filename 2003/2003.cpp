// https://www.acmicpc.net/problem/2003 //
#include <iostream>
#include <vector>

using namespace std;

int res = 0;

void solve(vector<int>& seq, int M) {
    if(seq.size() == 1) {
        res = (seq[0] == M) ? 1 : 0;
        return;
    }

    int s = -1, e = 0;
    int nowSum = seq[0];

    while(true) {
        if(nowSum == M) res++;
        if(nowSum >= M) {
            s += 1;
            if(s == (seq.size() - 1)) break;
            nowSum -= seq[s];
        }
        else {
            e += 1;
            if(e == seq.size()) break;
            nowSum += seq[e];
        }
    }
}

int main() {
    int N, M; cin >> N >> M;

    vector<int> seq(N, 0);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    solve(seq, M);

    cout << res;

    return 0;
}