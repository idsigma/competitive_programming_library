#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int n,q;
class Potentialized_UnionFind{
private:
	vector<int> p,r;
	vector<ll> diff_weight;
public:
	Potentialized_UnionFind(int N){
		p = r = vector<int>(N+1,0);
		diff_weight = vector<ll>(N+1,0);
		for(int i=1;i<=N;i++){
			p[i] = i;
			diff_weight[i] = 0;
			r[i] = 0;
		}
	}
	int root(int a){
		if(p[a] == a) return a;
		else{
			int r = root(p[a]);
			diff_weight[a] += diff_weight[p[a]];
			return (p[a] = r);
		}
	}
	bool is_same_set(int a,int b){
		return root(a) == root(b);
	}
	ll weight(int a){
		root(a);
		return diff_weight[a];
	}
	ll diff(int a, int b){
		return weight(b) - weight(a);
	}
	void unite(int a, int b, int w){
		w += weight(a);
		w -= weight(b);
		a = root(a);
		b = root(b);
		if(a==b) return;
		if(r[a]<r[b]){
			int t = a;
			a = b;
			b = t;
			w = -w;
		}
		if(r[a] == r[b]) r[a]++;
		p[b] = a;
		diff_weight[b] = w;
	}
};

int main(){
	while(cin >> n >> q && n>0){
		Potentialized_UnionFind uf(n);
		for(int i=0;i<q;i++){
			char c;
			ll w,a,b;
			cin >> c;
			if(c=='!'){
				cin >> a >> b >> w;
				uf.unite(a,b,w);
			}else{
				cin >> a >> b;
				if(uf.is_same_set(a,b)) cout << uf.diff(a,b) << endl;
				else cout << "UNKNOWN" << endl;
			}
		}
	}
}