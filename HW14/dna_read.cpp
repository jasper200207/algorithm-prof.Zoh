#include<iostream>
#include<vector>
#define MAX_RADIX 100
using namespace std;

vector<string> dna_vec;

vector<vector<int>> get_radix_vec(vector<int> dnas, int radix) {
    vector<vector<int>> radix_vec(6);
    for(int i : dnas) {
        string dna_str = dna_vec[i];
        if(dna_str.size() <= radix) {
            radix_vec[0].push_back(i);
            continue;
        }
        switch (dna_str[radix])
        {
            case 'a' : radix_vec[1].push_back(i); break;
            case 'c' : radix_vec[2].push_back(i); break;
            case 'g' : radix_vec[3].push_back(i); break;
            case 'n' : radix_vec[4].push_back(i); break;
            default : radix_vec[5].push_back(i); break;
        }
    }
    return radix_vec;
}

void print(vector<int> vec) {
    for(int i : vec) cout << dna_vec[i] << " ";
    cout << endl;
}

int main() {
    int k; cin >> k;
    string buf;
    vector<int> dnas;
    for(int i=0;cin >> buf; i++) {
        dna_vec.push_back(buf);
        dnas.push_back(i);
    }
    int type_cnt = 0, start_radix=0;
    while(type_cnt < 2 && start_radix <= MAX_RADIX) {
        type_cnt = 0;
        vector<vector<int>> radix_vec = get_radix_vec(dnas, start_radix);
        dnas.clear();
        int i=0;
        for(;radix_vec[i].size() < k-1;i++) k -= radix_vec[i].size();
        for(;dnas.size() < k+1; i++) {
            dnas.insert(dnas.end(), radix_vec[i].begin(), radix_vec[i].end());
            type_cnt++;
        }
        start_radix++;
    }
    int end_radix = MAX_RADIX;
    while(end_radix>=start_radix-1) {
        vector<vector<int>> radix_vec = get_radix_vec(dnas, end_radix);
        dnas.clear();
        for(vector<int> vec : radix_vec) {
            dnas.insert(dnas.end(), vec.begin(), vec.end());
        }
        end_radix--;
    }
    cout << dnas[k-2]+1 << "\n" << dnas[k-1]+1 << "\n" << dnas[k]+1 << endl;
}