#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;
int startIndex, endIndex;
bool visited[200007];
vector<ll> CC[200007];
void dfs(const int index, const int compIndex, const vector<ll> *adj, const int n) {
    for (auto x: adj[index]) {
        if (!visited[x]) {
            if (x == n - 1) {
                endIndex = compIndex;
            } else if (x == 0) {
                startIndex = compIndex;
            }
            visited[x] = true;
            CC[compIndex].emplace_back(x);
            dfs(x, compIndex, adj, n);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;

    while (t--) {
        int n, m; cin >> n >> m;

        vector<ll> adj[n];

        memset(visited, false, sizeof(visited));
        for (int i = 0; i < m; i++) {
            int start, dest; cin >> start >> dest;
            start--; dest--;
            adj[start].emplace_back(dest);
            adj[dest].emplace_back(start);
        }

        int compIndex = 0;
        startIndex = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (i == n - 1) endIndex = compIndex;
                
                CC[compIndex].emplace_back(i);
                visited[i] = true;
                dfs(i, compIndex, adj, n);
                compIndex++;
            }
        }

        for (int i = 0; i < compIndex; i++) {
            sort(CC[i].begin(), CC[i].end());
        }

        if (startIndex == endIndex) {
            cout << 0 << '\n';
        } else {
            ll middleOption = 1e18;
            for (int i = 0; i < compIndex; i++) {
                if (i == startIndex || i == endIndex) continue;
                ll closest1 = 1e9; ll closest2 = 1e9;
                for (auto x: CC[i]) {

                    auto it = lower_bound(CC[startIndex].begin(), CC[startIndex].end(), x);
                    if (it != CC[startIndex].end()) {
                        closest1 = min(closest1, abs((*it) - x));
                    }
                    if (it != CC[startIndex].begin()) closest1 = min(closest1, abs((*(--it)) - x));
                    

                    it = lower_bound(CC[endIndex].begin(), CC[endIndex].end(), x);
                    if (it != CC[endIndex].end()) {
                        closest2 = min(closest2, abs((*it) - x));
                    }
                    if (it != CC[endIndex].begin()) closest2 = min(closest2, abs((*(--it)) - x));
                }
                middleOption = min(middleOption, closest1 * closest1 + closest2 * closest2);
            }

            ll directOption = 1e18;

            for (auto x: CC[startIndex]) {
                auto it = lower_bound(CC[endIndex].begin(), CC[endIndex].end(), x);
                if (it != CC[endIndex].end()) directOption = min(directOption, abs((*it) - x));
                if (it != CC[endIndex].begin()) directOption = min(directOption, abs((*(--it)) - x));
            }
            directOption *= directOption;
            cout << min(directOption, middleOption) << '\n';



        }

        for (int i = 0; i < compIndex; i++) {
            CC[i].clear();
        }
        
    }

    
}