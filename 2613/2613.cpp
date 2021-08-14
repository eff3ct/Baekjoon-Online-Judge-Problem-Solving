// https://www.acmicpc.net/problem/2613 //
#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;

int maxValue = INF;

void solvePS(vector<int>& A, int start, int end, int& M) {
    if(start > end) {
        vector<int> c;
        cout << maxValue << '\n';
        int nowSum = 0, cnt = 0;
        for(int i = 0; i < A.size(); ++i) {
            nowSum += A[i];
            cnt += 1;
            if(nowSum > maxValue) {
                c.push_back(cnt - 1);
                nowSum = A[i];
                cnt = 1;
            }
        }
        c.push_back(cnt);

        int idx;
        while(c.size() != M) {
            for(int i = 0; i < c.size(); ++i) {
                if(c[i] > 1) idx = i;
            }
            c[idx] -= 1;
            c.insert(c.begin() + idx, 1);
        }
        
        for(auto& element : c) cout << element << " ";

        return;
    }

    int mid = (start + end) / 2;

    int nowSum = 0, groupCount = 1;
    bool isPossible = true;
    for(int i = 0; i < A.size(); ++i) {
        if(A[i] > mid) isPossible = false;
        nowSum += A[i];
        if(nowSum > mid) {
            groupCount++;
            nowSum = A[i];
        }       
    }

    if(groupCount > M || isPossible == false) solvePS(A, mid + 1, end, M);
    else {
        maxValue = min(maxValue, mid);
        solvePS(A, start, mid - 1, M);
    }
        
}

int main() {
    int N, M; cin >> N >> M;

    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    solvePS(A, 1, 30000, M);

    return 0;
}