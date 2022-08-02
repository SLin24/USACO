#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n, m; cin >> n >> m;

    ll pref[2 * m + 2]{};
    ll ends[m + 1]{};
    ll start[m + 1]{};
    for (int i = 0; i < n; i++) {
        ll s, e; cin >> s >> e;
        ends[e]++; start[s]++;
    }


    for (ll i = 0; i <= m; i++) {
        for (ll j = i; j <= m; j++) {
            if (ends[i] != 0 && ends[j] != 0) {
                if (i == j) {
                    pref[i + j + 1] += -1LL * (ends[i] * ends[i]); 
                } else {
                    pref[i + j + 1] += -2LL * (ends[i] * ends[j]);
                }           
            }
            if (start[i] != 0 && start[j] != 0) {
                if (i == j) {
                    pref[i + j] += start[i] * start[i];
                } else {
                    pref[i + j] += 2LL * start[i] * start[j];
                }
            }
        }
    }

    for (int i = 1; i <= 2 * m; i++) {
        pref[i] += pref[i - 1];
    }

    for (int i = 0; i <= 2 * m; i++) {
        cout << pref[i] << '\n';
    }
}