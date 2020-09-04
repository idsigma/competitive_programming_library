#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T,class U> using P = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;
using xy = complex<double>;
double eps = 1e-9;
double dot_product(xy a,xy b) {return (conj(a)*b).real();}
double cross_product(xy a,xy b) {return (conj(a)*b).imag();}
double dist_lp(xy a1,xy a2,xy p){return abs(cross_product(a2-a1,p-a1));}
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
    if(is_intersected(a1,a2,b1,b2)) return 0.0;
    return min({dist_lp(a1,a2,b1),dist_lp(a1,a2,b2),dist_lp(b1,b2,a1),dist_lp(b1,b2,a1)
    ,abs(a1-b1),abs(a1-b2),abs(a2-b1),abs(a2-b2)});   
}

int Q;
double X[5],Y[5];
int main(){
    cin >> Q;
    for(int i=0;i<Q;i++){
        for(int j=1;j<=4;j++){
            cin >> X[j] >> Y[j];
        }
        cout << dist_ll(xy(X[1],Y[1]),xy(X[2],Y[2]),xy(X[3],Y[3]),xy(X[4],Y[4])) << endl;       
    }
}