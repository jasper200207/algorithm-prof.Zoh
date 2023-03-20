#include<iostream>
#include<algorithm>
using namespace std;

void flipList(int *nums, int N, int start) {
    for(int i=0;i<=N/2;i++) {
        int p1=-1, p2=-1;
        int* it = find_if(nums,nums+N,[i,start](int n){return -n==i+start;});
        if (it!=nums+N) {
            p1 = i; p2 = it-nums;
        }
        else {
            it = find_if(nums,nums+N,[i,N,start](int n){return -n==N-i+start-1;});
            if(it!=nums+N) p1 = N-i-1; p2 = it-nums;
        }
        if(p1!=-1) {
            int s = min(p1,p2), e=max(p1,p2);
            while(s <= e) {
                if(s==e) nums[s]*=-1;
                else {
                    nums[s]*=-1;nums[e]*=-1;
                    nums[s]=nums[s]^nums[e];
                    nums[e]=nums[s]^nums[e];
                    nums[s]=nums[s]^nums[e];
                }
                s++;e--;
            }
            break;
        }
    }
}

pair<int,int> get_edge(int start, int end, int*nums) {
    pair<int,int> edge = make_pair(start,end);
    for(int i=start;i<=end;i++) {
        if(nums[i-1]==i) edge.first=i+1;
        else break;
    }
    for(int i=end;i>=start;i--) {
        if(nums[i-1]==i) edge.second=i-1;
        else break;
    }
    return edge;
}

int main() {
    int N;
    cin >> N;
    for(int t=0;t<5;t++) {
        int nums[100000];
        for(int i=0;i<N;i++) cin >> nums[i];
        pair<int,int> edge = get_edge(1,N,nums);
        flipList(nums+edge.first-1,edge.second-edge.first+1,edge.first);
        edge = get_edge(edge.first,edge.second,nums);
        if(edge.first > edge.second) cout << "one\n";
        else {
            flipList(nums+edge.first-1,edge.second-edge.first+1,edge.first);
            edge = get_edge(edge.first,edge.second,nums);
            if(edge.first > edge.second) cout << "two\n";
            else cout << "over\n";
        }
    }
}