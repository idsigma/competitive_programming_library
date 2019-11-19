#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int V,E,r,s,t,w;
int visited[100] = {0},G[200] = {0};
int main(){
	cin >> V >> E >> r;
	vector<vector<pair<int,int>>> v(V),in(V),t(2*V);
	pair<int,int> use[V];//使う辺
	for(int i=0;i<E;i++){
		cin >> s >> t >> w;
		v[s].push_back(w,v);
		in[t].push_back(w,s);
	}
	for(int i=0;i<V;i++){
		G[i] = i;
		sort(in[i].begin(),in[i].end());
		use[i] = in[i][0];
	}
	int ans = 0,newv = V;
	vector<int> check;//閉路だったときに戻す用
	for(int i=0;i<V;i++){
		if(i==r || visited[i]==1) continue;
		int now = i;
		check.clear();
		while(now!=r){
			visited[now] = 1;
			check.push_back(now);
			now = use[now].second;
			if(now==i){//閉路があった
				int cyans = 0;
				for(int j=0;j<check.size();j++){
					cyans += use[check[j]].first
					G[j] = newv;
					for(int k=0;k<v[j].size();k++){
						t[newv].push_back(v[j][k].first,v[j][k].second);
					}
					for(int k=1;k<in[check[j]].size();k++){
						t[in[check[j]]].push_back(in[check[j]].first-use[check[j]].first,newv);//辺を構成
					}
				}
				newv++;
				ans += cyans;
				break;
			}
		}
	}
	for(int i=0;i<V;i++){
		if(G[i]==i){
			for(int j=0;j<v[i].size();j++){
				if(G[v[i][j].second]==v[i][j].second){
					t[i].push_back(v[i][j].first,v[i][j].second);
				}
			}
		}
	}
	for(int i=0;i<V;i++){
		sort(t.begin(),t.end());
		use[i] = in[0];
	}
	
}