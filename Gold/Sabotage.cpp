#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;


bool check(vector<double> arr, double avg) {
    double rem = 0;
    for (int i = 0; i < arr.size(); i++) {
        arr[i] -= avg;
        rem += arr[i];
    }
    double greatest = -1e12;
    double temp = -1e12;
    for (int i = 1; i < arr.size() - 1; i++) {
        temp += arr[i];
        if (temp < arr[i]) {
            temp = arr[i];
        }
        greatest = max(greatest, temp);
    }
    if (rem-greatest <= 0) {
        return true;
    } else {
        return false;
    }
}

double round3(double num) {
    return (int)(1000.0 * num + 0.5) / 1000.0;
}
double round4(double num) {
    return (int)(10000.0 * num + 0.5) / 10000.0;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);

    int n; cin >> n;
    
    vector<double> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    double left = 0, right = 10001;
    double avg = -1;
    while (left <= right) {
        double mid = left + round4((right - left) / 2.0);
        if (check(arr, mid)) {
            avg = mid;
            right = mid - 0.0001;
        } else {
            left = mid + 0.0001;
        }
    }

    cout << fixed << setprecision(3) << round3(avg) << '\n';
    


    
}
