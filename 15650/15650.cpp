// https://www.acmicpc.net/problem/15650 //
#include <iostream>

using namespace std;

void solve(const int& N, const int& M, int depth, int start) {
    static int arr[10] = { 0, };
    if(depth == M) {
        for(int i = 0; i < M; ++i) {
            cout << arr[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i = start; i <= N; ++i) {
        arr[depth] = i;
        solve(N, M, depth + 1, i + 1);
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    solve(N, M, 0, 1);
    return 0;
}