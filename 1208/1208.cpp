#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int cnt[8000001];
const int mid = 4000000;
int N, S;

void leftDFS(int idx, int sum, vector<int>& seq) {
    if(idx == N / 2) {
        cnt[sum + mid]++;
        return;
    }

    leftDFS(idx + 1, sum, seq);
    leftDFS(idx + 1, sum + seq[idx], seq);
}

long long rightDFS(int idx, int sum, vector<int>& seq) {
    if(idx == N) {
        return cnt[S - sum + mid];
    }

    return rightDFS(idx + 1, sum, seq) 
    + rightDFS(idx + 1, sum + seq[idx], seq);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> S;
    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    leftDFS(0, 0, seq);
    long long ret = rightDFS(N / 2, 0, seq);

    if(S == 0) ret--;

    cout << ret;

    return 0;
}