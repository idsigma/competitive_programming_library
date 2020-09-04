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

double convex_diameter(vector<xy> v){
    int n = v.size();
    int l = 0,r = 0;
    for(int i=1;i<n;i++){
        if(v[i].imag()>v[l].imag()) l = i;
        if(v[i].imag()<v[r].imag()) r = i;
    }
    double res = abs(v[l]-v[r]);
    int i = l,mai = l,j = r,maj = r;
    do{
        if(cross_product(v[(i+1)%n]-v[i],v[(j+1)%n]-v[j])>=0) j = (j+1)%n;
        else i = (i+1)%n;
        if(abs(v[i]-v[j])>res){
            res = abs(v[i]-v[j]);
            mai = i; maj = j;
        }
    }while(i!=l || j!=r);
    return res;
}

int N;
vector<xy> v,u;

int main(){
    cin >> N;
    double x,y;
    for(int i=0;i<N;i++){
        cin >> x >> y;
        v.push_back(xy(x,y));
    }
    cout << fixed;
    cout << setprecision(10) << convex_diameter(v) << endl;
}