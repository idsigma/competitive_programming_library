#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<typename T,typename U> using P = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

struct edge{
    int to,id;
    ll dist;
    edge(int to,ll dist=1,int id=1):to(to),id(id),dist(dist){};
};

class CentroidDecomposition{
public:
    int N;
    vvec<edge> g;
    vec<int> size;
    vec<int> used;
    ll ans;

    CentroidDecomposition(int N,vvec<edge> tree): N(N),g(tree){
        size = used = vec<int>(N,0);
        ans = 0;
    }

    int calc_size(int cur,int par){
        int c = 1;
        for(auto& x:g[cur]){
            if(x.to==par || used[x.to]) continue;
            c += calc_size(x.to,cur);
        }
        return size[cur] = c;
    }

    //tは連結成分の大きさ
    //cur以下のうち、削除して残る最大の部分木の大きさを返す
    P<int,int> search_centroid(int cur,int par,int cmp_size){
        P<int,int> res = {1e9,-1};
        int s = 1,ma = 0;
        for(auto& x:g[cur]){
            if(x.to==par || used[x.to]) continue;
            res = min(res,search_centroid(x.to,cur,cmp_size)); 
            ma = max(ma,size[x.to]);
            s += size[x.to];
        }
        //子と親の部分木の大きい方
        ma = max(ma,cmp_size-s);
        res = min(res,{ma,cur});
        return res;
    }

    //テンプレここまで

    void dfs(int cur,int par,ll d,vec<ll>& dlist){
        dlist.push_back(d);
        for(auto& e:g[cur]) if(e.to!=par && !used[e.to]){
            dfs(e.to,cur,d+e.dist,dlist);
        }
    }

    void solve(int v,ll X){
        calc_size(v,-1);
        int centroid = search_centroid(v,-1,size[v]).second;
        used[centroid] = true;
        vec<ll> d;
        vvec<ll> ed;
        vvec<ll> esum;
        for(auto& e:g[centroid]){
            if(used[e.to]) continue;
            vec<ll> d2;
            dfs(e.to,-1,e.dist,d2);
            sort(d2.begin(),d2.end());
            ed.push_back(d2);
            for(auto& x:d2) d.push_back(x);
            int si = d2.size();
            vec<ll> s(si+1);
            for(int j=0;j<si;j++) s[j+1] = s[j]+d2[j];
            esum.push_back(s);
        }
        if(ed.empty()) return ;
        int n = d.size();
        int m = ed.size();
        sort(d.begin(),d.end());
        vec<ll> sum(n+1);
        for(int i=0;i<n;i++) sum[i+1] = sum[i]+d[i];
        int id = lower_bound(d.begin(),d.end(),X)-d.begin();
        ans += 2*(sum[id]+(n-id)*X);
        ll dmin = 1e18;
        for(auto& e:g[centroid]) if(!used[e.to]){
            if(e.dist>X) ans -= 2*X;
            else ans -= 2*e.dist;
            dmin = min(dmin,e.dist);
        }
        for(auto& e:g[centroid]) if(!used[e.to]){
            ans += 2*min({e.dist,dmin+X,(N-((int) g[e.to].size()+(int) g[centroid].size())>=1? 2*X:(ll) 1e18)});
        }
        for(int i=0;i<m;i++){
            int n2 = ed[i].size();
            for(auto& x:ed[i]){
                ll id = lower_bound(d.begin(),d.end(),X-x)-d.begin();
                ans += id*x+sum[id]+(n-id)*X;
                ll id2 = lower_bound(ed[i].begin(),ed[i].end(),X-x)-ed[i].begin();
                ans -= id2*x+esum[i][id2]+(n2-id2)*X;
            }
        }
        for(auto& e:g[centroid]) if(!used[e.to]) solve(e.to,X);
    }
    ll solve(ll X){
        solve(0,X);
        return ans/2;
    }
};
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll N,X;
    cin >> N >> X;
    vvec<edge> tree(N);
    for(int i=0;i<N-1;i++){
        ll a,b,c;
        cin >> a >> b >> c;
        a--; b--;
        tree[a].push_back(edge(b,c));
        tree[b].push_back(edge(a,c));
    }
    CentroidDecomposition C(N,tree);
    cout << C.solve(X) << endl;
}