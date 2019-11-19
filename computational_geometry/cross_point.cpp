#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
using namespace std;
typedef complex<double> xy;
double eps = 1e-9;
double dot_product(xy a,xy b) {return (conj(a)*b).real();}
double cross_product(xy a,xy b) {return (conj(a)*b).imag();}
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

xy cross_point(xy a1, xy a2, xy b1, xy b2){
    xy b = b2-b1;
    double d1 = abs(cross_product(b,a1-b1));
    double d2 = abs(cross_product(b,a2-b1));
    double t = d1/(d1+d2);
    return a1+(a2-a1)*t;
}

int Q;
double X[5],Y[5];
int main(){
    cin >> Q;
    for(int i=0;i<Q;i++){
        for(int j=1;j<=4;j++){
            cin >> X[j] >> Y[j];
        }
        xy ans = cross_point(xy(X[1],Y[1]),xy(X[2],Y[2]),xy(X[3],Y[3]),xy(X[4],Y[4]));
        cout << fixed;
        cout << setprecision(10) << ans.real() << " " << ans.imag() << endl;     
    }
}