#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

struct Point {
    int loc, color, type;
};

bool comp(Point a, Point b) {
    if (a.loc == b.loc) {
        return a.type < b.type;
    } else {
        return a.loc < b.loc;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);
    int n; cin >> n;
    vector<int> painting(n);

    for (int i = 0; i < n; i++) {
        cin >> painting[i];
    }

    vector<int> first(n, -1);
    vector<int> last(n, -1);

    for (int i = 0; i < n; i++) {
        if (painting[i] == 0) continue;
        if (first[painting[i] - 1] == -1) {
            first[painting[i] - 1] = i;
        }
        last[painting[i] - 1] = i;
    }

    
    stack<int> stk;

    vector<Point> order;
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        if (first[i] != -1) {
            order.push_back({first[i], i + 1, 1});
            order.push_back({last[i], i + 1, 2});
        }
    }
    sort(order.begin(), order.end(), comp);
    bool fail = false;
    for (int i = 0; i < order.size(); i++) {
        if (order[i].type == 1) {
            stk.push(order[i].color);
        } else {
            if (stk.top() != order[i].color) {
                fail = true;
                break;
            } else {
                stk.pop();
            }
        }
        maxLength = max((int)(stk.size()), maxLength);
    }

    if (fail) {
        cout << -1 << '\n';
    } else {
        cout << maxLength << '\n';
    }

}