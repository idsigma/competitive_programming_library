#include <iostream>
#include <vector>
using namespace std;

class LCA{
private:
	vector<vector<int>> v;
	vector<vector<int>> parent;
	vector<int> depth;
	void dfs(int n,int m,int d){
		parent[0][n] = m;
		depth[n] = d;
		for(auto x:v[n]){
			if(x!=m) dfs(x,n,d+1);
		}
	}
public:
	LCA(int N,int root,vector<vector<int>>& tree){
		v = tree;
		parent = vector<vector<int>>(20,vector<int>(N,0));
		depth = vector<int>(N,0);
		dfs(root,-1,0);
		for(int j=0;j+1<20;j++){
			for(int i=0;i<N;i++){
				if(parent[j][i]<0) parent[j+1][i] = -1;
				else parent[j+1][i] = parent[j][parent[j][i]];
			}
		}
	}
	int lca(int n,int m){
		if(depth[n]>depth[m]) swap(n,m);
		for(int j=0;j<20;j++){
			if((depth[m]-depth[n]) >> j&1) m = parent[j][m];
		}
		if(n==m) return n;
		for(int j=19;j>=0;j--){
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
	LCA lca(N,0,tree);
	cin >> Q;
	for(int i=0;i<Q;i++){
		cin >> a >> b;
		int p = lca.lca(a,b);
		cout << p << endl;
	}
}