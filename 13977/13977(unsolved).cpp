// https://www.acmicpc.net/problem/13977 //
#include <iostream>
#include <vector>

#define DNM 1000000007

using namespace std;

typedef long long ll;

ll combination(int N, int K) {
    if(K == 0 || N == K) return 1;
}

int main() {
    int M; cin >> M;

    while(M--) {
        int N, K; cin >> N >> K;
        cout << combination(N, K) << '\n';
    }

    return 0;
}