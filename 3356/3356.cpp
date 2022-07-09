#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

void getFail(string& P, vector<int>& fail) {
    for(int i = 1, j = 0; i < (int)P.length(); ++i) {
        while(j && P[i] != P[j]) j = fail[j - 1];
        if(P[i] == P[j]) fail[i] = ++j;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int L; cin >> L;
    string str; cin >> str;

    vector<int> fail(L);
    getFail(str, fail);

    cout << L - fail[L - 1] << '\n';

    return 0;
}