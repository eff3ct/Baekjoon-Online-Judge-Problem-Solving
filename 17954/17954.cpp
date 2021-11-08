#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<vector<int>> apple(2, vector<int>(N));

    if(N != 1) {
        apple[0][0] = 2 * N;
        apple[0][N - 1] = 2 * N - 1;
        apple[1][0] = 2 * N - 2;
        apple[1][N - 1] = 2 * N - 3;

        int col = N - 2;
        for(int i = 2 * N - 4; i > N - 2; --i) apple[1][col--] = i;

        col = N - 2;
        for(int i = N - 2; i > 0; --i) apple[0][col--] = i;

        ll time = 1;
        ll s = N * (2 * N + 1);
        ll ret = 0;

        ll now = 2 * N - 3;
        for(int i = 0; i < N - 1; ++i) {
            s -= now--;
            ret += s * time++;
        }

        now = 2 * N - 2;
        s -= now;
        ret += s * time++;

        now = 2 * N - 1;
        s -= now;
        ret += s * time++;

        now = N - 2;
        for(int i = 0; i < N - 2; ++i) {
            s -= now--;
            ret += s * time++;
        }

        cout << ret << '\n';

        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < N; ++j) {
                cout << apple[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    else {
        cout << 2 << '\n';
        cout << 1 << '\n' << 2;
    }
 
    return 0;
}