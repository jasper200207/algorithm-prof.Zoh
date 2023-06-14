#include<iostream>
#include<vector>
#include<utility>
#include<string>
#define MAX 1000000000
using namespace std;

int graph[26][26];

typedef pair<string,int> Solution;

class Path {
    private:
        int checkList[26];
        vector<int> path;
        vector<int> distance;
    public:
        Path() {
            fill_n(checkList, 26, -1);
        }
        bool check(int node) {
            return checkList[node] != -1;
        }
        void add(int node) {
            checkList[node] = path.size();
            distance.push_back(path.empty()?0:graph[path.back()][node]);
            path.push_back(node);
        }
        Solution get_cycle(int node) {
            if(!check(node)) return make_pair("", MAX);
            string cycle = "";
            int total = 0;
            for(int i=checkList[node];i<path.size();i++) {
                cycle += (char)(path[i]+'a');
                total += distance[i];
            }
            return make_pair(cycle+(char)(node+'a'), total+graph[path.back()][node]);
        }
};

Solution dfs(Path path, int back_node) {
    Solution solution = make_pair("", MAX);
    for(int i=0;i<26;i++) {
        if(back_node == i) continue;
        else if(back_node != -1 && graph[back_node][i] == MAX) continue;;
        Solution cycle = make_pair("", MAX);
        if(path.check(i)) {
            cycle = path.get_cycle(i);
        }else {
            Path next = path;
            next.add(i);
            cycle = dfs(next, i);
        }
        if(cycle.second < solution.second) solution = cycle;
    }
    return solution;
}

int main() {
    fill(&graph[0][0], &graph[0][0] + sizeof(graph) / sizeof(int), MAX);
    int n; cin >> n;
    for(int i=0;i<n;i++) {
        char node1, node2; int distance;
        cin >> node1 >> node2 >> distance;
        graph[node1-'a'][node2-'a'] = graph[node2-'a'][node1-'a'] = distance;
    }
    Solution solution = dfs(Path(), -1);
    if(solution.second == MAX) cout << -1 << endl;
    else cout << solution.first << endl;
}