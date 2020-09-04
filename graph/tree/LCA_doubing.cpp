#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T, class U> using Pa = pair<T, U>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;

struct edge{
    int to;
    ll d;
};

template<class T>
class LeastCommonAncestor{
private:
    vvec<edge> g;
    vvec<int> parent;
    vvec<T> value;
    vec<int> depth;
    int h = 0;
    void dfs(int cur,int par,int d){
        parent[0][cur] = par;
        depth[cur] = d;
        for(auto e:g[cur]){
            if(e.to!=par) dfs(e.to,cur,d+1);
        }
    }
    void dfs(int cur,int par,int d,T val){
        parent[0][cur] = par;
        depth[cur] = d;
        value[0][cur] = val;
        for(auto e:g[cur]){
            if(e.to!=par) dfs(e.to,cur,d+1,e.d);
        }
    }
public:
    LeastCommonAncestor(){}
    LeastCommonAncestor(int N,int root,vvec<edge>& tree){
        while((1<<h)<=N) h++;
        g = tree;
        parent = vvec<int>(h,vec<int>(N,0));
        depth = vec<int>(N,0);
        dfs(root,-1,0);
        for(int j=0;j+1<h;j++){
            for(int i=0;i<N;i++){
                if(parent[j][i]<0) parent[j+1][i] = -1;
                else parent[j+1][i] = parent[j][parent[j][i]];
            }
        }
    }
    int lca(int u,int v){
        if(depth[u]>depth[v]) swap(u,v);
        for(int j=0;j<h;j++){
            if((depth[v]-depth[u]) >> j&1) v = parent[j][v];
        }
        if(u==v) return u;
        for(int j=h-1;j>=0;j--){
            if(parent[j][u]!=parent[j][v]){
                u = parent[j][u];
                v = parent[j][v];
            }
        }
        return parent[0][u];
    }

    template<class F>
    LeastCommonAncestor(int N,int root,vvec<edge>& tree,F& f,T e){
        while((1<<h)<=N) h++;
        g = tree;
        parent = vvec<int>(h,vec<int>(N,0));
        value = vvec<T>(h,vec<T>(N,0));
        depth = vec<int>(N,0);
        dfs(root,-1,0,e);
        for(int j=0;j+1<h;j++){
            for(int i=0;i<N;i++){
                if(parent[j][i]<0){
                    parent[j+1][i] = -1;
                    value[j+1][i] = e;
                }else{
                    parent[j+1][i] = parent[j][parent[j][i]];
                    value[j+1][i] = f(value[j][i],value[j][parent[j][i]]);
                }
            }
        }
    }
    //辺クエリ
    template<class F>
    T query(int u,int v,F& f,T e,bool isedge=true){
        if(depth[u]>depth[v]) swap(u,v);
        T uval = e,vval = e;
        for(int j=0;j<h;j++){
            if((depth[v]-depth[u])>>j&1){
                vval = f(vval,value[j][v]);
                v = parent[j][v];
            }
        }
        if(u==v) return vval;
        for(int j=h-1;j>=0;j--){
            if(parent[j][u]!=parent[j][v]){
                uval = f(uval,value[j][u]);
                u = parent[j][u];
                vval = f(vval,value[j][v]);
                v = parent[j][v];
            }
        }
        uval = f(uval,value[0][u]);
        vval = f(vval,value[0][v]);
        T res = f(uval,vval);
        if(isedge) return res;
        else return f(res,value[0][parent[0][u]]);
    }
    int dep(int n){return depth[n];}
};

class UnionFind{
private:
    vec<int> p,s;
    int cnt;
public:
    UnionFind(){}
    UnionFind(int N):cnt(N),s(N,1),p(N){
        iota(p.begin(),p.end(),0);
    }
    int find(int x){
        if(p[x]==x) return x;
        else return p[x] = find(p[x]);
    }
    void unite(int x,int y){
        x = find(x); y = find(y);
        if(x==y) return;
        if(s[x]>s[y]) swap(x,y);
        p[x] = y;
        s[y] += s[x];
        cnt--;
    }
    bool is_same_set(int x,int y) {return find(x)==find(y);}
    int size(int x) {return s[find(x)];}
    int compnents_number(){return cnt;}
};

struct E{
    int a,b,id;
    ll c;
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    vec<E> edges(M);
    for(int i=0;i<M;i++){
        int a,b;
        ll c;
        cin >> a >> b >> c;
        a--; b--;
        edges[i] = {a,b,i,c};
    }
    sort(edges.begin(),edges.end(),[](E& a,E& b){return a.c<b.c;});
    UnionFind uf(N);
    set<int> s;
    ll now = 0;
    vec<ll> ans(M);
    vvec<edge> g(N);
    vec<E> use;
    for(auto& e:edges){
        if(!uf.is_same_set(e.a,e.b)){
            s.insert(e.id);
            uf.unite(e.a,e.b);
            now += e.c;
            g[e.a].push_back({e.b,e.c});
            g[e.b].push_back({e.a,e.c});
            use.push_back(e);
        }
    }
    auto op = [](ll a,ll b){return max(a,b);};
    
    LeastCommonAncestor LCA(N,0,g,op,-1LL);

    for(auto& e:edges){
        if(s.count(e.id)) ans[e.id] = now;
        else{
            ans[e.id] = now+e.c-LCA.query(e.a,e.b,op,-1LL);
        }
    }
    for(auto& x:ans) cout << x << "\n";
}