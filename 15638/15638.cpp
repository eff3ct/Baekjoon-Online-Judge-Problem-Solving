#include <iostream>

using namespace std;

bool isPrime(int N) {
    int cnt = 0;
    for(int i = 1; i <= N; ++i) {
        if(N % i == 0) cnt++;
    }

    if(cnt == 2) return true;
    else return false;
}

int main() {
    int N; cin >> N;

    int tmp;
    for(int i = 0; i < N; ++i) cin >> tmp;

    if(isPrime(N)) cout << "Yes";
    else cout << "No";

    return 0;
}