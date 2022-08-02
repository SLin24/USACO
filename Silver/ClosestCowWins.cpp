#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

struct Gap {
    ll value;
    ll fIndex;
    ll sIndex;
};
struct cmp {
    bool operator()(Gap const& p1, Gap const& p2)
    {
        return p1.value < p2.value;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll k, m, n;  cin >> k >> m >> n;

    vector<pair<ll, ll>> patches(k);
    for (int i = 0; i < k; i++) {
        ll location, tastiness; cin >> location >> tastiness;
        patches[i] = make_pair(location, tastiness);
    }

    sort(patches.begin(), patches.end());

    vector<ll> NhojCows(m);
    for (int i = 0; i < m; i++) {
        cin >> NhojCows[i];
    }
    sort(NhojCows.begin(), NhojCows.end());
    vector<int> twoCows(m + 1);
    vector<int> oneCow(m + 1);



    auto it = lower_bound(patches.begin(), patches.end(), make_pair(NhojCows[0], -1LL));
    ll sum = 0;
    for (auto t = patches.begin(); t < it; t++) {
        sum += (*t).second;
    }
    oneCow[0] = sum;
    twoCows[0] = sum;

    it = upper_bound(patches.begin(), patches.end(), make_pair(NhojCows[m - 1], (ll)(1e12)));
    sum = 0;
    for (auto t = it; t < patches.end(); t++) {
        sum += (*t).second;
    } 

    oneCow[m] = sum;
    twoCows[m] = sum;
    
    sum = 0;
    int NIndex = 0;
    for (int i = 0; i < k && NIndex < m - 1; i++) {
        if (patches[i].first <= NhojCows[0]) {
            continue;
        }
        if (patches[i].first >= NhojCows[m - 1]) {
            twoCows[NIndex + 1] = sum;
            break;
        }
        if (patches[i].first > NhojCows[NIndex] && patches[i].first < NhojCows[NIndex + 1]) {
            sum += patches[i].second;
        } else {
            twoCows[NIndex + 1] = sum;
            while(NIndex < m - 1 && patches[i].first > NhojCows[NIndex + 1]) {
                NIndex++;
            }
            sum = patches[i].second;
        }
    }
    ll windowSum = 0;
    NIndex = 0;
    int gIndex = 0;
    int right = -1;
    ll maxWindowSum = 0;
    int left = 0;
    for (int i = 0; i < k && gIndex < m - 1; i++) {
        if (patches[i].first <= NhojCows[0]) {
            continue;
        }
        if (patches[i].first >= NhojCows[m - 1]) {
            oneCow[gIndex + 1] = maxWindowSum;
            break;
        }

        if (patches[i].first > NhojCows[gIndex] && patches[i].first < NhojCows[gIndex + 1]) {
            windowSum += patches[i].second;
            if (right == -1) {
                left = i;
                int mid = patches[i].first + (patches[i].first - NhojCows[gIndex]);
                right = mid + (NhojCows[gIndex + 1] + 1 - mid) / 2;
            }
            while (patches[i].first >= right) {
                windowSum -= patches[left].second;
                left++;
                int mid = min(NhojCows[gIndex + 1], patches[left].first + (patches[left].first - NhojCows[gIndex]));
                right = mid + (NhojCows[gIndex + 1] + 1 - mid) / 2;
            }
            maxWindowSum = max(windowSum, maxWindowSum);
        } else {
            oneCow[gIndex + 1] = maxWindowSum;
            maxWindowSum = 0;
            windowSum = 0;
            while (gIndex < m - 1 && patches[i].first >= NhojCows[gIndex + 1]) {
                gIndex++;
            }
            i--;
            right = -1;
            left = -1;
        }
    }


    multiset<pair<ll, ll>, greater<pair<ll, ll>>> q;
    ll total = 0;
    
    for (int i = 0; i < m + 1; i++) {
        q.insert(make_pair(oneCow[i], i));
    }
    
    for (int cnt = 0; cnt < n && !q.empty(); cnt++) {
        total += (*q.begin()).first;
        if ((*q.begin()).second != -1) q.insert(make_pair(twoCows[(*q.begin()).second] - oneCow[(*q.begin()).second], -1));
        q.erase(q.begin());
    }
    
    cout << total << '\n';






    

}