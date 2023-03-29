#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#define MAXLEN 34645
#define onLine(P,A,B) ((B-A).length() >= (P-A).length()+(P-B).length())
#define normalize(A,B) (B - A)*(1/(B-A).length());
using namespace std;

class Vector3 {
    private:
        double x,y,z;
    public:
        Vector3(double x=0, double y=0, double z=0):x(x),y(y),z(z){};
        double dot(Vector3 v) {
            return x * v.x + y * v.y + z * v.z;
        }
        Vector3 cross(Vector3 v) {
            return Vector3(y * v.z - z * v.y,
                           z * v.x - x * v.z,
                           x * v.y - y * v.x);
        }
        double length() {
            return sqrt(x * x + y * y + z * z);
        }
        Vector3 operator+(Vector3 v) {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }
        Vector3 operator-(Vector3 v) {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }
        Vector3 operator*(double n) {
            return Vector3(x*n, y*n, z*n);
        }
 };

Vector3 getContactPoint(Vector3 normal, Vector3 P, Vector3 A, Vector3 B) {
    Vector3 nAB = normalize(A,B);
    return A + (nAB * (normal.dot(P-A)/normal.dot(nAB)));
}

double getHbyPandL(Vector3 P, Vector3 A, Vector3 B) {
    Vector3 AB = A-B, BP = P-B;
    double cos = AB.dot(BP) /(AB.length()*BP.length());
    double len = BP.length() * cos;
    Vector3 nAB = normalize(A,B);
    Vector3 H = B - nAB * len;
    if(onLine(H,A,B)) return (P-H).length();
    else return MAXLEN;
}

double getShortestPath(Vector3 A, Vector3 B, Vector3 C, Vector3 D) {
    vector<double> results = {
                                getHbyPandL(A,C,D),
                                getHbyPandL(B,C,D),
                                getHbyPandL(C,A,B),
                                getHbyPandL(D,A,B),
                                (A-C).length(),
                                (A-D).length(),
                                (B-C).length(),
                                (B-D).length()
                            };
    Vector3 AB = B - A, CD = D - C, AC = C - A;
    Vector3 ABcrossCD = AB.cross(CD);
    Vector3 p1 = getContactPoint(ABcrossCD.cross(CD),C,A,B), p2 = getContactPoint(ABcrossCD.cross(AB),A,C,D);
    if(onLine(p1,A,B) && onLine(p2,C,D)) results.push_back((p1-p2).length());
    return *min_element(results.begin(),results.end());
}

int main() {
    double x,y,z;
    Vector3 V[4];
    for(int i=0;i<4;i++) {
        cin >> x >> y >> z;
        V[i] = Vector3(x,y,z);
    }
    cout << int(ceil(getShortestPath(V[0],V[1],V[2],V[3])));
}