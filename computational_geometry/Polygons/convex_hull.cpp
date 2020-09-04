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
bool comp(xy a,xy b){
    return (a.real()!=b.real()? a.real()<b.real() : a.imag()<b.imag());
}

vector<xy> convex_hull(vector<xy> v){
    int n = v.size();
    vector<xy> res;
    sort(v.begin(),v.end(),comp);
    for(int i=0;i<n;i++){
        if(i<2){
            res.push_back(v[i]);
            continue;
        }
        while(true){
            int s = res.size();
            if(s<2){
                res.push_back(v[i]);
                break;
            }
            double c = cross_product(res[s-1]-res[s-2],v[i]-res[s-2]);
            if(c<-eps){
                res.pop_back();
            }else{
                res.push_back(v[i]);
                break;
            }
        }
    }
    reverse(v.begin(),v.end());
    for(int i=0;i<n;i++){
        while(true){
            int s = res.size();
            if(v[i]==res.back()) break;
            if(s<2){
                res.push_back(v[i]);
                break;
            }
            double c = cross_product(res[s-1]-res[s-2],v[i]-res[s-2]);
            if(c<-eps){
                res.pop_back();
            }else{
                res.push_back(v[i]);
                break;
            }
        }
    }
    res.pop_back();
    return res;
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
    vector<xy> ans = convex_hull(v);
    int n = ans.size();
    int id = 0;
    for(int i=1;i<n-1;i++){
        if(ans[i-1].imag()>ans[i].imag() && ans[i].imag()-eps<=ans[i+1].imag()){
            id = i;
            break;
        }
    }
    cout << n << endl;
    for(int i=0;i<n;i++){
        cout << ans[(i+id)%n].real() << " " << ans[(i+id)%n].imag() << endl;
    }
}