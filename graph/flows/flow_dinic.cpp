#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T, class U> using Pa = pair<T, U>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;

constexpr ll inf = 1e18;

class network_flow{
private:
	int N;
	struct edge{int to; ll cap; int rev; bool is_rev;};
	vvec<edge> G;
	vec<int> level,iter;
	void bfs(int s){
		for(int i=0;i<=N;i++) level[i] = -1;
		queue<int> Q;
		level[s] = 0;
		Q.push(s);
		while(!Q.empty()){
			int v = Q.front(); Q.pop();
			for(auto& e:G[v]){
				if(e.cap > 0 && level[e.to]<0){
					level[e.to] = level[v]+1;
					Q.push(e.to);
				}
			}
		}
	}
	ll dfs(int v,int t,ll f){
		if(v==t) return f;
		for(int &i=iter[v];i<G[v].size();i++){
			edge &e = G[v][i];
			if(level[v]<level[e.to] && e.cap>0){
				ll d = dfs(e.to,t,min(f,e.cap));
				if(d>0){
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}
public:
	network_flow(int n){
		N = n;
		G = vvec<edge>(N+1);
		level = iter = vec<int>(N+1);
	}
	void add_edge(int from, int to,ll cap){
		G[from].push_back((edge){to,cap,(int) G[to].size(),false});
		G[to].push_back((edge){from,0,(int) G[from].size()-1,true});
	}
	ll max_flow(int s,int t){
		ll flow = 0;
		for(;;){
			bfs(s);
			if(level[t]<0) return flow;
			for(int i=0;i<=N;i++) iter[i] = 0;
			ll f;
			while((f=dfs(s,t,inf))>0) flow += f;
		}
	}
};

int V,E;

int main(){
	cin >> V >> E;
	network_flow flow(V);
	for(int i=0;i<E;i++){
		int t,c,r;
		cin >> t >> r >> c;
		flow.add_edge(t,r,c);
	}
	cout << flow.max_flow(0,V-1) << endl;
}