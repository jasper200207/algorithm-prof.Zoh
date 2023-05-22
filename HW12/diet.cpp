#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int min_protein, min_fat, min_carbs, min_vitamin;

class Base {
    public:
        int protein;
        int fat;
        int carbs;
        int vitamin;
        int price;
        int sum() const {
            return protein + fat + carbs + vitamin;
        }
};

class Food : public Base {
    public:
        int index;
};

class Diet : public Base {
    public:
        vector<int> foods;
        void add_food(Food food) {
            protein += food.protein;
            fat += food.fat;
            carbs += food.carbs;
            vitamin += food.vitamin;
            price += food.price;
            foods.push_back(food.index);
            sort(foods.begin(), foods.end());
        }
        bool check_healthy() {
            return protein >= min_protein && fat >= min_fat && carbs >= min_carbs && vitamin >= min_vitamin;
        }
        bool operator > (const Diet& d) const {
            if(price < d.price) return true;
            else if(price > d.price) return false;
            else {
                if(sum() > d.sum()) return true;
                else if(sum() < d.sum()) return false;
                else return foods < d.foods;
            }
        }
        void print() {
            for(int v : foods) {
                cout << v << " ";
            }
            cout << endl;
        }
};

int main() {
    int k;
    Diet solution;
    queue<Diet> diets;
    vector<Food> foods;
    cin >> k;
    cin >> min_protein >> min_fat >> min_carbs >> min_vitamin;
    for(int i=0;i<k;i++) {
        Food food;
        cin >> food.protein >> food.fat >> food.carbs >> food.vitamin >> food.price;
        food.index = i+1;
        foods.push_back(food);
    }
    sort(foods.begin(), foods.end(), [](const Food& a, const Food& b) {
        return a.sum() > b.sum()?true:(a.sum() < b.sum()?false:(a.price < b.price));
    });
    for(Food food : foods) {
        solution.add_food(food);
        if(solution.check_healthy()) break;
    }
    if(!solution.check_healthy()) {
        cout << 0 << endl;
        return 0;
    }
    diets.push(Diet());
    for(Food food : foods) {
        queue<Diet> remain_diets;
        if(diets.empty()) break;
        if(food.sum() == 0) continue;
        while(!diets.empty()) {
            Diet diet = diets.front();
            diets.pop();
            if(diet.price < solution.price && food.price > 0) {
                remain_diets.push(diet);
            }
            diet.add_food(food);
            if(diet.check_healthy()) {
                if(diet > solution) solution = diet;
            } else if(diet.price < solution.price) {
                remain_diets.push(diet);
            }
        }
        diets = remain_diets;
    }
    if(solution.check_healthy()) {
        solution.print();
    } else {
        cout << 0 << endl;
    }
}