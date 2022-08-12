#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

bool dist(pair<ll, ll> a, pair<ll, ll> b, ll X) {
    ll x = abs(a.first - b.first);
    x *= x;
    ll y = abs(a.second - b.second);
    y *= y;
    if (x + y <= X) {
        return true;
    }
    return false;
}

void dfs(int index, const vector<int> *adj, bool *visited) {
    for (auto x: adj[index]) {
        if (visited[x]) continue;
        visited[x] = true;
        dfs(x, adj, visited);
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    int n; cin >> n;
    vector<pair<ll, ll>> cows(n);
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        cows[i] = make_pair(x, y);
    }

    ll left = 0, right = 1e10;
    ll ans = -1;
    while (left <= right) {
        ll mid = left + (right - left) / 2;

        vector<int> adj[n];
        bool visited[n]{};

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dist(cows[i], cows[j], mid)) {
                    adj[i].emplace_back(j);
                    adj[j].emplace_back(i);
                }
            }
        }
        dfs(0, adj, visited);
        bool pass = true;
        for (auto x: visited) {
            if (!x) {
                pass = false;
                break;
            }
        }
        if (pass) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << ans << '\n';
}