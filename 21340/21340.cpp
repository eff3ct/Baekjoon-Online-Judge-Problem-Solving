#include <bits/stdc++.h>
#include <random>

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, int(1e6) - 1);

    int n; cin >> n;
    
    int dragon_ball = 0;
    while(dragon_ball != n) {
        ll x = dis(gen), y = 0;
        ll d1;
        ll d2;

        cout << x << ' ' << y << endl;
        cin >> d1;

        if(d1 == 0) {
            dragon_ball++;
            continue;
        }

        cout << x + 1 << ' ' << y << endl;
        cin >> d2;
        
        if(d2 == 0) {
            dragon_ball++;
            continue;
        }

        ll tcos = (d1 + 1 - d2) / 2;
        ll q_x = tcos + x, q_y = sqrt(max(d1 - tcos * tcos, 0LL)) + y;

        cout << q_x << ' ' << q_y << endl;
        ll result; cin >> result;

        if(result == 0) dragon_ball++;
    }

    return 0;
}