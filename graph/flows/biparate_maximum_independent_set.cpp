#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <set>
using namespace std;
typedef long long ll;
ll inf = 1e18;

class network_flow{
public:
	int N;
	struct edge{int to; ll cap; int rev; bool is_rev;};
	vector<vector<edge>> G;
	vector<int> level,iter;
	void bfs(int s){
		for(int i=0;i<=N;i++) level[i] = -1;
		queue<int> Q;
		level[s] = 0;
		Q.push(s);
		while(!Q.empty()){
			int v = Q.front(); Q.pop();
			for(int i=0;i<G[v].size();i++){
				edge &e = G[v][i];
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
	network_flow(int n){
		N = n;
		G = vector<vector<edge>>(N+1);
		level = iter = vector<int>(N+1);
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


vector<int> v(200000);
set<int> prime;

void erast(){
	for(int i=0;i<=200000;i++){
		v[i] = 1;
	}
	for(int i=2;i*i<=200000;i++){
		if(v[i]){
			for(int j=0;i*(j+2)<=200000;j++){
				v[i*(j+2)]=0;
			}
		}
	}
	for(int i=2;i<=200000;i++){
		if(v[i]){
			prime.insert(i);
		}
	}
}

int main(){
    erast();
    int N;
    cin >> N;
    vector<int> A(N+1);
    network_flow flow(N+2);
    for(int i=1;i<=N;i++){
        cin >> A[i];
        if(A[i]%2) flow.add_edge(0,i,1);
        else flow.add_edge(i,N+1,1);
    }
    for(int i=0;i<N;i++) for(int j=i+1;j<N;j++){
        if(prime.count(A[i]+A[j])){
            int l = (A[i]%2? i:j);
            int r = (A[i]%2? j:i);
            flow.add_edge(l,r,1);
        }
    }

    int s = flow.max_flow(0,N+1);
    queue<int> Q;
    vector<int> col(N,0);
    for(int i=1;i<=N;i++){
        if(A[i]%2==0) continue;
        bool matched = false;
        for(auto& e:flow.G[i]){
            if(!e.cap) matched = true;
        }        
        if(!matched){
            col[i] = 1;
            Q.push(i);
        }
    }

    while(!Q.empty()){
        int now = Q.front(); Q.pop();
        for(auto& e:flow.G[now]){
            if(e.is_rev xor e.cap){
                if(!col[e.to]){
                    col[e.to] = 1;
                    Q.push(e.to);
                }
            }
        }
    }

    vector<int> ans;
    for(int i=1;i<=N;i++) if(A[i]%2 xor !col[i]) ans.push_back(A[i]);
    cout << s << endl;
    for(int i=0;i<s;i++) cout << ans[i] << (i!=s-1? " ":"");
    cout << "\n";
}