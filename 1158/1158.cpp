// https://www.acmicpc.net/problem/1158 //
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string solve(int n, int k) {
    string ret = "<";

    int idx = -1;
    vector<int> seq(n);
    for(int i = 1; i <= n; ++i) seq[i - 1] = i;
    
    while(!seq.empty()) {
        idx = (idx + k) % seq.size();
        ret += to_string(seq[idx]);
        ret += ", ";
        seq.erase(seq.begin() + idx);
        idx -= 1;
    }

    ret[ret.size() - 2] = '>';

    return ret;
}

int main() {
    int n, k; cin >> n >> k;

    cout << solve(n, k);

    return 0;
}