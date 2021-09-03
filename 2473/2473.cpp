#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define INF 3000000001LL

using namespace std;
typedef long long ll;

void solve(vector<int>& seq) {
    vector<int> ret;

    ll last = INF;
    for(int i = 0; i < (int)seq.size() - 1; ++i) {
        int front = i + 1;
        int end = (int)seq.size() - 1;

        while(front < end) {
            ll summation = seq[front] + seq[end];

            if(abs(summation + seq[i]) < last) {
                ret = {seq[i], seq[front], seq[end]};
                last = abs(summation + seq[i]);
            }

            if(summation + seq[i] < 0) front++;
            else end--;
        }
    }

    cout << ret[0] << " " << ret[1] << " " << ret[2];
}

int main() {
    int N; cin >> N;
    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    sort(seq.begin(), seq.end());

    solve(seq);

    return 0;
}  