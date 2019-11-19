#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> P;

class Persistent_UnionFind{
private:
	vector<vector<P>> p;
	vector<int> r,fin,s;
public:
	Persistent_UnionFind(int N){
		p = vector<vector<P>>(N+1);
		r = fin = s = vector<int>(N+1,0);
		for(int i=1;i<=N;++i){
			p[i].push_back({-1,-1});
			fin[i] = 1e9;
			s[i] = -1;
		}
	}
	int find(int x,int t){
		if(t>=fin[x]) return find(s[x],t);
		else return x;
	}
	bool is_same_set(int x,int y,int t){
		return find(x,t)==find(y,t);
	}
	int size(int x,int t){
		x = find(x,t);
		return -prev(lower_bound(p[x].begin(),p[x].end(),make_pair(t,0)))->second;
	}
	void unite(int x, int y,int t){
		x = find(x,t);
		y = find(y,t);
		if(x==y) return;
		if(s[x]>s[y]) swap(x,y);
		s[x] += s[y];
		p[x].push_back({t,s[x]});
		s[y] = x;
		fin[y] = t;
	}
};

int N,M,Q,a,b,x,y;

int main(){
	cin >> N >> M;
	Persistent_UnionFind uf(N);
	for(int i=0;i<M;i++){
		cin >> a >> b;
		uf.unite(a,b,i+1);
	}
	cin >> Q;
	for(int i=0;i<Q;i++){
		cin >> x >> y;
		int l = 0,r = M+1;
		while(l+1<r){
			int m = (l+r)/2;
			if(uf.is_same_set(x,y,m)) r = m;
			else l = m;
		}
		cout << (r!=M+1? r:-1) << endl;
	}
}