#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T,class U> using Pa = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

class UnionFind{
private:
	vec<int> p,s;
	int cnt;
public:
	UnionFind(){}
	UnionFind(int N):cnt(N),s(N,1),p(N){
		iota(p.begin(),p.end(),0);
	}
	int find(int x){
		if(p[x]==x) return x;
		else return p[x] = find(p[x]);
	}
	void unite(int x,int y){
		x = find(x); y = find(y);
		if(x==y) return;
		if(s[x]>s[y]) swap(x,y);
		p[x] = y;
		s[y] += s[x];
		cnt--;
	}
	bool is_same_set(int x,int y) {return find(x)==find(y);}
	int size(int x) {return s[find(x)];}
	int compnents_number(){return cnt;}
};

int N,K,L,p,q,r,s;
int main(){
    cin >> N >> K >> L;
    UnionFind uf1(N),uf2(N);
    for(int i=0;i<K;i++){
        cin >> p >> q;
		p--; q--;
        uf1.unite(p,q);
    }
    for(int i=0;i<L;i++){
        cin >> r >> s;
		r--; s--;
        uf2.unite(r,s);
    }
    map<pair<int,int>,int> m;
    for(int i=0;i<N;i++){
        m[{uf1.find(i),uf2.find(i)}]++;
    }
    for(int i=0;i<N;i++){
        cout << m[{uf1.find(i),uf2.find(i)}] << (i!=N? " ":"\n");
    }
}