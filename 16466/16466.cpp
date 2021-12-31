#include <iostream>
#include <algorithm>

using namespace std;

int ticket[1000001];
bool check[1000001] = { false, };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    for(int i = 0; i < N; ++i) {
        cin >> ticket[i];
        check[ticket[i]] = true;
    }

    for(int i = 1; i < 1000001; ++i) {
        if(!check[i]) {
            cout << i; 
            break;
        }
    }
    return 0;

}