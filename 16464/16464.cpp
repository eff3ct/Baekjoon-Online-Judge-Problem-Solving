#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int N; cin >> N;
    while(N --> 0) {
        int p; cin >> p;
        if(p & 1) cout << "Gazua\n";
        else {
            while(p != 1) {
                if(p & 1) {
                    cout << "Gazua\n";
                    break;
                }
                p /= 2;
            }

            if(p == 1) cout << "GoHanGang\n";
        }
    }
    return 0;
}