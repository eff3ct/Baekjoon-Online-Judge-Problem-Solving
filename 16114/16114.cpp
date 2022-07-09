#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int X, N; cin >> X >> N;
    if(N & 1) {
        if(N == 1) {
            if(X < 0) cout << "INFINITE\n";
            else cout << "0\n";
        }
        else cout << "ERROR\n";
    }
    else if(N == 0) {
        if(X > 0) cout << "INFINITE\n";
        else cout << "0\n";
    }
    else {
        cout << max(0, (int)ceil(double((X - N / 2)) / (N / 2))) << '\n';
    }

    return 0;
}