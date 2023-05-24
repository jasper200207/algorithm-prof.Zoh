#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;

class Place{
    public:
        int x,y,index;
        Place(int x, int y, int index):x(x),y(y),index(index){}
        int distance(Place p) {
            return abs(x - p.x) + abs(y - p.y);
        }
        bool operator<(const Place& p) const {
            return index < p.index;
        }
};

class Path : public vector<Place> {
    public:
        int travel = 0;
        vector<int> foods ;
        Path() {
            push_back(Place(500,500,0));
        }
        bool is_can_move(const Place& p) const {
            if(p.index > 0 && foods.size() >= 2) {
                return false;
            }else if(p.index < 0 && find(foods.begin(), foods.end(), -p.index) == foods.end()) {
                return false;
            }
            return true;
        }
        void move_to(Place p) {
            travel += back().distance(p);
            if(p.index > 0) {
                foods.push_back(p.index);
            }
            else {
                foods.erase(
                    remove_if(
                        foods.begin(), foods.end(), 
                        [p](int i) {
                            return i == -p.index;
                        }
                    )
                );
            }
            push_back(p);
        }
        bool operator<(const Path& p) const {
            if(travel != p.travel)
                return travel < p.travel;
            return p > *this;
        }
        void print() {
            for(Place p : *this) {
                if(p.index != 0) cout << p.index << " ";
            }
            cout << "\n" << travel << endl;
        }
};

Path dfs(Path path, vector<Place> placeList, Path best) {
    if(placeList.empty()) {
        return best < path ? best : path;
    }
    else if(best < path) return best;
    else {
        for(Place p : placeList) {
            if(!path.is_can_move(p)) continue;
            Path new_path = path;
            new_path.move_to(p);
            vector<Place> new_placeList = placeList;
            new_placeList.erase(
                remove_if(
                    new_placeList.begin(), new_placeList.end(), 
                    [p](Place place) {
                        return place.index == p.index;
                    }
                )
            );
            best = dfs(new_path, new_placeList, best);
        }
        return best;
    }
}

int main() {
    int n; cin >> n;
    vector<Place> placeList;
    for(int i = 0; i < n; i++) {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        placeList.push_back(Place(x1,y1,i+1));
        placeList.push_back(Place(x2,y2,-(i+1)));
    }
    Path best_path;
    for(Place p : placeList) {
        best_path.move_to(p);
    }
    best_path = dfs(Path(), placeList, best_path);
    best_path.print();
}