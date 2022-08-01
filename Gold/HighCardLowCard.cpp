#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    int n; cin >> n;

    bool visited[2 * n]{};
    vector<int> Elsie(n);
    vector<int> Bessie;

    for (int i = 0; i < n; i++) {
        cin >> Elsie[i];
        visited[Elsie[i] - 1] = true;
    }

    for (int i = 0; i < 2 * n; i++) {
        if (!visited[i]) {
            Bessie.push_back(i + 1);
        }
    }

    vector<int> ElsieFirst(n / 2);
    vector<int> BessieFirst(n / 2);
    
    for (int i = 0; i < n / 2; i++) {
        ElsieFirst[i] = Elsie[i];
        BessieFirst[i] = Bessie[i + n / 2];
    }

    sort(ElsieFirst.begin(), ElsieFirst.end());
    sort(BessieFirst.begin(), BessieFirst.end());

    int total = 0;

    int indexE = n / 2 - 1;
    int indexB = n / 2 - 1;

    while (indexE >= 0) {
        if (BessieFirst[indexB] > ElsieFirst[indexE]) {
            total++;
            indexE--;
            indexB--;
        } else {
            indexE--;
        }
    }

    vector<int> ElsieLatter(n / 2);
    vector<int> BessieLatter(n / 2);

    for (int i = n / 2; i < n; i++) {
        ElsieLatter[i - n / 2] = Elsie[i];
        BessieLatter[i - n / 2] = Bessie[i - n / 2];
    }

    sort(ElsieLatter.begin(), ElsieLatter.end());
    sort(BessieLatter.begin(), BessieLatter.end());

    indexE = 0;
    indexB = 0;

    while (indexE < n / 2) {
        if (BessieLatter[indexB] < ElsieLatter[indexE]) {
            total++;
            indexE++;
            indexB++;
        } else {
            indexE++;
        }
    }

    cout << total << '\n';
    
}