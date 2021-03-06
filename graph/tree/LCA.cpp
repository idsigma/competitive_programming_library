#include <iostream>
#include <vector>
using namespace std;

class LeastCommonAncestor{
private:
	vector<vector<int>> v;
	vector<vector<int>> parent;
	vector<int> depth;
	int h = 0;
	void dfs(int n,int m,int d){
		parent[0][n] = m;
		depth[n] = d;
		for(auto x:v[n]){
			if(x!=m) dfs(x,n,d+1);
		}
	}
public:
	LeastCommonAncestor(int N,int root,vector<vector<int>>& tree){
		while((1<<h)<=N) h++;
		v = tree;
		parent = vector<vector<int>>(h,vector<int>(N,0));
		depth = vector<int>(N,0);
		dfs(root,-1,0);
		for(int j=0;j+1<h;j++){
			for(int i=0;i<N;i++){
				if(parent[j][i]<0) parent[j+1][i] = -1;
				else parent[j+1][i] = parent[j][parent[j][i]];
			}
		}
	}
	int lca(int n,int m){
		if(depth[n]>depth[m]) swap(n,m);
		for(int j=0;j<h;j++){
			if((depth[m]-depth[n]) >> j&1) m = parent[j][m];
		}
		if(n==m) return n;
		for(int j=h-1;j>=0;j--){
			if(parent[j][n]!=parent[j][m]){
				n = parent[j][n];
				m = parent[j][m];
			}
		}
		return parent[0][n];
	}
	int dep(int n){return depth[n];}
};

int N,Q,x,y,a,b;

int main(){
	cin >> N;
	vector<vector<int>> tree(N+1);
	for(int i=0;i<N;i++){
		int k;
		cin >> k;
		for(int j=0;j<k;j++){
			int c;
			cin >> c;
			tree[i].push_back(c);
			tree[c].push_back(i);
		}
	}
	LeastCommonAncestor lca(N,0,tree);
	cin >> Q;
	for(int i=0;i<Q;i++){
		cin >> a >> b;
		int p = lca.lca(a,b);
		cout << p << endl;
	}
}