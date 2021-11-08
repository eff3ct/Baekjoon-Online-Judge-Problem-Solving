#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define INF 12345678987654321LL

using namespace std;
typedef long long ll;

void solve(vector<ll>& address, ll N, ll C, ll M) {
    //dp[count][x] = x위치에 count번째 사업장을 놓을때 최소 cost

    //ret = min(dp[count][x], ret), ret init = inf

    //dp[count][x] = min(dp[count - 1][k < x] + C * summation(|x - update_loc|) 
    //                  - C * summation(|k - update_loc|) + m, dp[count][x])

    //dp init = inf

    //dp[1][x'] : for every x', dp[1][x'] = C * summation(|x' - loc|) + m
    //5000 * 5000 vector -> x는 N에서 유효한 좌표만 있으면 되기 때문에 최대 ~ 100MB
    ll ret = 12345678987654321LL;
    int retCnt = 1;

    sort(address.begin(), address.end());
    vector<ll> cpy(address);
    cpy.erase(unique(cpy.begin(), cpy.end()), cpy.end());

    vector<vector<ll>> dp(N + 1, vector<ll>(N + 1, INF));

    for(int i = 0; i < (int)cpy.size(); ++i) {
        ll s = 0;
        for(auto& element : address) s += abs(cpy[i] - element);
        dp[1][cpy[i]] = C * s + M;
        ret = min(ret, dp[1][cpy[i]]);
    }

    for(int count = 2; count <= N; ++count) {
        for(int loc = 0; loc < cpy.size(); ++loc) {
            for(int k = 0; k < loc; ++k) {
                ll sCur = 0, sLast = 0;
                for(auto& element : address) {
                    if(abs(element - cpy[k]) > abs(element - cpy[loc])) {
                        sCur += abs(cpy[loc] - element);
                        sLast += abs(cpy[k] - element);
                    }
                }

                dp[count][cpy[loc]] = min(dp[count][cpy[loc]], 
                dp[count - 1][cpy[k]] + C * sCur - C * sLast + M);
                
                if(dp[count][cpy[loc]] < ret) {
                    ret = dp[count][cpy[loc]];
                    retCnt = count;
                }
            }
        }
    }

    cout << ret << " " << retCnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll N; cin >> N;
    vector<ll> address(N);
    for(int i = 0; i < N; ++i) cin >> address[i];
    ll C, M; cin >> C >> M;

    solve(address, N, C, M);

    return 0;
}