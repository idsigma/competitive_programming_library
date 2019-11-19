#include <iostream>
using namespace std;
typedef long long ll;

ll inf = 998244353;
ll fact[3000010] = {0};
ll finv[3000010] = {0};
ll inv[3000010] = {0};

ll mult(ll n, ll m){
	if(m==1) return n%inf;
	else if(m%2==0){
		ll t = mult(n,m/2);
		return t*t%inf;
	}else{
		ll t = mult(n,m-1);
		return t*n%inf;
	}
}

void factorial(ll N){
	fact[0] = fact[1] = 1;
	finv[0] = finv[1] = 1;
	inv[1] = 1;
	for(ll i=2;i<=N;i++){
		fact[i] = i*fact[i-1]%inf;
		inv[i] = inf-inv[inf%i]*(inf/i)%inf;
		finv[i] = finv[i-1]*inv[i]%inf;
	}
}

ll comb(ll n,ll k){
	if(n<k) return 0;
	if(n<0 || k<0) return 0;
	else return (((fact[n]*finv[k])%inf)*finv[n-k])%inf;
}

ll hcomb(ll n,ll k){
	if(n==0 && k==0) return 1;
	return comb(n+k-1,k);
}

int main(){
	int x,y;
	factorial(107);
}