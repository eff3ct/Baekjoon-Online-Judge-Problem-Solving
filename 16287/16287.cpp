#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int w, n; cin >> w >> n;
    vector<int> a(n);
    vector<int> weight(w + 1, -1);
    for(int& e : a) cin >> e;

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(a[i] + a[j] > w) continue;
            
            if(weight[w - a[i] - a[j]] != -1 && weight[w - a[i] - a[j]] < i) {
                cout << "YES\n";
                return 0;
            }

            if(weight[a[i] + a[j]] == -1) weight[a[i] + a[j]] = j;
            else weight[a[i] + a[j]] = min(weight[a[i] + a[j]], j);
        }
    }

    cout << "NO\n";

    return 0;
}