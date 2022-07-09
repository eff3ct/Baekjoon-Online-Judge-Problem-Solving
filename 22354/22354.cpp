#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll seq[300'001];

ll solve(int N, string& str) {
    vector<ll> reduced_stone;
    for(int i = 0; i < N; ++i) {
        ll M = seq[i];
        if(str[i] == str[i + 1]) {
            int j;

            for(j = i + 1; j < N && str[i] == str[j]; ++j) 
                M = max(M, seq[j]);
            
            i = j - 1;
        }
        reduced_stone.push_back(M);
    }

    if((int)reduced_stone.size() <= 2) return 0;
    else if((int)reduced_stone.size() == 3) return reduced_stone[1];
    else {
        ll ret = 0;
        sort(reduced_stone.begin() + 1, reduced_stone.end() - 1, greater<ll>());

        int n = (int)reduced_stone.size();
        for(int i = 1; i <= ceil((double)(n - 2) / 2.0); ++i) 
            ret += reduced_stone[i];
        
        return ret;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    string stone; cin >> stone;
    for(int i = 0; i < N; ++i) cin >> seq[i];

    cout << solve(N, stone) << '\n';

    return 0;
}