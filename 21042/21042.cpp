#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i = 0; i < 25; ++i) {
        int a = i % 25, b = (i + 1) % 25, c = (i + 3) % 25;
        int d = (i + 4) % 25, e = (i + 11) % 25;
        int f = (i + 5) % 25, g = (i + 13) % 25;
        int h = (i + 6) % 25, j = (i + 15) % 25;

        cout << char('A' + a) << char('A' + b) << char('A' + c) << '\n';
        cout << char('A' + a) << char('A' + d) << char('A' + e) << '\n';
        cout << char('A' + a) << char('A' + f) << char('A' + g) << '\n';
        cout << char('A' + a) << char('A' + h) << char('A' + j) << '\n';
    }   

    return 0;
}