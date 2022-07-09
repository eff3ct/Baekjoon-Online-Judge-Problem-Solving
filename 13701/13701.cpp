#include <iostream>
#include <vector>

using namespace std;
typedef unsigned int uint;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<uint> bitmask(1048576, 0);
    int N;

    while(cin >> N) {
        int Q = N / 32;
        int R = N % 32;

        if(bitmask[Q] & (1 << R)) continue;
        bitmask[Q] |= (1 << R);
        cout << N << ' ';
    }

    return 0;
}