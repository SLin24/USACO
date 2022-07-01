#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

vector<vector<ll>> connectedComp;
bool visited[100007]{};

void findCC(ll index, const vector<ll> *bDir, const ll id) {
    visited[index] = true;
    connectedComp[id].push_back(index);

    for (auto x: bDir[index]) {
        if (!visited[x]) {
            findCC(x, bDir, id);
        }
    }
}

ll backTrack[100007]{};
bool ok = false;
ll elem = -1;
void findCycle(ll index, const vector<ll> *dir) {
    if (ok) {
        return;
    }
    visited[index] = true;
    for (auto x: dir[index]) {
        if (visited[x]) {
            backTrack[x] = index;
            elem = x;
            ok = true;
            break;
        } else {
            backTrack[x] = index;
            findCycle(x, dir);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<ll> weights(n);
    vector<ll> bDir[n];
    vector<ll> dir[n];
    for (int i = 0; i < n; i++) {
        ll node, weight; cin >> node >> weight;
        node--;
        bDir[node].push_back(i);
        bDir[i].push_back(node);
        dir[i].push_back(node);
        weights[i] = weight;
    }

    ll cur = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            connectedComp.push_back(vector<ll>());
            findCC(i, bDir, cur);
            cur++;
        }
    }
    memset(visited, false, sizeof(visited));
    bool cycleVis[100007]{};
    ll globSum = 0;
    int sz = connectedComp.size();
    for (int i = 0; i < sz; i++) {
        ok = false;
        elem = -1;
        findCycle(connectedComp[i][0], dir);

        ll temp = backTrack[elem];
        cycleVis[elem] = true;
        ll sum = weights[elem];
        ll mn = weights[elem];
        while (temp != elem) {
            sum += weights[temp];
            mn = min(mn, weights[temp]);
            cycleVis[temp] = true;
            temp = backTrack[temp];
        }

        sum -= mn;
        for (auto x: connectedComp[i]) {
            if (!cycleVis[x]) {
                sum += weights[x];
            }
        }
        globSum += sum;
    }
    cout << globSum << '\n';
}