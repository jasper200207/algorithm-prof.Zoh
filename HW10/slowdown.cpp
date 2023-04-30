#include<iostream>
#include<queue>
using namespace std;

struct Job {
    int cost = 0;
    int due_date = 0;
    int num = 0;
    bool operator>(const Job& rhs) const {
        if(cost == rhs.cost) return due_date > rhs.due_date;
        return cost > rhs.cost;
    }
};

struct JobCompare {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.due_date > rhs.due_date;
    }
};

int main() {
    int N,T,k;
    priority_queue<Job, vector<Job>, greater<Job>> max;
    priority_queue<Job, vector<Job>, JobCompare>jobs;
    cin >> N >> T >> k;
    for(int i=0;i<N;i++) {
        Job job;
        cin >> job.cost >> job.due_date;
        job.num = i+1;
        jobs.push(job);
    }
    Job miss, front_miss;
    int miss_size = 100;
    while(!jobs.empty()) {
        max.push(jobs.top());
        if(max.size() > k*jobs.top().due_date) {
            Job last = max.top();
            max.pop();
            if(last.num == front_miss.num) {
                miss_size = max.top().cost - miss.cost;
                front_miss = max.top();
            }
            if(max.top().cost > last.cost && max.top().cost - last.cost < miss_size) {
                miss = last;
                front_miss = max.top();
                miss_size = max.top().cost - last.cost;
            }
        }
        jobs.pop();
    }
    int max_cost = 0, gap = max.top().cost > miss_size ? miss_size : max.top().cost;
    while(!max.empty()) {
        max_cost += max.top().cost;
        max.pop();
    }
    cout << max_cost << " " << max_cost - gap << endl;
    return 0;
}