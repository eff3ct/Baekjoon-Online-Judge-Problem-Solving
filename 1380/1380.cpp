#include <iostream>
#include <string>

using namespace std;

int main() {
    int idx = 1;

    while(true) {
        int n; cin >> n;
        cin.get();

        if(n == 0) break;

        string nameList[101];
        int count[101] = { 0, };
        for(int i = 1; i <= n; ++i) getline(cin, nameList[i], '\n');

        for(int i = 0; i < 2 * n - 1; ++i) {
            int num;
            char ab;
            cin >> num >> ab;
            count[num]++;
        }
        
        for(int i = 1; i <= n; ++i) {
            if(count[i] == 1) cout << idx << ' ' << nameList[i] << '\n';
        }

        idx++;
    }

    return 0;
}