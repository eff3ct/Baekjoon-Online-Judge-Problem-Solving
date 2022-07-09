#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int p, g; cin >> p >> g;
    map<string, int> m;

    for(int i = 0; i < p; ++i) {
        string party; cin >> party;
        double val; cin >> val;
        m[party] = int(val * 10 + 0.1);
    }

    for(int i = 0; i < g; ++i) {
        double val = 0;
        while(true) {
            string x; cin >> x;
            if(x[0] == '=' || x[0] == '<' || x[0] == '>') {
                int y; cin >> y;
                y *= 10;

                bool isCorrect = false;
                if(x == "=") {
                    if(val == y) isCorrect = true;
                }
                else if(x == ">=") {
                    if(val >= y) isCorrect = true;
                }
                else if(x == "<=") {
                    if(val <= y) isCorrect = true;
                }
                else if(x == "<") {
                    if(val < y) isCorrect = true;
                }
                else {
                    if(val > y) isCorrect = true;
                }

                cout << "Guess #" << i + 1 << " was ";
                if(isCorrect) cout << "correct.\n";
                else cout << "incorrect.\n";

                break;
            }
            else if(x[0] == '+') continue;

            val += m[x];
        }
    }

    return 0;
}