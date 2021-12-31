#include <iostream>
#include <cmath>

using namespace std;

int solve(int a, int b, char ch, int goal) {
    int temp;
    int ret = 6;
    if(ch == 'A') {
        if(a == goal) return 0;
        if(b == goal) return 1;

        temp = a;
        for(int i = 1; i <= 6; ++i) {
            temp += 20;
            if(temp > 146000) temp = 144000;
            if(temp == goal) ret = min(ret, i);
        }

        temp = b;
        for(int i = 1; i <= 6; ++i) {
            temp += 20;
            if(temp > 146000) temp = 144000;
            if(temp == goal) ret = min(ret, i + 1);
        }

        temp = a;
        for(int i = 1; i <= 6; ++i) {
            temp -= 20;
            if(temp < 144000) temp = 146000;
            if(temp == goal) ret = min(ret, i);
        }

        temp = b;
        for(int i = 1; i <= 6; ++i) {
            temp -= 20;
            if(temp < 144000) temp = 146000;
            if(temp == goal) ret = min(ret, i + 1);
        }
    }
    else {
        if(b == goal) return 0;
        if(a == goal) return 1;

        temp = b;
        for(int i = 1; i <= 6; ++i) {
            temp += 20;
            if(temp > 146000) temp = 144000;
            if(temp == goal) ret = min(ret, i);
        }

        temp = a;
        for(int i = 1; i <= 6; ++i) {
            temp += 20;
            if(temp > 146000) temp = 144000;
            if(temp == goal) ret = min(ret, i + 1);
        }

        temp = b;
        for(int i = 1; i <= 6; ++i) {
            temp -= 20;
            if(temp < 144000) temp = 146000;
            if(temp == goal) ret = min(ret, i);
        }

        temp = a;
        for(int i = 1; i <= 6; ++i) {
            temp -= 20;
            if(temp < 144000) temp = 146000;
            if(temp == goal) ret = min(ret, i + 1);
        }

    }

    return ret;
}

int main() {
    int t; cin >> t;
    while(t --> 0) {
        double a, b; cin >> a >> b;
        char chn; cin >> chn;
        double goal; cin >> goal;
        cout << solve(1000 * a, 1000 * b, chn, 1000 * goal) << '\n';
    }

    return 0;
}