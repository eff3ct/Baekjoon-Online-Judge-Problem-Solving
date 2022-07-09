#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll INF = 1234567654321LL;

vector<ll> prefix_sum;

ll get_sum(int i, int j) {
    return prefix_sum[j] - prefix_sum[i - 1];
}

ll get_cost(vector<ll>& adr, int i, int j) {
    ll mid = (adr[i] + adr[j] + 1) / 2;
    int lb = lower_bound(adr.begin() + 1, adr.end(), mid) - adr.begin();
    return (get_sum(i, lb - 1) - adr[i] * (lb - i)) + (adr[j] * (j - lb + 1) - get_sum(lb, j));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    prefix_sum.resize(N + 1);

    vector<int> cnt(N + 1, 1);
    vector<ll> dp(N + 1); // dp[idx] := idx번째에 국밥집 놓았을때 1 ~ idx번째까지 cost 최솟값

    vector<ll> adr(N + 1);
    for(int i = 1; i <= N; ++i) cin >> adr[i];
    ll C, M; cin >> C >> M;

    sort(adr.begin() + 1, adr.end());

    for(int i = 1; i <= N; ++i) prefix_sum[i] = adr[i] + prefix_sum[i - 1];
    for(int i = 1; i <= N; ++i) dp[i] = M + C * (adr[i] * i - get_sum(1, i));

    for(int i = 1; i <= N; ++i) {
        if(adr[i] == adr[i - 1]) continue;

        for(int j = i + 1; j <= N; ++j) {
            ll new_cost = M + C * get_cost(adr, i, j);

            if(dp[i] + new_cost < dp[j]) {
                dp[j] = new_cost + dp[i];
                cnt[j] = cnt[i] + 1;
            }
            else if(dp[i] + new_cost == dp[j] 
            && cnt[j] > cnt[i] + 1) cnt[j] = cnt[i] + 1;
        }
    }

    ll ans_cost = INF;
    ll ans_cnt = -1;
    for(int i = 1; i <= N; ++i) {
        if(adr[i] == adr[i - 1]) continue;

        ll tmp = dp[i] + C * (get_sum(i + 1, N) - adr[i] * (N - i));
        if(tmp < ans_cost) {
            ans_cost = tmp;
            ans_cnt = cnt[i];
        }
    }

    cout << ans_cost << ' ' << ans_cnt << '\n';

    return 0;
}