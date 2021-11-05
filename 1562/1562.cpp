#include <iostream>
#include <vector>
#define MOD 1000000000

using namespace std;

vector<vector<vector<int>>> dp;
int N; 

int solve(int number, int length, int visited) {
    if(number < 0 || number > 9) return 0;
    
    if(length == N) {
        if(visited == (1 << 10) - 1) return 1;
        else return 0;
    }

    int& ret = dp[number][length][visited];
    if(ret != - 1) return ret;

    return ret = (solve(number - 1, length + 1, visited | (1 << (number - 1))) 
    + solve(number + 1, length + 1, visited | (1 << (number + 1)))) % MOD;
}

int main() {
    cin >> N;

    dp.resize(10, vector<vector<int>>(N, vector<int>(1 << 10, -1)));
    
    int ret = 0;
    for(int i = 1; i <= 9; ++i) {
        int visited = 1 << i;
        ret += solve(i, 1, visited);
        ret %= MOD;
    }

    cout << ret;

    return 0;
}