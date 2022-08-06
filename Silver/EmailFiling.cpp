#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;

    while (t--) {
        int m, n, k; cin >> m >> n >> k;
        vector<int> emails(n);
        multiset<int> list;
        for (int i = 0; i < n; i++) {
            int folder; cin >> folder;
            emails[i] = folder;
            list.insert(folder);
        }

        for (int i = 0; i < k; i++) {
            list.erase(list.find(emails[i]));
        }
        int topMail = 1;
        int bottomMail = k;
        int shift = 0;
        bool bContinue = false;
        while (!emails.empty()) {
            bContinue = false;
            for (int i = shift; i < min((int)(emails.size()), shift + k); i++) {
                if (emails[i] >= topMail && emails[i] <= bottomMail) {
                    auto it = emails.begin();
                    advance(it, i);
                    emails.erase(it);
                    i--;
                    if (emails.size() > shift + k - 1) list.erase(list.find(emails[shift + k - 1]));
                    if (shift + k - 1 >= emails.size()) {
                        shift = emails.size() - k;
                        bContinue = true;
                        break;
                    }
                }
            }
            if (bContinue) continue;
            
            int minimum = -1;
            if (!list.empty()) {
                minimum = *list.begin();
            }
            if (minimum == -1 && bottomMail == m) {
                break;
            }
            if ((minimum == -1 || minimum > topMail) && bottomMail != m) {
                topMail++;
                bottomMail++;
            } else if (minimum == topMail) {
                if ((shift + k - 1 >= emails.size() - 1)) {
                    if (bottomMail == m) {
                        break;
                    } else {
                        topMail++;
                        bottomMail++;
                    }
                }
                shift++;
                if (emails.size() > shift + k - 1) list.erase(list.find(emails[shift + k - 1]));
            }
        }

        cout << (emails.empty()?"YES":"NO") << '\n';
    }
}