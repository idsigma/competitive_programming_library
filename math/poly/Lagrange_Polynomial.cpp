#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T, class U> using Pa = pair<T, U>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;

constexpr ll mod = 1e9+7;
struct mint {
    ll x;
    mint(ll x=0):x((x%mod+mod)%mod){}
    
    friend ostream &operator<<(ostream& os,const mint& a){
        return os << a.x;
    }

    friend istream &operator>>(istream& is,mint& a){
        ll t;
        is >> t;
        a = mint(t);
        return (is);
    }

    mint& operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) {
        (x *= a.x) %= mod;
        return *this;
    }
    mint operator+(const mint a) const {
        mint res(*this);
        return res+=a;
    }
    mint operator-(const mint a) const {
        mint res(*this);
        return res-=a;
    }
    mint operator*(const mint a) const {
        mint res(*this);
        return res*=a;
    }
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }
    // for prime mod
    mint inv() const {
        return pow(mod-2);
    }
    mint& operator/=(const mint a) {
        return (*this) *= a.inv();
    }
    mint operator/(const mint a) const {
        mint res(*this);
        return res/=a;
    }
};

class combination{
private:
    vec<mint> fact,inv,finv;
public:
    combination(int N){
        fact = inv = finv = vec<mint>(N+1);
        fact[0] = fact[1] = 1;
        inv[0] = inv[1] = 1;
        finv[0] = finv[1] = 1;
        for(ll i=2;i<=N;i++){
            fact[i] = fact[i-1]*i;
            inv[i] = (mint) mod - inv[mod%i]*(mod/i);
            finv[i] = finv[i-1]*inv[i];
        }
    }
    mint f(int i){
        return fact[i];
    }

    mint fiv(int i){
        return finv[i];
    }
    
    mint comb(int n,int k){
        if(n<k) return 0;
        if(n<0 || k<0) return 0;
        return fact[n]*finv[k]*finv[n-k];
    }
    mint hcomb(int n,int k){
        if(n==0 && k==0) return 1;
        return comb(n+k-1,k);
    }
};

//N次多項式において、f(0),...,f(N)がわかっているときに使える
mint lagrange_polynomial(const vec<mint>& Y,ll t){
    ll N = Y.size()-1;
    combination comb(N);
    if(t<=N) return Y[t];
    mint res = 0;
    vec<mint> dp(N+1,1),pd(N+1,1);
    for(int i=0;i<N;i++) dp[i+1] = dp[i]*(t-i);
    for(int i=N;i>0;i--) pd[i-1] = pd[i]*(t-i);
    for(int i=0;i<=N;i++){
        mint tmp = Y[i]*dp[i]*pd[i]*comb.fiv(i)*comb.fiv(N-i);
        if((N-i)&1) res -= tmp;
        else res += tmp;
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll N,T;
    cin >> N;
    vec<mint> A(N+1);
    for(int i=0;i<=N;i++) cin >> A[i];
    cin >> T;
    cout << lagrange_polynomial(A,T) << "\n";
}
