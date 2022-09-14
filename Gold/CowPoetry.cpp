#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

int MOD = 1e9 + 7;

ll exponentiation(ll num, int pow) {
    ll fac = num;
    ll res = 1;
    while (pow > 0) {
        if (pow & 1) {
            res *= fac;
            res %= MOD;
        }
        fac *= fac;
        fac %= MOD;
        pow >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    //lucked out in that there were no duplicate words, else would have used a set to ensure no duplicates were counted
    vector<int> adj[n];
    map<ll, ll> options;
    int cnt[26]{};
    for (int i = 0; i < n; i++) {
        ll s, c; cin >> s >> c;
        adj[c-1].push_back(s);
        options[s]++;
    }

    for (int i = 0; i < m; i++) {
        char ch; cin >> ch;
        cnt[ch - 'A']++;
    }

    vector<int> poem;

    for (int i = 0; i < 26; i++) {
        if (cnt[i] > 0) poem.push_back(cnt[i]);
    }
    sort(poem.begin(), poem.end());

    ll dp[k + 1]{};
    dp[0] = 1;
    
    for (int j = 0; j <= k; j++) {
        for (auto x: options) {
            if (j - x.first >= 0) {
                dp[j] += dp[j - x.first] * x.second;
                if (dp[j] >= MOD) {
                    dp[j] %= MOD;
                }
            }
        }
    }





    vector<ll> rhymes;
    for (int i = 0; i < n; i++) {
        ll total = 0;
        for (int j = 0; j < adj[i].size(); j++) {
            total += dp[k - adj[i][j]];
            if (total >= MOD) total -= MOD;
        }
        if (total > 0) {
            rhymes.push_back(total);
        }
    }


    

    ll factor = 1;

    for (int i = 0; i < poem.size() - 1; i++) {
        factor *= rhymes.size();
        factor %= MOD;
    }

    ll ans = 1;
    for (int i = 0; i < poem.size(); i++) {
        ll temp = 0;
        for (int j = 0; j < rhymes.size(); j++) {
            temp += exponentiation(rhymes[j], poem[i]);
            if (temp >= MOD) temp -= MOD;
        }
        ans *= temp;
        ans %= MOD;
    }

    cout << ((rhymes.empty())?0:ans) << '\n';
    

    

}