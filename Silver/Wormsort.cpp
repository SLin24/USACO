#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

void dfs(int index, const vector<int> *adj, bool *visited, int *components, int curComp) {
    for (auto x: adj[index]) {
        if (visited[x]) continue;
        visited[x] = true;
        components[x] = curComp;
        dfs(x, adj, visited, components, curComp);
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);

    int n, m; cin >> n >> m;

    vector<int> order(n);

    for (int i = 0; i < n; i++) {
        cin >> order[i];
    }
    vector<pair<pair<int,int>, int>> list;
    for (int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w; x--; y--;
        list.push_back(make_pair(make_pair(x, y), w));
    }

    int left = -1, right = 1e9; 
    int ans = -1;
    bool keepGoing = false;
    for (int i = 0; i < n; i++) {
        if (order[i] != i + 1) {
            keepGoing = true;
            break;
        }
    }
    if (!keepGoing) {
        cout << -1 << '\n';
        return 0;
    }
    while (left <= right) {
        int mid = left + (right - left) / 2;

        vector<int> adj[n];
        for (int i = 0; i < m; i++) {
            if (list[i].second >= mid) {
                adj[list[i].first.first].push_back(list[i].first.second);
                adj[list[i].first.second].push_back(list[i].first.first);
            }
        }

        int components[n];
        memset(components, -1, sizeof(components));
        int curComp = 0;
        bool visited[n]{};
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                visited[i] = true;
                components[i] = curComp;
                dfs(i, adj, visited, components, curComp);
                curComp++;
            }
        }
        bool pass = true;

        for (int i = 0; i < n; i++) {
            if (components[i] != components[order[i] - 1]) {
                pass = false;
                break;
            }
        }

        if (pass) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << ans << '\n';
}