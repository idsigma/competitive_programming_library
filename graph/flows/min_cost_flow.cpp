#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
const ll inf = 1e14;

class min_cost_flow{
private:
    int N;
    struct edge{int to; ll cap,cost; int rev;};
    vector<vector<edge>> G;
    vector<ll> h,dist,prevv,preve;
public:
    min_cost_flow(int n){
        N = n;
        G = vector<vector<edge>>(N);
        h = dist = prevv = preve = vector<ll>(N,0);
    }
    void add_edge(int from,int to,ll cap,ll cost){
        G[from].push_back((edge){to,cap,cost,(int) G[to].size()});
        G[to].push_back((edge){from,0,-cost,(int) G[from].size()-1});
    }
    ll answer(int s,int t,ll f){
        ll res = 0;
        fill(h.begin(),h.end(),0);
        while(f>0){
            priority_queue<P,vector<P>,greater<P>> Q;
            fill(dist.begin(),dist.end(),inf);
            dist[s] = 0;
            Q.push(P(0,s));
            while(!Q.empty()){
                P p = Q.top(); Q.pop();
                int v = p.second;
                if(dist[v]<p.first) continue;
                for(int i=0;i<G[v].size();i++){
                    edge &e = G[v][i];
                    if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
                        dist[e.to] = dist[v]+e.cost+h[v]-h[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        Q.push(P(dist[e.to],e.to));
                    }
                }
            }
            if(dist[t]==inf) return -1;
            for(int v=0;v<N;v++) h[v] += dist[v];
            ll d = f;
            for(int v=t;v!=s; v=prevv[v]){
                d = min(d,G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d*h[t];
            for(int v=t;v!=s;v=prevv[v]){
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};

int N,M,F;

int main(){
    cin >> N >> M >> F;
    min_cost_flow flow(N+1);
    int u,v,c,d;
    for(int i=0;i<M;i++){
        cin >> u >> v >> c >> d;
        flow.add_edge(u,v,c,d);
    }
    cout << flow.answer(0,N-1,F) << endl;
}