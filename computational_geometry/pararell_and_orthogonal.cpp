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

int N,Q;
int X[5],Y[5],dx[2],dy[2];
int main(){
    cin >> Q;
    for(int i=0;i<Q;i++){
        for(int j=1;j<=4;j++){
            cin >> X[j] >> Y[j];
        }
        dx[0] = X[2]-X[1];
        dx[1] = X[4]-X[3];
        dy[0] = Y[2]-Y[1];
        dy[1] = Y[4]-Y[3];
        if(dx[0]*dy[1]==dx[1]*dy[0]) cout << 2 << endl;
        else if(dx[0]*dx[1]+dy[0]*dy[1]==0) cout << 1 << endl;
        else cout << 0 << endl;
    }
}