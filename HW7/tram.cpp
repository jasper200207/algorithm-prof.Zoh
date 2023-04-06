#include<iostream>
#include<vector>
#include<algorithm>
#define INF 0x7fffffff - 1
#define min(x) *min_element(x.begin(), x.end())
using namespace std;

int main() {
    int cost_1, cost_d, cost_3d, cost_w, N;
    vector<vector<int>> histories = { {0, 0, 0, 0} };
    cin >> cost_1 >> cost_d >> cost_3d >> cost_w;
    cin >> N;
    for(int i=0;i<N;i++) {
        int d, r;
        cin >> d >> r;
        while(histories.size() <= d) {
            int now = histories.size();
            histories.push_back({
                min(histories.back()) + cost_1*(now==d ? r : 0),
                min(histories.back()) + cost_d*(now==d),
                min(histories[max(0,now-3)]) + cost_3d,
                now%7==1 ? min(histories.back()) + cost_w : histories[((now-1)/7)*7 + 1][3]
            });
        }
    }
    cout << min(histories.back());
}