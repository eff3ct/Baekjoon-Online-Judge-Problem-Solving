// https://www.acmicpc.net/problem/5639 //
#include <iostream>
#include <vector>

using namespace std;

void printPostOrder(int start, int end, vector<int>& preOrder) {
    if(start > end) return;

    int root = preOrder[start];

    int rStart = end + 1;
    for(int i = start + 1; i <= end; ++i) {
        if(root < preOrder[i]) {
            rStart = i;
            break;
        }
    }

    printPostOrder(start + 1, rStart - 1, preOrder);
    printPostOrder(rStart, end, preOrder);
    cout << root << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> preOrder;

    int x;
    while(cin >> x) preOrder.push_back(x);

    printPostOrder(0, preOrder.size() - 1, preOrder);

    return 0;
}