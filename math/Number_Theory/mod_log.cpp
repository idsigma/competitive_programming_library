#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
typedef unsigned long long ll;

ll mod_log(ll a, ll b, ll p) {
    ll ok = p, ng = -1;
    while(ok - ng > 1) {
        auto mid = (ok + ng) / 2;
        if(mid * mid >= p) ok = mid;
        else ng = mid;
    }
 
    unordered_map< ll, ll > baby;
    baby.reserve(ok);
    ll factor = 1;
    for(ll i = 0, e = b; i < ok; i++) {
        baby[e] = i;
        (factor *= a) %= p;
        (e *= a) %= p;
    }
    for(ll i = 1, e = factor; i <= ok; i++) {
        auto it = baby.find(e);
        if(it != end(baby)) return i * ok - it->second;
        (e *= factor) %= p;
    }
    return -1;
}

ll pow(ll x,ll n,ll P){
    if(n==1) return x;
    if(n%2){
        ll p = pow(x,n-1,P);
        return x*p%P;
    }else{
        ll p = pow(x,n/2,P);
        return p*p%P;    
    }
}

int main(){
    ll X,P,A,B;
    cin >> X >> P >> A >> B;
    
}