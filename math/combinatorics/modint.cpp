#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

constexpr ll mod = 998244353;
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
    bool operator==(const mint a)const{
        return x==a.x;
    }
};

class combination{
private:
    vector<mint> fact,inv,finv;
public:
    combination(int N){
        fact = inv = finv = vector<mint>(N+1);
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

int main(){
    ll N,M;
    cin >> N >> M;
    combination c(N+3*M);
    mint ans = c.hcomb(N,3*M);
    for(int k=M+1;k<=min(N,3*M);k++){
        if((3*M-k)%2==0){
            ans -= c.comb(N,k)*c.hcomb(N,(3*M-k)/2);
        }
    }
    ans -= c.hcomb(N,M-1)*N;
    cout << ans << endl;
}