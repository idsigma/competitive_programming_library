#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int inf = 1e9;
class network_flow{
private:
	struct edge{int to, cap, rev;};
	vector<vector<edge>> G;
	vector<bool> used;
public:
	network_flow(int N){
		G = vector<vector<edge>>(N+1);
		used = vector<bool>(N+1,0); 
	}
	void add_edge(int from, int to, int cap){
		G[from].push_back((edge){to,cap,(int) G[to].size()});
		G[to].push_back((edge){from,0,(int) G[from].size()-1});
	}
	int dfs(int v,int t,int f){
		if(v==t) return f;
		used[v] = true;
		for(int i=0;i<G[v].size();i++){
			edge &e = G[v][i];
			if(!used[e.to] && e.cap>0){
				int d = dfs(e.to,t,min(f,e.cap));
				if(d>0){
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}
	int max_flow(int s,int t){
		int flow = 0;
		for(;;){
			for(int i=0;i<(int)used.size();i++) used[i] = 0;
			int f = dfs(s,t,inf);
			if(f==0) return flow;
			flow += f;
		}
	}
};

int main(){
	int inf = 1e8;
	int V,E;
	cin >> V >> E;
	network_flow flow(V);
	for(int i=0;i<E;i++){
		int t,c,r;
		cin >> t >> r >> c;
		flow.add_edge(t,r,c);
	}
	cout << flow.max_flow(0,V-1) << endl;
}