// https://www.acmicpc.net/problem/12738 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solveLIS(vector<int> seq) {
    vector<int> lis;
    lis.push_back(seq[0]);
    for(int i = 1; i < seq.size(); ++i) {
        int lowBound = lower_bound(lis.begin(), lis.end(), seq[i]) - lis.begin();
        
        if(lowBound != lis.size()) lis[lowBound] = seq[i];
        else lis.push_back(seq[i]);
    }

    return lis.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;

    vector<int> seq(n);
    for(int i = 0; i < n; ++i) cin >> seq[i];

    cout << solveLIS(seq);

    return 0;
}