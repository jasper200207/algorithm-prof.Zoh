#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#define MAX 1000000000
using namespace std;

typedef struct Node {
    int to;
    int distance;
} Node;

typedef struct Solution {
    string path;
    int distance;
} Solution;

int main() {
    vector<Node> graph[26];
    int n; cin >> n;
    for(int i=0;i<n;i++) {
        char v1, v2;
        int distance; 
        cin >> v1 >> v2 >> distance;
        graph[v1-'a'].push_back({v2-'a', distance});
        graph[v2-'a'].push_back({v1-'a', distance});
    }
    Solution solution = {"-1", MAX};
    for(int root=0; root<26; root++) {
        for(Node start_node : graph[root]) {
            for(Node end_node : graph[root]) {
                if(start_node.to >= end_node.to) continue;
                bool checked[26] = {};
                checked[root] = true;
                int distance[26], prev[26], check_cnt=1;
                fill_n(distance, 26, MAX);
                distance[root] = distance[start_node.to] = 0;
                int now = start_node.to;
                while(check_cnt < 26) {
                    for(int i=0;i<graph[now].size();i++) {
                        Node next = graph[now][i];
                        if(!checked[next.to] && distance[next.to] > distance[now] + next.distance) {
                            distance[next.to] = distance[now] + next.distance;
                            prev[next.to] = now;
                        }
                    }
                    checked[now] = true;
                    check_cnt++;
                    int min = MAX;
                    for(int i=0;i<26;i++) {
                        if(!checked[i] && distance[i] < min) {
                            min = distance[i];
                            now = i;
                        }
                    }
                    if(now == end_node.to) break;
                }
                if(solution.distance > distance[end_node.to] + start_node.distance + end_node.distance) {
                    solution.distance = distance[end_node.to] + start_node.distance + end_node.distance;
                    solution.path = (char)(root + 'a');
                    int now = end_node.to;
                    while(now != start_node.to) {
                        solution.path = " " + solution.path;
                        solution.path = (char)(now + 'a') + solution.path;
                        now = prev[now];
                    }
                    solution.path = " " + solution.path;
                    solution.path = (char)(start_node.to + 'a') + solution.path;
                    solution.path = " " + solution.path;
                    solution.path = (char)(root + 'a') + solution.path;
                }
            }
        }
    }
    cout << solution.path << endl;
}