#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);

    int n; cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    vector<int> base;
    vector<stack<int>> top;
    int ans = n;
    int highest = 0;
    bool fail = false;
    for (int i = 0; i < n; i++) {
        if (arr[i] < highest) {
            ans = i;
            break;
        }
        if (base.empty() || arr[i] > *base.rbegin()) {
            base.push_back(arr[i]);
            top.push_back(stack<int>());
            top[top.size() - 1].push(arr[i]);
        } else {
            int idx = upper_bound(base.begin(), base.end(), arr[i]) - base.begin();
            while (!top[idx].empty()) {
                if (arr[i] < top[idx].top()) {
                    top[idx].push(arr[i]);
                    break;
                } else {
                    if (highest > top[idx].top()) {
                        fail = true;
                        ans = i;
                    } else {
                        highest = top[idx].top();
                        top[idx].pop();
                    }
                }
            }
            if (fail) {
                break;
            }
        }
    }
    cout << ans << '\n';
}