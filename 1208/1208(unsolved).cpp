#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

int solve(vector<int>& seq, int& S) {
    int cnt = 0;
    int a = 0, b = 0;
    int nowSum = 0;

    for(int i = 0; i < seq.size(); ++i) {
        nowSum = 0;
        for(int j = i; j < seq.size(); ++j) {
            nowSum += seq[j];
            if(nowSum == S) cnt++;
        }
    }

    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, S; cin >> N >> S;
    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    sort(seq.begin(), seq.end());
    
    cout << solve(seq, S);

    return 0;
}