#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

bool solve(vector<int> &totalMembers, vector<int> &totalStrength, int c, int v) {
    for (int i = 0; i < 3; ++i) {
        if (!totalMembers[i]) {
            continue;
        }
        --totalMembers[i];
        for (int j = i; j < 3; ++j) {
            if (!totalMembers[j]) {
                continue;
            }
            --totalMembers[j];
            if (c * (totalStrength[i] + totalStrength[j]) >= v) {
                return true;
            }
            ++totalMembers[j];
        }
        ++totalMembers[i];
    }
    
    return false;
}

bool check(vector<int> totalMembers, vector<int> totalStrength, vector<int> &speedFactor, int v) {
    for (int &c : speedFactor) {
        if (!solve(totalMembers, totalStrength, c, v)) {
            return false;
        }
    }
    return true;
}
    
int main() {
    vector<int> totalMembers(3);
    int n = 0;
    for (int &m : totalMembers) {
        cin >> m;
        n += m;
    }
    vector<int> totalStrength(3);
    for (int &s : totalStrength) {
        cin >> s;
    }
    vector<int> speedFactor(n / 2);
    for (int &c : speedFactor) {
        cin >> c;
    }
    
    sort(speedFactor.begin(), speedFactor.end());
    
    int low = 0;
    int high = pow(10, 9);
    
    while (high - low > 1) {
        int mid = (high + low) / 2;
        if (check(totalMembers, totalStrength, speedFactor, mid)) {
            low = mid;
        }
        else {
            high = mid;
        }
    }
    
    cout << low << endl;
    
    return 0;
}
    