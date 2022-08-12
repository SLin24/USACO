#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

bool pass(const vector<ll>& coords, ll index, ll power) {
    ll i = index;
    ll upd = i;
    if (index == 0) return true;
    while(i >= 0 && power - 10 > 0) {
        upd = i;
        power-=10;
        ll lowerBound = coords[i] - power;
        while (i > 0 && coords[i - 1] >= lowerBound) {
            i--;
        }

        if (upd == i) {
            return false;
        } else if (i == 0) {
            return true;
        }
        
    }
    return false;
}

bool test(const vector<ll>& coords, ll index, ll power) {
    ll i = index;
    ll upd = i;
    if (i == coords.size() - 1) return true;
    while(i < coords.size() && power - 10 > 0) {
        upd = i;
        power-=10;
        ll upperBound = coords[i] + power;
        while (i < coords.size() - 1 && coords[i + 1] <= upperBound) {
            i++;
        }

        if (upd == i) {
            return false;
        } else if (i == coords.size() - 1) {
            return true;
        }
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    int n; cin >> n;

    vector<ll> coords(n);

    for (int i = 0; i < n; i++) {
        cin >> coords[i];
        coords[i] *= 10;
    }
    sort(coords.begin(), coords.end());
    
    ll left = 0, right = 1e11;
    ll ans = -1;
    while (left <= right) {
        ll mid = left + (right - left) / 2;

        ll indexL = 0, indexR = coords.size() - 1;
        ll ansIndex = 0;
        
        while (indexL <= indexR) {
            ll midIndex = indexL + (indexR - indexL) / 2;
            if (pass(coords, midIndex, mid)) {
                ansIndex = midIndex;
                indexL = midIndex + 1;
            } else {
                indexR = midIndex - 1;
            }
        }
        
        ll maxRange = coords[ansIndex] + 2 * mid; 
        ll finalStart = -1;
        for (int i = ansIndex; i < n; i++) {
            if (coords[i] <= maxRange) {
                finalStart = i;
            } else {
                break;
            }
        }
        if (test(coords, finalStart, mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }

    }
    cout << fixed;
    cout << setprecision(1) << (double)(ans / 10.0) << '\n';
    
}