#include<iostream>
#include<set>
#include<queue>
#include<vector>
using namespace std;

typedef struct Bucket {
    int capacity=0;
    int amount=0;
    bool operator<(const Bucket& other) const {
        return capacity < other.capacity || (capacity == other.capacity && amount < other.amount);
    }
}Bucket;

vector<Bucket> pour(vector<Bucket> state, int from, int to) {
    int pourAmount = min(state[from].amount, state[to].capacity - state[to].amount);
    state[from].amount -= pourAmount;
    state[to].amount += pourAmount;
    return state;
}

int main() {
    int cnt=1;
    queue<vector<Bucket>> q;
    vector<Bucket> buckets = {Bucket(), Bucket(), Bucket()};
    set<vector<Bucket>> states;
    for(int i=0;i<3;i++) {
        cin >> buckets[i].capacity;
    }
    for(int i=0;i<3;i++) {
        cin >> buckets[i].amount;
    }
    q.push(buckets);
    states.insert(buckets);
    while(!q.empty()) {
        vector<Bucket> state = q.front();
        q.pop();
        for(int i=0;i<3;i++) {
            for(vector<Bucket> next : {pour(state, i, (i+1)%3), pour(state, i, (i+2)%3)}) {
                if(states.find(next) == states.end()) {
                    q.push(next);
                    states.insert(next);
                    cnt++;
                }
            }
        }
    }
    cout << cnt;
}