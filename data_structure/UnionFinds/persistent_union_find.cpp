#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int,int> p[100010];
int r[100010] = {0},fin[100010] = {0},idx;

void init(int N){
	idx = 0;
	for(int i=0;i<=N;++i){
		p[i][0] = i;
		r[i] = 1;
		fin[i] = 0;
	}
}

int find(int x,int t){
	if(t>=fin[x] && p[x][fin[x]]!=x) return find(p[x][fin[x]],t);
	else return x;
}

bool is_same_set(int x,int y,int t){
	return find(x,t)==find(y,t);
}

void unite(int x, int y){
	x = find(x,idx);
	y = find(y,idx);
	idx++;
	if(x==y) return;
	if(r[x]<r[y]){
		p[x][idx] = y;
		fin[x] = idx;
	}else{
		p[y][idx] = x;
		fin[y] = idx;
		if(r[x] == r[y]) r[x]++;
	}
}

int N,M,Q,a,b,x,y;

int main(){
	cin >> N >> M;
	init(N);
	for(int i=0;i<M;i++){
		cin >> a >> b;
		unite(a,b);
	}
	cin >> Q;
	for(int i=0;i<Q;i++){
		cin >> x >> y;
		int l = 0,r = M+1;
		while(l+1<r){
			int m = (l+r)/2;
			if(is_same_set(x,y,m)) r = m;
			else l = m;
		}
		cout << (r!=M+1? r:-1) << endl;
	}
}