#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    int seq[100001];
    for(int i = 0; i < N; ++i) cin >> seq[i];

    int count[500001];

    int left = 0, right = 100001;
    int mid = (left + right) / 2;
    while(left + 1 < right) {
        memset(count, 0, sizeof(int) * 500001);
        mid = (left + right) / 2;

        int cnt = 0;
        int f = 0, b = 0;
        count[seq[b]]++;

        while(b != N) {
            int length = b - f + 1;
            if(length == mid) {
                for(int i = f; i <= b; ++i) count[seq[i]] = 0;
                b++, f = b;
                if(b != N) count[seq[b]]++;
                cnt++;
            }
            else {
                b++;
                if(b == N) break;
                count[seq[b]]++;
                while(count[seq[b]] > 1 && f <= b) {
                    count[seq[f]]--;
                    f++;
                }
            }
        }

        if(cnt >= M) left = mid;
        else right = mid;
    }

    cout << left << '\n';

    return 0;
}