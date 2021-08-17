#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> ID; int id;
vector<bool> isSCC;
vector<vector<int>> SCC;
stack<int> stackSCC;

int DFS(vector<vector<int>>& adj, int node) {
    ID[node] = ++id;
    stackSCC.push(node);

    int parent = ID[node];

    for(auto& element : adj[node]) {
        int nextNode = element;
        if(ID[nextNode] == 0) parent = min(parent, DFS(adj, nextNode));
        else if(!isSCC[nextNode]) parent = min(parent, ID[nextNode]);
    }

    if(parent == ID[node]) {
        vector<int> elementSCC;
        while(true) {
            int topNode = stackSCC.top();
            stackSCC.pop();

            elementSCC.push_back(topNode);
            isSCC[topNode] = true;

            if(topNode == node) break;
        }
        SCC.push_back(elementSCC);
    }

    return parent;
}

void solve(vector<vector<int>>& adj, int& V) {
    for(int i = 1; i <= V; ++i) {
        if(ID[i] == 0) DFS(adj, i);
    }

    cout << SCC.size() << '\n';
    
    for(auto& element : SCC) sort(element.begin(), element.end());
    sort(SCC.begin(), SCC.end());

    for(auto& element : SCC) {
        for(auto& x : element) cout << x << " ";
        cout << "-1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int V, E; cin >> V >> E;

    isSCC.resize(V + 1, false);
    ID.resize(V + 1, 0);
    vector<vector<int>> adj(V + 1);
    for(int i = 0; i < E; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }

    solve(adj, V);

    return 0;
}