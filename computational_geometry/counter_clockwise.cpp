#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
using namespace std;
typedef complex<double> xy;

double dot_product(xy a,xy b) {return (conj(a)*b).real();}
double cross_product(xy a,xy b) {return (conj(a)*b).imag();}
void counter_clockwise(xy p0,xy p1,xy p2){
    double d = cross_product(p1-p0,p2-p0);
    if(d<0) cout << "CLOCKWISE" << endl;
    else if(d>0) cout << "COUNTER_CLOCKWISE" << endl;
    else{
        if(dot_product(p1-p0,p2-p0)<0) cout << "ONLINE_BACK" << endl;
        else if(norm(p1-p0)<norm(p2-p0)) cout << "ONLINE_FRONT" << endl;
        else cout << "ON_SEGMENT" << endl;
    }
}

int N,Q;
double x_1,y_1,x_2,y_2;
int main(){
    cin >> x_1 >> y_1 >> x_2 >> y_2;
    cin >> Q;
    for(int i=0;i<Q;i++){
        double x,y;
        cin >> x >> y;
        cout << fixed;
        counter_clockwise(xy(x_1,y_1),xy(x_2,y_2),xy(x,y));
    }
}