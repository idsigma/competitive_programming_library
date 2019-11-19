#include <iostream>
#include <vector>
using namespace std;
int V,E,s,t;
vector<vector<int>> v(10001);
vector<int> u;
int visited[10001] = {0};

void dfs(int n){
	visited[n] = 1;
	for(int i=0;i<v[n].size();i++){
		if(visited[v[n][i]]==0) dfs(v[n][i]);
	}
	u.push_back(n);
}

int main(){
	cin >> V >> E;
	for(int i=0;i<E;i++){
		cin >> s >> t;
		v[s].push_back(t);
	}
	for(int i=0;i<V;i++){
		if(visited[i]==0) dfs(i);
	}
	for(int i=V-1;i>=0;i--) cout << u[i] << endl;
}