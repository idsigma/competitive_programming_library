#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class BIT{
private:
    vector<ll> bit;
    int n;
public:
    BIT(){};
    BIT(int N){
        init(N);
    }
    void init(int N){
        n = N;
        bit.clear();
        bit.resize(N+1,0);
    }
    ll sum(int i){
        ll s = 0;
        while(i>0){
            s += bit[i];
            i -= i&-i;
        }
        return s;
    }
    ll sum_range(int l,int r){
        if(l>r) return 0;
        return (sum(r)-sum(l-1));
    }
    void add(int i,ll x){
        while(i<=n){
            bit[i] += x;
            i += i&-i;
        }
    }
    ll sum0(int i){
        return sum(i);
    }
    void add0(int i,ll x){
        add(i,x);
    }
};

int n,q,com,x,y;

int main(){
	cin >> n >> q;
	for(int i=0;i<q;i++){
		cin >> com >> x >> y;
		if(com==0){
			add(x,y);
		}else{
			cout << sum(y) - sum(x-1) << endl;
		}
	}
}