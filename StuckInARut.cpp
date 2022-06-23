#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

int children[1000]{};
bool vis[1000]{};

struct Cow {
    ll x, y, index;
};

bool compX(const Cow& a, const Cow& b) {
    return a.x < b.x;
}

bool compY(const Cow& a, const Cow& b) {
    return a.y < b.y;
}


int update(int index, const vector<int> *adj) {
    if (vis[index]) {
        return children[index];
    }
    vis[index] = true;
    if (adj[index].empty()) {
        children[index] = 0;
    } else {
        children[index] += adj[index].size();
        for (int x: adj[index]) {
            children[index] += update(x, adj);
        }
    }
    return children[index];
    
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;

    vector<Cow> north;
    vector<Cow> east;
    for (int i = 0; i < n; i++) {
        char direction; int x, y; cin >> direction >> x >> y;
        if (direction == 'N') {
            north.push_back({x, y, i});
        } else {
            east.push_back({x, y, i});
        }
    }

    bool visited[n];
    memset(visited, false, sizeof(visited));
    sort(north.begin(), north.end(), compX);
    sort(east.begin(), east.end(), compY);

    vector<int> adj[n];
    for (auto nC: north) {
        for (auto eC: east) {
            if (!visited[eC.index] && nC.x > eC.x && eC.y > nC.y) {
                if (nC.x - eC.x > eC.y - nC.y) {
                    visited[eC.index] = true;
                    adj[nC.index].push_back(eC.index);
                } else if (nC.x - eC.x < eC.y - nC.y) {
                    adj[eC.index].push_back(nC.index);
                    break;
                }
            }
        }
    }


    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            update(i, adj);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << children[i] << '\n';
    }
    
    
}
