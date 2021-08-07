// https://www.acmicpc.net/problem/1644 //
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> isPrime(4000001, true);

vector<int> getPrimeNumber(int& N) {
    vector<int> res;
    isPrime[0] = false;
    isPrime[1] = false;
    for(int i = 2; i <= (int)sqrt(N); ++i) {
        if(isPrime[i]) {
            for(int j = i*i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for(int i = 2; i <= N; ++i) {
        if(isPrime[i]) res.push_back(i);
    }

    return res;
}

void solve(vector<int>& number, int& N) {
    int res = 0;
    
    int nowSum = 0, low = 0, high = 0;

    while(true) {
        if(nowSum >= N) nowSum -= number[low++];
        else if(nowSum < N && high == number.size()) break;
        else nowSum += number[high++];

        if(nowSum == N) res++;
    }

    cout << res;
}

int main() {
    int N; cin >> N;
    vector<int> primeVector = getPrimeNumber(N);

    solve(primeVector, N);

    return 0;
}