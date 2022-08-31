#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);
    int n, k; cin >> n >> k; k--;
    vector<int> adj[n];
    for (int i = 0; i < n - 1; i++) {
        int s, d; cin >> s >> d; s--; d--;
        adj[s].push_back(d);
        adj[d].push_back(s);
    }

    int dist[n];
    memset(dist, -1, sizeof(dist));

    dist[k] = 0;
    queue<int> q;
    q.push(k);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto n: adj[x]) {
            if (dist[n] == -1) {
                dist[n] = dist[x] + 1;
                q.push(n);
            }
        }
    }
    queue<pair<int, int>> q2;
    int dist2[n];
    memset(dist2, -1, sizeof(dist2));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            q2.push(make_pair(i, -1));
            dist2[i] = 0;
            ans++;
        }
    }

    while (!q2.empty()) {
        auto x = q2.front();
        q2.pop();
        for (int n: adj[x.first]) {
            if (n == x.second) continue;
            if (dist2[n] == -1) {
                q2.push(make_pair(n, x.first));
                dist2[n] = dist2[x.first] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (adj[i].size() >= 3) {
            if (dist2[i] <= dist[i]) {
                ans -= adj[i].size() - 2;
            }
        }
    }
    
    cout << ((adj[k].size() == 1)?1:ans) << '\n';


}