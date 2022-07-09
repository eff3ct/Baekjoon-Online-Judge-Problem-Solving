#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<int> score(N);
    for(int i = 0; i < N; ++i) {
        double x; cin >> x;
        score[i] = int(x * 1000 + 0.1);
    }

    int ans = 1;
    while(true) {
        bool flag = false;
        for(int i = 0; i < N; ++i) {
            bool fl = false;
            for(int j = 0; j <= ans * 10; ++j) {
                int cmp = int(floor(1000 * (double)j / ans));
                if(cmp == score[i]) {
                    fl = true;
                    break;
                }
            }

            if(!fl) {
                flag = true;
                break;
            }
        }

        if(flag) ans++;
        else break;
    }

    cout << ans << '\n';

    return 0;
}