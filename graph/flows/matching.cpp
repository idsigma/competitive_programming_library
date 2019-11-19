#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string.h>
using namespace std;

typedef pair<int,int> P;
int N;
vector<int> G[202];
bool used[202];
int match[202];

bool dfs(int v){
	used[v] = true;
	for(int i=0;i<G[v].size();i++){
		int u = G[v][i],w = match[u];
		if(w<0 || !used[w] && dfs(w)){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

int mat(){
	int ans = 0;
	memset(match,-1,sizeof(match));
	for(int v=1;v<=2*N;v++){
		if(match[v]<0){
			memset(used,0,sizeof(used));
			if(dfs(v)){
				ans++;
			}
		}
	}
	return ans;
}

int main(){
	cin >> N;
	vector<P> R(N+1),B(N+1);
	for(int i=1;i<=N;i++){
		int a,b;
		cin >> a >> b;
		R[i] = P(a,b);
	}
	for(int i=1;i<=N;i++){
		int a,b;
		cin >> a >> b;
		B[i] = P(a,b);
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(R[i].first < B[j].first && R[i].second < B[j].second){
				G[i].push_back(j+N);
				G[j+N].push_back(i);
			}
		}
	}
	cout << mat() << endl;
}
