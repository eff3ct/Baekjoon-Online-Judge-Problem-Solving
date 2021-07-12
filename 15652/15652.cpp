// https://www.acmicpc.net/problem/15650 //
#include <iostream>
#include <vector>

using namespace std;

void printPicked(vector<int>& picked) {
    int size = picked.size();
    for(int i = 0; i < size; ++i) {
        cout << picked[i] << " ";
    }
    cout << "\n";
}

void solve(int N, int M, vector<int>& picked) {
    if(M == 0) {
        printPicked(picked);
        return;
    }

    int lowBound = picked.empty() ? 1 : picked.back();

    for(int i = lowBound; i <= N; ++i) {
        picked.push_back(i);
        solve(N, M - 1, picked);
        picked.pop_back();
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> v;
    solve(N, M, v);
    return 0;
}