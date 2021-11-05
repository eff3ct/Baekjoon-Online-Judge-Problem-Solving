#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

int main() {
    ll n; cin >> n;

    vector<ll> ret;
    double eulerPhi = n;

    int sqrtN = sqrt(n);
    for(int div = 2; div <= sqrtN; ++div) {
        while(n % div == 0) {
            n /= div;
            ret.push_back(div);
        }
    }
    if(n > 1) ret.push_back(n);

    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    
    for(auto& p : ret) eulerPhi *= (double)(p - 1) / p;

    cout << (ll)eulerPhi;

    return 0;
}