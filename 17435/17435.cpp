#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m; cin >> m;
    vector<vector<int>> f(m + 1, vector<int>(20));
    for(int i = 1; i <= m; ++i) cin >> f[i][0];

    for(int i = 1; i <= 19; ++i) {
        for(int j = 1; j <= m; ++j) {
            f[j][i] = f[ f[j][i - 1] ][i - 1];
        }
    }

    int Q; cin >> Q;
    while(Q --> 0) {
        int n, x; cin >> n >> x;
        for(int j = 19; j >= 0; --j) {
            if(n >= 1 << j) {
                n -= 1 << j;
                x = f[x][j];
            }
        }
        cout << x << '\n';
    }

    return 0;
}