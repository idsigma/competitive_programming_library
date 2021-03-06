#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
typedef complex<double> xy;
double eps = 1e-9;
double dot_product(xy a,xy b) {return (conj(a)*b).real();}
double cross_product(xy a,xy b) {return (conj(a)*b).imag();}
double dist_lp(xy a1,xy a2,xy p){
    if(dot_product(a2-a1,p-a1)<eps) return abs(p-a1);
    if(dot_product(a1-a2,p-a2)<eps) return abs(p-a2);
    return abs(cross_product(a2-a1,p-a1))/abs(a2-a1);
}
xy projection(xy p,xy b) {return b*dot_product(p,b)/norm(b);}
xy projection2(xy p1,xy p2,xy p){
    p -= p1; p2 -= p1;
    xy proj = projection(p,p2);
    return p1+proj;
}

bool is_online(xy a1,xy a2,xy p){
    return abs(a1-p)+abs(a2-p)<=abs(a1-a2)+eps;    
}

bool is_intersected(xy a1, xy a2, xy b1, xy b2){
    if(is_online(a1,a2,b1) || is_online(a1,a2,b2)) return true;
    if(is_online(b1,b2,a1) || is_online(b1,b2,a2)) return true;
    return (cross_product(a2-a1,b1-a1)*cross_product(a2-a1,b2-a1)<-eps) && 
    (cross_product(b2-b1,a1-b1)*cross_product(b2-b1,a2-b1))<-eps;
}

double dist_ll(xy a1,xy a2,xy b1,xy b2){
    if(is_intersected(a1,a2,b1,b2)) return 0;
    return min({dist_lp(a1,a2,b1),dist_lp(a1,a2,b2),dist_lp(b1,b2,a1),dist_lp(b1,b2,a1)
    ,abs(a1-b1),abs(a1-b2),abs(a2-b1),abs(a2-b2)});   
}

double area_of_polygon(vector<xy>& v){
    int n = v.size();
    double res = 0;
    for(int i=0;i+2<n;i++){
        res += cross_product(v[i+1]-v[0],v[i+2]-v[0]);
    }
    return res/2;
}

bool is_convex(vector<xy>& v){
    int n = v.size();
    for(int i=0;i<n;i++){
        xy a = v[i%n],b = v[(i+1)%n],c = v[(i+2)%n];
        if(cross_product(b-a,c-a)<-eps) return false;
    }
    return true;
}

int N;
vector<xy> v;
int main(){
    cin >> N;
    double x,y;
    for(int i=0;i<N;i++){
        cin >> x >> y;
        v.push_back(xy(x,y));
    }
    cout << (is_convex(v)? 1:0) << endl;
}