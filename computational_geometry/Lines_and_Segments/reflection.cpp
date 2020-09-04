#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
using namespace std;
typedef complex<double> xy;

double dot_product(xy a,xy b) {return (conj(a)*b).real();}
double cross_product(xy a,xy b) {return (conj(a)*b).imag();}
xy projection(xy p,xy b) {return b*dot_product(p,b)/norm(b);}
xy projection2(xy p1,xy p2,xy p){
    p -= p1; p2 -= p1;
    xy proj = projection(p,p2);
    return p1+proj;
}

xy reflection(xy p1,xy p2, xy p){
    xy pj = projection2(p1,p2,p);
    xy res = 2.0*pj-p;
    return res;
}

int N,Q;
double x_1,y_1,x_2,y_2;
int main(){
    cin >> x_1 >> y_1 >> x_2 >> y_2;
    cin >> Q;
    for(int i=0;i<Q;i++){
        double x,y;
        cin >> x >> y;
        xy ans = reflection(xy(x_1,y_1),xy(x_2,y_2),xy(x,y));
        cout << fixed;
        cout << setprecision(10) << ans.real() << " " << ans.imag() << endl;
    }
}