#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;
bool fail = false;
void dfs(int index, const vector<pair<int, bool>> *adj, int p, vector<int>& colors) {
    for (auto x: adj[index]) {
        if (x.first == p) continue;
        int type = 1;
        if (colors[index] == 2) {
            type = -1;
        }
        if (!x.second) {
            type *= -1;
        }
        if (type == -1) {
            if (colors[x.first] != 0) {
                if (colors[x.first] != 2) {
                    fail = true;
                }
            } else {
                colors[x.first] = 2;
                dfs(x.first, adj, index, colors);
            }
        } else {
            if (colors[x.first] != 0) {
                if (colors[x.first] != 1) {
                    fail = true;
                }
            } else {
                colors[x.first] = 1;
                dfs(x.first, adj, index, colors);
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);

    int n, m; cin >> n >> m;


    vector<pair<pair<int, int>, bool>> instructions;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        bool truth; 
        char type; cin >> type;
        if (type == 'T') {
            truth = true;
        } else {
            truth = false;
        }
        instructions.emplace_back(make_pair(make_pair(a, b), truth));
    }

    //binary search and creating a graph

    //bipartite matching no contradictions

    //dfs regardless if color assigned as long as there are paths to verify all statemetns

    int left = 1, right = m;
    int ans = 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        vector<pair<int, bool>> adj[n]; 
        //1 is truthteller, 2 is liar
        //if current type is 2 and T, then adjacent will be 2
        //if current type is 2 and F, then adjacent will be 1
        //if current type is 1 and T, then adjacent will be 1
        //if current type is 1 and F, then adjacent will be 2

        for (int i = 0; i < mid; i++) {
            adj[instructions[i].first.first].push_back(make_pair(instructions[i].first.second, instructions[i].second));
            adj[instructions[i].first.second].push_back(make_pair(instructions[i].first.first, instructions[i].second));
        }

        vector<int> colors(n, 0);
        fail = false;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() > 0 && colors[i] == 0) {
                colors[i] = 1;
            }
            dfs(i, adj, -1, colors);
        }
        if (fail) {
            right = mid - 1;
        } else {
            ans = mid;
            left = mid + 1;
        }
    }

    cout << ans << '\n';


}
