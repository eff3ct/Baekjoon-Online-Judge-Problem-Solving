#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    while(T --> 0) {
        priority_queue<int> pq;
        int M; cin >> M;
        cout << (M + 1) / 2 << '\n';

        bool finished = false;
        int cnt = 0;
        for(int i = 1; i <= M; ++i) {
            bool finished = false;
            int a; cin >> a;
            pq.push(a);

            if(i & 1) {
                vector<int> temp;
                for(int j = 0; j < (i - 1) / 2; ++j) {
                    temp.push_back(pq.top());
                    pq.pop();
                }

                cout << pq.top() << ' ';
                
                for(auto& e : temp) pq.push(e);

                if(++cnt == 10) {
                    finished = true;
                    cout << '\n';
                    cnt = 0;
                }
            }
        }

        if(!finished) cout << '\n';
    }

    return 0;
}