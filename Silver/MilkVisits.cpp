#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

bool visited[100007]{};
struct DSU {
	vector<ll> p;
	void init(ll N) {p = vector<ll>(N, -1);}
	ll get(ll a) {return ((p[a] < 0)?a:p[a] = get(p[a]));}
	bool same_set(ll a, ll b) {return get(a) == get(b);}
	bool unite(ll a, ll b) {
		a = get(a); b = get(b);
		if (a==b)return false;
		if (p[a] > p[b]) swap(a, b);
		p[a] += p[b]; p[b] = a;
		return true;
	}
};
DSU D;
void dfs(ll index, const vector<int> *adj, const string& key, const char& type) {
	for (auto x: adj[index]) {
		if (!visited[x] && key[x] == type) {
			visited[x] = true;
			D.unite(x, index);
			dfs(x, adj, key, type);
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("milkvisits.in", "r", stdin);
	freopen("milkvisits.out", "w", stdout);

	ll n, m; cin >> n >> m;
	D.init(n);
	string key; cin >> key;
	vector<int> adj[n];
	for (int i = 0; i < n - 1; i++) {
		ll x, y; cin >> x >> y; x--; y--;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	for (ll i = 0; i < n; i++) {
		if (!visited[i]) {
			visited[i] = true;
			dfs(i, adj, key, key[i]);
		}
	}
	string ans = "";
	for (int i = 0; i < m; i++) {
		ll start, targ; char type; cin >> start >> targ >> type; start--; targ--;
		if (key[start] != type && D.same_set(start, targ)) {
			ans += '0';
		} else {
			ans += '1';
		}
	}
	cout << ans << '\n';
	
}