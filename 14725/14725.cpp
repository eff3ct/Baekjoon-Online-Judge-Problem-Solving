#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

struct node {
    map<string, node> child;
};

class trie {
    private:
        node root;
    
    public:
        node& get_root() { return root; }

        void insert(node& cur_node, vector<string>& str, int level) {
            if(level == (int)str.size()) return;

            if(cur_node.child.find(str[level]) == cur_node.child.end()) 
                cur_node.child.insert({str[level], node()});
            
            insert(cur_node.child[str[level]], str, level + 1);
        }

        void DFS(node& cur_node, int level) {
            for(auto& node : cur_node.child) {
                for(int i = 0; i < level; ++i) cout << "--";
                cout << node.first << '\n';
                DFS(node.second, level + 1);
            }
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    trie t;
    for(int i = 0; i < N; ++i) {
        int K; cin >> K;
        vector<string> str(K);
        for(string& e : str) cin >> e;
        t.insert(t.get_root(), str, 0);
    }

    t.DFS(t.get_root(), 0);

    return 0;
}