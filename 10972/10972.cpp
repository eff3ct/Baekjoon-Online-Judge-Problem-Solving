#include <iostream>
#include <vector>

using namespace std;

void solve(vector<int>& seq) {
    int idx = -1;
    for(int i = (int)seq.size() - 2; i >= 0; --i) {
        if(seq[i] < seq[i + 1]) {
            idx = i;
            break;
        }
    }

    if(idx == -1) {
        cout << -1;
        return;
    }

    for(int i = (int)seq.size() - 1; i >= 0; --i) {
        if(seq[i] > seq[idx]) {
            swap(seq[i], seq[idx]);
            int l = idx + 1, r = (int)seq.size() - 1;
            while(l < r) {
                swap(seq[l], seq[r]);
                l++; r--;
            }
            break;
        }
    }

    for(auto& e : seq) cout << e << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    solve(seq);

    return 0;
}