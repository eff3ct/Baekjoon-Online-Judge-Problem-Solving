#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;
const double INF = 987654321.0;

double solve(vector<pair<double, double>>& seq, vector<bool> chosen, int cnt, int size, int startIdx) {
    //base
    if(cnt == size / 2) {
        double frontX = 0, backX = 0, frontY = 0, backY = 0;
        for(int i = 0; i < size; ++i) {
            if(chosen[i]) {
                frontX += seq[i].first;
                frontY += seq[i].second;
            }
            else {
                backX += seq[i].first;
                backY += seq[i].second;
            }
        }

        double X = frontX - backX;
        double Y = frontY - backY;

        return sqrt(pow(X, 2) + pow(Y, 2));
    }

    //combination
    double ret = INF;
    for(int i = startIdx; i < size; ++i) {
        if(!chosen[i]) {
            chosen[i] = true;
            ret = min(ret, solve(seq, chosen, cnt + 1, size, i));
            chosen[i] = false;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    cout << fixed;
    cout.precision(10);

    while(T--) {
        int N; cin >> N;
        vector<pair<double, double>> seq(N);
        for(int i = 0; i < N; ++i) cin >> seq[i].first >> seq[i].second;

        vector<bool> chosen(N, false);
        double ret = solve(seq, chosen, 0, N, 0);
        cout << ret << '\n';
    }

    return 0;
}