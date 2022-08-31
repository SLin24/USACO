#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    int n, xL, yL, xB, yB;
    cin >> n >> xL >> yL >> xB >> yB;
    map<int, stack<int>> adjX;
    map<int, stack<int>> adjY;
    vector<pair<int, int>> points;
    points.push_back(make_pair(xL, yL));
    adjX[xL].push(0);
    adjY[yL].push(0);
    for (int i = 1; i <= n; i++) {
        int x, y; cin >> x >> y;
        points.push_back(make_pair(x, y));
        adjX[x].push(i);
        adjY[y].push(i);
    }
    adjX[xB].push(n + 1);
    adjY[yB].push(n + 1);
    points.push_back(make_pair(xB, yB));
    queue<int> q;
    vector<int> dist(n + 2, -1);
    dist[0] = 0;
    q.push(0);
    while (!q.empty()) {
        auto x = q.front();
        q.pop();
        while (!adjX[points[x].first].empty()) {
            int firstElem = adjX[points[x].first].top();
            if (dist[firstElem] == -1) {
                q.push(firstElem);
                dist[adjX[points[x].first].top()] = dist[x]+1;
            }
            adjX[points[x].first].pop();
        }
        while (!adjY[points[x].second].empty()) {
            int firstElem = adjY[points[x].second].top();
            if (dist[firstElem] == -1) {
                q.push(firstElem);
                dist[firstElem] = dist[x] + 1;
            }
            adjY[points[x].second].pop();
        }
    }
    cout << ((dist[n + 1] == -1)?-1:dist[n + 1] - 1) << '\n';

}