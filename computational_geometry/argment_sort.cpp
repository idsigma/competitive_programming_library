#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

const long double PI=3.14159265358979;

struct point{
    int x,y,id;
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vec<point> P;
    vec<int> X(N),Y(N);
    for(int i=0;i<N;i++){
        cin >> X[i] >> Y[i];
        P.push_back({X[i],Y[i],i});
    }
    sort(P.begin(),P.end(),[](point& A,point& B){
        long double la = atan2(A.y,A.x);
        long double ra = atan2(B.y,B.x);
        if(abs(la - ra) > 1) return la < ra;
        else return A.x * B.y > A.y * B.x;
    });

    long double mi = 1e9;
    int a,b;
    for(int i=0;i<N;i++){
        if(i!=N-1){
            long double l = atan2(P[i].y,P[i].x);
            long double r = atan2(P[i+1].y,P[i+1].x);
            if(abs(r-l)<mi){
                mi = abs(r-l);
                a = P[i].id;
                b = P[i+1].id;
            }
        }else{
            long double l = atan2(P[i].y,P[i].x);
            long double r = atan2(P[0].y,P[0].x);
            long double c = 2*PI-l+r;
            if(abs(c)<mi){
                mi = abs(c);
                a = P[i].id;
                b = P[0].id;
            }
        }
    }
    cout << a+1 << " " << b+1 << endl;
}