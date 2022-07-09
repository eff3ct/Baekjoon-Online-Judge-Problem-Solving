#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return (b == 0 ? a : gcd(b, a % b));
}

int lcm(int a, int b) {
    return a*b / gcd(a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;  
    cin >> T;

    while(T--) {
        int M, N, x, y;
        cin >> M >> N >> x >> y;
        bool print = false;

        if(M == x) x = 0;
        if(N == y) y = 0;
        for(int i = x; i <= (M * N); i += M) {
            if(((i % M) == x) && ((i % N) == y)) {
                cout << (i == 0 ? lcm(M, N) : i) << "\n";
                print = true;
                break;
            }
        }
        if(!print) cout << -1 << "\n";
    }

    return 0;
}