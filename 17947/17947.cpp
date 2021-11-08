#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int N, M, K; cin >> N >> M >> K;

    vector<int> modSeq(K);
    for(int i = 1; i <= 4 * N; ++i) modSeq[i % K]++;

    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        modSeq[a % K]--; modSeq[b % K]--;
    }

    int A, B; cin >> A >> B;
    modSeq[A % K]--; modSeq[B % K]--;

    int scr = abs(A % K - B % K);

    int cnt = 0;
    int s = 0;
    for(int i = scr + 1; i < K; ++i) {
        s += modSeq[i - scr - 1];
        cnt += min(s, modSeq[i]);
        s -= min(s, modSeq[i]);
    }

    if(cnt >= M) cnt = M - 1;

    cout << cnt;
    
    return 0;
}