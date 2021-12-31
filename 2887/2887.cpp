#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;
typedef long long ll;
typedef struct _Coord {
    int x;
    int y;
    int z;
    int idx;

    _Coord() {
        x = 0;
        y = 0;
        z = 0;
        idx = -1;
    }
} Coord;

int find(int a, vector<int>& parent) {
    if(a == parent[a]) return a;
    else return parent[a] = find(parent[a], parent);
}

void uni(int a, int b, vector<int>& parent) {
    int aP = find(a, parent);
    int bP = find(b, parent);

    if(aP == bP) return;

    if(aP < bP) parent[bP] = aP;
    else parent[aP] = bP;
}

bool cmp_x(const Coord& A, const Coord& B) {return A.x < B.x;}
bool cmp_y(const Coord& A, const Coord& B) {return A.y < B.y;}
bool cmp_z(const Coord& A, const Coord& B) {return A.z < B.z;};

ll solve(vector<Coord>& coord) {
    vector<pair<int, pair<int, int>>> edge;

    sort(coord.begin(), coord.end(), cmp_x);
    for(int i = 0; i < (int)coord.size() - 1; ++i) 
        edge.push_back({abs(coord[i].x - coord[i + 1].x), {coord[i].idx, coord[i + 1].idx}});

    sort(coord.begin(), coord.end(), cmp_y);
    for(int i = 0; i < (int)coord.size() - 1; ++i)
        edge.push_back({abs(coord[i].y - coord[i + 1].y), {coord[i].idx, coord[i + 1].idx}});

    sort(coord.begin(), coord.end(), cmp_z);
    for(int i = 0; i < (int)coord.size() - 1; ++i)
        edge.push_back({abs(coord[i].z - coord[i + 1].z), {coord[i].idx, coord[i + 1].idx}});

    sort(edge.begin(), edge.end());

    vector<int> parent((int)coord.size());
    iota(parent.begin(), parent.end(), 0);

    ll ret = 0;
    for(auto& element : edge) {
        if(find(element.second.first, parent) != find(element.second.second, parent)) {
            ret += element.first;
            uni(element.second.first, element.second.second, parent);
        }
    }

    return ret;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<Coord> coord(N);
    for(int i = 0; i < N; ++i) {
        cin >> coord[i].x >> coord[i].y >> coord[i].z;
        coord[i].idx = i;
    }

    ll ret = solve(coord);
    cout << ret;

    return 0;
}