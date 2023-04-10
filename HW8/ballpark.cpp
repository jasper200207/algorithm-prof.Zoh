#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N,M;
bool board[1000][1000];
int memo[1000][1000];

int main() {
    vector<vector<int>> result;
    int max = 0;

    cin >> N >> M;
    for(int i=N;i>0;i--) {
        char inp[1001];
        cin >> inp;
        for(int j=0;j<M;j++) {
            board[i-1][j] = inp[j]=='1';
        }
    }
    for(int i=N-1;i>=0;i--) {
        for(int j=M-1;j>=0;j--) {
            if(board[i][j]) memo[i][j]=0;
            else if(i==N-1 || j==M-1) memo[i][j]=1;
            else memo[i][j] = min(memo[i+1][j],min(memo[i][j+1],memo[i+1][j+1]))+1;
            if(memo[i][j] > max) {
                max = memo[i][j];
                result.clear();
                result.push_back({j+1,i+1});
            } else if(memo[i][j] == max && max > 0) {
                result.push_back({j+1,i+1});
            }
        }
    }
    sort(result.begin(), result.end());
    cout << max << " " << result.size() << endl;
    for(auto& v : result) {
        cout << v[0] << " " << v[1] << endl;
    }
}