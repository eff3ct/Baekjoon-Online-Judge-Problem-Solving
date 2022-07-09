#include <bits/stdc++.h>
#include <random>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    random_device rd;
    mt19937 gen(rd());

    vector<int> C[10001];

    int N, c; cin >> N >> c;
    vector<int> seq(N + 1);
    for(int i = 1; i <= N; ++i) {
        int color; cin >> color;
        seq[i] = color;
        C[color].push_back(i);
    }

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int A, B; cin >> A >> B;
        uniform_int_distribution<int> dis(A, B);
        bool flag = false;
        for(int j = 0; j < 30; ++j) {
            int r = dis(gen);
            int cnt = upper_bound(C[seq[r]].begin(), C[seq[r]].end(), B) 
            - lower_bound(C[seq[r]].begin(), C[seq[r]].end(), A);

            if(cnt > (B - A + 1) / 2) {
                cout << "yes " << seq[r] << '\n';
                flag = true;
                break;
            }
        }

        if(!flag) cout << "no\n";
    }

    return 0;
}