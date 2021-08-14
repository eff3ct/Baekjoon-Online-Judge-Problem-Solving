// https://www.acmicpc.net/problem/2672 //
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cctype>

using namespace std;

class segTree {
    private:
        vector<int> sum;
        vector<int> cnt;

    public:
        segTree(int N) {
            sum.resize(N * 4);
            cnt.resize(N * 4);
        }

        void updateRange(int start, int end, int node, int left, int right, int diff) {
            if(start > right || end < left) return;

            if(left <= start && end <= right) cnt[node] += diff;
            else {
                int mid = (start + end) / 2;
                updateRange(start, mid, node * 2, left, right, diff);
                updateRange(mid + 1, end, node * 2 + 1, left, right, diff);
            }

            if(cnt[node]) sum[node] = end - start + 1;
            else if(start != end) sum[node] = sum[node * 2] + sum[node * 2 + 1];
            else sum[node] = 0;
        }

        int getHeight() {
            return sum[1];
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    segTree Tree(20000);

    vector<tuple<int, int, int, int>> line;
    for(int i = 0; i < N; ++i) {
        double x1, y1, a, b; cin >> x1 >> y1 >> a >> b;
        x1 *= 10; y1 *= 10; a *= 10; b *= 10;
        x1 += 0.1; y1 += 0.1; a += 0.1; b += 0.1;
        line.push_back({(int)x1, (int)y1, (int)(y1 + b), 1});
        line.push_back({(int)(x1 + a), (int)y1, (int)(y1 + b), -1});
        /*          (x2, y2)
          (x1, y1)          */
        //x1 , y1 ~ y2 , start = 1
        //x2 , y1 ~ y2 , end = -1
        //sort by x
        //(x, y1, y2, isStart)
    }

    sort(line.begin(), line.end());
    int ret = 0;
    int prev = get<0>(line[0]);
    for(auto& element : line) {
        int x = get<0>(element);
        int y1 = get<1>(element);
        int y2 = get<2>(element);
        int diff = get<3>(element);

        int deltaX = x - prev;
        ret += Tree.getHeight() * deltaX;
        prev = x;

        Tree.updateRange(1, 20000, 1, y1, y2 - 1, diff);
    }

    double res = (double)ret / 100.00;
    cout << fixed;
    cout.precision(2);
    if(res == (int)res) cout << (int)res;
    else cout << res;

    return 0;
}