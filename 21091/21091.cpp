#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

struct Result {
    int l, r;
    char dir;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N), B(N);
    for(int& e : A) cin >> e;
    for(int& e : B) cin >> e;

    vector<Result> ans;
    bool flag = false;
    for(int i = 0; i < N; ++i) {
        if(A[i] != B[i]) {
            flag = true;
            break;
        }
    }

    if(flag) {
        ans.push_back({1, N, 'I'});
        sort(A.begin(), A.end());
        for(int i = 0; i < N; ++i) {
            if(A[i] == B[i]) continue;
            for(int j = i + 1; j < N; ++j) {
                if(A[j] == B[i]) {
                    sort(A.begin() + i, A.begin() + j + 1);
                    if(A[i] == B[i]) {
                        ans.push_back({i + 1, j + 1, 'I'});
                        break;
                    }
                    
                    sort(A.begin() + i, A.begin() + j + 1, greater<int>());
                    ans.push_back({i + 1, j + 1, 'D'});
                    break;
                }
            }
        }

        cout << ans.size() << '\n';
        for(auto& e : ans) cout << e.l << ' ' << e.r << ' ' << e.dir << '\n';
    }
    else cout << "0\n";

    return 0;
}