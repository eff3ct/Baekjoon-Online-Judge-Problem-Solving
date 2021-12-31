#include <iostream>

using namespace std;

int main() {
    int N, M, L; cin >> N >> M >> L;

    int bookLength = 0;
    for(int i = 0; i < N; ++i) {
        int temp; cin >> temp;
        bookLength += temp;
    }

    if(bookLength == M) cout << 0;
    else if(bookLength < M && bookLength >= L || bookLength + L <= M) cout << 1;
    else cout << -1;

    return 0;
}