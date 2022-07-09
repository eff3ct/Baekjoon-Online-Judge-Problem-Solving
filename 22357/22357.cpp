#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

bool is_prime[4'000'001];
vector<int> prime;
int K, N; 

void get_prime() {
    fill(is_prime, is_prime + 4'000'001, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= sqrt(4'000'000); ++i) {
        if(is_prime[i]) {
            for(int j = i * i; j <= 4'000'000; j += i) 
                is_prime[j] = false;
        }
    }

    for(int i = N; i <= 4'000'000; ++i) {
        if(is_prime[i] ) prime.push_back(i);
    }
}

void solve() {
    get_prime();
    for(int i = 0; i < K; ++i) {
        int d = prime[i];
        for(int j = 0; j < N; ++j) cout << 1 + j * d << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> K >> N;
    solve();

    return 0;
}