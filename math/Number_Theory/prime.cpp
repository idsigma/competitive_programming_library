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

struct Prime{
	vector<int> v;
	vec<int> prime;
	vec<int> mobius;
	vvec<int> prime_list;
	Prime(int N):v(N),prime_list(N+1),mobius(N){
		for(int i=0;i<=N;i++){
			v[i] = 1;
		}
		for(int i=2;i<=N;i++){
			if(v[i]){
				prime_list[i].push_back(i);
				for(int j=0;i*(j+2)<=N;j++){
					v[i*(j+2)] = 0;
					prime_list[i*(j+2)].push_back(i);
				}
			}
		}
		v[1] = false;
		for(int i=2;i<=N;i++){
			if(v[i]){
				prime.push_back(i);
			}
		}    
	}
	void calc_mobius(int N){
		for(int i=1;i<=N;i++){
			mobius[i] = (prime_list[i].size()%2? -1:1);
			for(auto& p:prime_list[i]) if((i/p)%p==0) mobius[i] = 0;
		}
	}
};

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int N,K;
	cin >> N >> K;
	vec<mint> powN(K+1);
	for(int i=1;i<=K;i++) powN[i] = ((mint) i).pow(N);
	vvec<pair<int,mint>> list(K+1);
	Prime P(K);
	P.calc_mobius(K);
	vec<mint> ans(K+1);
	vec<mint> F(K+1);
	vec<mint> delta(K+1);
	for(int i=1;i<=K;i++){
		for(int j=i;j<=K;j+=i){
			delta[j] -= powN[(j-1)/i]*P.mobius[i];
			delta[j] += powN[j/i]*P.mobius[i];
		}
	}
	for(int i=1;i<=K;i++){
		ans[i] = ans[i-1]+delta[i];
	}
	ll res = 0;
	for(int i=1;i<=K;i++) (res += ans[i].x^i)%=mod;
	cout << res << "\n";
}
