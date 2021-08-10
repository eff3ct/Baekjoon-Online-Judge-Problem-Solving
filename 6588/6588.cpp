// https://www.acmicpc.net/problem/6588 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> isPrime(1000001, true);

void solve(int& n, vector<int>& primeVector) {
    int a = 0;
    
    while(true) {
        if(isPrime[n - primeVector[a]]) break;
        a++;
    }

    cout << n << " = " << primeVector[a] << " + " << n - primeVector[a] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //eratosthenes's sieve
    isPrime[0] = isPrime[1] = false;
    for(int i = 2; i <= 1000; ++i) {
        if(isPrime[i]) {
            for(int j = i * i; j <= 1000000; j += i) {
                isPrime[j] = false;
            }
        }
    }

    //save prime numbers
    vector<int> primeVector;
    for(int i = 3; i <= 1000000; ++i) {
        if(isPrime[i]) primeVector.push_back(i);
    }

    //solve
    while(true) {
        int n; cin >> n;
        if(n == 0) break;
        solve(n, primeVector);
    }

    return 0;
}