#include<iostream>
#include<string>
#include <unistd.h>
using namespace std;

class Checker {
    private:
        string str;
        string name;
        int left_shift = 0;
        int right_shift = 0;
        int idx = 0;
        bool last_result = true;
    public:
        Checker(string str, string name):str(str),name(name){};
        bool end() {
            return idx+left_shift >= str.length()-idx-1-right_shift || !last_result;
        }
        bool check() {
            if(!end()) {
                last_result = str[idx + left_shift] == str[str.length()-idx-1-right_shift];
                idx++;
            }
            return last_result;
        }
        void shift_left(int shift) {left_shift=shift;};
        void shift_right(int shift) {right_shift=shift;};
};

int main() {
    int N;
    cin >> N;
    for(int i=0;i<N;i++) {
        string str; cin >> str;
        Checker palin = {str,"palin"}, leftPass = {str,"leftPass"}, rightPass = {str,"rightPass"};
        while(!palin.end() || !leftPass.end() || !rightPass.end()) {
            if(!palin.check()) {
                leftPass.shift_left(1);
                rightPass.shift_right(1);
            }
            leftPass.check(); rightPass.check();
        }
        cout << (palin.check() ? 1 : leftPass.check()||rightPass.check() ? 2 : 3) << "\n";
    }
}