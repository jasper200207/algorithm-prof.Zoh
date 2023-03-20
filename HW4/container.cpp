#include "container.h"

int main() {
    box_ready();
    int N=box_size();
    int first = box_comp(1,2)== 1 ? 1 : 2;
    int second = 3 - first;
    for(int i=3;i<=N;i++) {
        if(box_comp(i,second)==1) {
            if(box_comp(i,first)==1){
                second = first;
                first = i;
            }else second = i;
        }
    }
    box_report(second);
}