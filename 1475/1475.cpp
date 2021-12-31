#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int N; cin >> N;
    int count[10] = { 0, };

    while(N) {
        count[N % 10]++;
        N /= 10;
    }

    int cnt = 0;
    for(int i = 0; i < 10; ++i) {
        if(i == 6 || i == 9) continue;
        cnt = max(count[i], cnt);
    }

    cnt = max(int(ceil((double)(count[6] + count[9]) / 2)), cnt);

    cout << cnt;

    return 0;
}