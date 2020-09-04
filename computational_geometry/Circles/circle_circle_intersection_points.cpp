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
bool comp(xy a,xy b){
    return (a.real()!=b.real()? a.real()<b.real() : a.imag()<b.imag());
}

struct circle{
    xy c;
    double r;
};

vector<xy> cc_intertsection_points(circle o1,circle o2){
    double d1 = abs(o2.c-o1.c);
    double x = (d1*d1+o1.r*o1.r-o2.r*o2.r)/(2*d1);
    xy v1 = (o2.c-o1.c)/d1,v2 = v1*(xy(0,1));
    double d2 = max(sqrt(o1.r*o1.r-x*x),0.0);
    return vector<xy> {o1.c+v1*x+v2*d2,o1.c+v1*x-v2*d2};
}

int main(){
    double c1x,c1y,c1r,c2x,c2y,c2r;
    cin >> c1x >> c1y >> c1r;
    cin >> c2x >> c2y >> c2r;
    vector<xy> ans = cc_intertsection_points({xy(c1x,c1y),c1r},{xy(c2x,c2y),c2r});
    if(!comp(ans[0],ans[1])) swap(ans[0],ans[1]);
    cout << fixed;
    for(auto x:ans) cout << setprecision(10) << x.real() << " " << x.imag() << endl;
}