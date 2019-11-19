#include <iostream>
#include <vector>
#include <map>
using namespace std;

class UnionFind{
private:
    vector<int> p,s;
	int cnt;
public:
	UnionFind(){}
	UnionFind(int N){
		cnt = N;
		p = s = vector<int>(N+1,0);
		for(int i=0;i<=N;i++){
			p[i] = i; s[i] = 1;
		}
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
        uf1.unite(p,q);
    }
    for(int i=0;i<L;i++){
        cin >> r >> s;
        uf2.unite(r,s);
    }
    map<pair<int,int>,int> m;
    for(int i=1;i<=N;i++){
        m[{uf1.find(i),uf2.find(i)}]++;
    }
    for(int i=1;i<=N;i++){
        cout << m[{uf1.find(i),uf2.find(i)}] << (i!=N? " ":"\n");
    }
}