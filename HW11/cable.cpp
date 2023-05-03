#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
using namespace std;

vector<int> findCable(int L, queue<int> parts) {

    int part_size = parts.front(); parts.pop();
    int cnt = L/part_size;

    if(parts.empty()) return L - part_size*cnt == 0 ? (vector<int>(1,cnt)) : vector<int>();

    vector<int> result;
    int minSum = 500;
    for(;cnt >= 0;cnt--) {
        int remaining = L - part_size*cnt;
        vector<int> foundRemain = findCable(remaining, parts);
        if(!foundRemain.empty()) {
            foundRemain.insert(foundRemain.begin(),cnt);
            int sum = accumulate(foundRemain.begin(),foundRemain.end(),0);
            if(minSum > sum) {
                minSum = sum;
                result = foundRemain;
            }
        }
    }

    return result;
}

int main() {
    int L,n;
    queue<int> parts;
    cin >> L >> n;

    for(int i = 0;i < n;i++) {
        int part;
        cin >> part;
        parts.push(part);
    }

    vector<int> ans = findCable(L, parts);

    if(ans.empty()) cout << -1 << endl;
    else {
        for(int cnt : ans) {
            cout << cnt << " ";
        }
    }
    return 0;
}