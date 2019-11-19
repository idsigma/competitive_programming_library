#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<int>> v(100000);
int visited[100010] = {0};
int depth[100010] = {0};
int mini[100010] = {0};
int V,E,s,t;
int inf = 1e9;
vector<int> ans;

int dfs(int n,int m){
	visited[n] = 1;
	for(int i=0;i<v[n].size();i++){
		if(visited[v[n][i]]==0){
			depth[v[n][i]] = depth[n] + 1;
			dfs(v[n][i],n);
		}
	}
	for(int i=0;i<v[n].size();i++){
		if(v[n][i]!=m) mini[n] = min(mini[n],min(depth[n],depth[v[n][i]]));
	}
}

int dfs2(int n){
	visited[n] = 1;
	for(int i=0;i<v[n].size();i++){
		if(visited[v[n][i]]==0){
			dfs2(v[n][i]);
			mini[n] = min(mini[n],mini[v[n][i]]);
			if(n!=0 && depth[n]<=mini[v[n][i]]) ans.push_back(n);
		}
	}
}

int main(){
	cin >> V >> E;
	for(int i=0;i<E;i++){
		cin >> s >> t;
		v[s].push_back(t);
		v[t].push_back(s);
	}
	for(int i=0;i<V;i++) mini[i] = inf;
	dfs(0,-1);
	int count = 0;
	for(int i=0;i<V;i++){
		visited[i] = 0;
		if(depth[i]==1) count++;
	}
	if(count>=2) ans.push_back(0);
	dfs2(0);
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++){
		if(i==0 || ans[i]!=ans[i-1]) cout << ans[i] << endl;
	}
}