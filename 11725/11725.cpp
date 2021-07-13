// https://www.acmicpc.net/problem/11725 //
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void solve(vector<int>*& link, int N) {
    int* pArr = new int[100001];
    bool* visit = new bool[100001];
    fill_n(visit, 100001, false);
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int node : link[x]) {
            if(!visit[node]) {
                pArr[node] = x;
                visit[node] = true;
                q.push(node);
            }
        }
    }

    for(int i = 2; i <= N; ++i) {
        cout << pArr[i] << "\n";
    }

    delete[] pArr;
    delete[] visit;
}

int main() {
    int N;
    cin >> N;
    vector<int>* link = new vector<int>[100001];
    for(int i = 0; i < (N - 1); ++i) {
        int a, b;
        cin >> a >> b;
        link[a].push_back(b);
        link[b].push_back(a);
    }
    solve(link, N);
    delete[] link;
    return 0;
}