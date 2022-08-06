#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;
ll total = 0;
void dfs(const vector<pair<ll, ll>> *adj, int index, int p, ll curRel, ll maxSum) {
    for (auto x: adj[index]) {
        if (x.first != p) {
            if (min(curRel, x.second) >= maxSum) {
                total++;
                dfs(adj, x.first, index, min(curRel, x.second), maxSum);
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);


    int n, q; cin >> n >> q;

    vector<pair<ll, ll>> adj[n];

    for (int i = 0; i < n - 1; i++) {
        ll f, s, k; cin >> f >> s >> k;
        f--; s--;
        adj[f].emplace_back(make_pair(s, k));
        adj[s].emplace_back(make_pair(f, k));
    }
    for (int i = 0; i < q; i++) {
        ll start, maximum; cin >> maximum >> start;
        start--;
        total = 0;
        dfs(adj, start, -1, 2e9, maximum);
        cout << total << '\n';
    }
}