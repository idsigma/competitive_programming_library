#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T, class U> using Pa = pair<T, U>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;

template<typename T>
class MonotoneCHT{
private:
    struct line{
        T a,b;
        line(T a,T b):a(a),b(b){}
        bool operator<(const line& r)const{
            return (a!=r.a? a<r.a:b<r.b);
        }
        bool operator>(const line& r)const{
            return (a!=r.a? a>r.a:b>r.b);
        } 
    };
    //直線群
    vector<line> lines;
    //単調性があるか
    bool isMonotonicX;
    function<bool(T l, T r)> comp;

public:
    MonotoneCHT(bool flagX,function<bool(T l, T r)> compFunc)
                :isMonotonicX(flagX),comp(compFunc){
//                    lines.emplace_back(0,0);
    }
    
    //maxのときは不等号の向きが逆！
    bool check(line l1,line l2,line l3){
        if(l1<l3) swap(l1,l3);
        return (long double) (l3.b-l2.b)*(l2.a-l1.a)<=(long double) (l2.b-l1.b)*(l3.a-l2.a);
    }

    void add(T a,T b){
        line l(a,b);
        while(lines.size()>=2 && check(*(lines.end()-2),lines.back(),l)) lines.pop_back();
        lines.emplace_back(l);
    }

    T f(int i,T x){
        return lines[i].a*x+lines[i].b;
    }

    T f(line l,T x){
        return l.a*x+l.b;
    }
    //最小値/最大値を返す
    T get(T x){
        if(isMonotonicX){
            static int head = 0;
            while(lines.size()-head>=2 && comp(f(head, x), f(head + 1, x))) head++;
            return f(head,x);
        }else{
            int l = -1,r = lines.size()-1;
            while(l+1<r){
                int m = (l+r)/2;
                (comp(f(m,x),f(m+1,x))? l:r) = m;
            }
            return f(r,x);
        }
    }
};

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

    CentroidDecomposition(int N,vvec<edge> tree): N(N),g(tree){
        size = used = vec<int>(N,0);
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
    Pa<int,int> search_centroid(int cur,int par,int cmp_size){
        Pa<int,int> res = {1e9,-1};
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

    void dfs(int cur,int par,ll d,vec<ll>& dlist){
        dlist.push_back(d);
        for(auto& e:g[cur]) if(e.to!=par && !used[e.to]){
            dfs(e.to,cur,d+e.dist,dlist);
        }
    }

    int build(int v){
        calc_size(v,-1);
        int centroid = search_centroid(v,-1,size[v]).second;
        used[centroid] = true;
        return centroid;
    }

    void disable(int v){used[v] = true;}
    bool is_alive(int v){return !used[v];}
};

struct query{
    ll v,l;
    int id;
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vvec<edge> g(N);
    for(int i=0;i<N-1;i++){
        int a,b;
        ll c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    vvec<query> L(N);
    int M;
    cin >> M;
    for(int i=0;i<M;i++){
        int v;
        ll l;
        cin >> v >> l;
        v--;
        L[v].push_back({v,l,i});
    }
    vec<ll> ans(M,0);
    CentroidDecomposition CD(N,g);
    queue<int> que;
    vec<ll> depth(N),sum(N);
    que.push(0);
    
    auto dfs = [&](auto&& self,int cur,int par,ll pval,ll ma,vec<Pa<ll,ll>>& line,vec<query>& Q)->void{
        ma = max(ma,pval);
        if(ma==pval) line.emplace_back(pval,sum[cur]-pval*depth[cur]);
        for(auto& l:L[cur]) Q.emplace_back(l);
        for(auto& e:g[cur]) if(e.to!=par && CD.is_alive(e.to)){
            depth[e.to] = depth[cur]+1;
            sum[e.to] = sum[cur]+e.dist;
            self(self,e.to,cur,e.dist,ma,line,Q);
        }
    };

    while(!que.empty()){
        int c = CD.build(CD.build(que.front())); que.pop();
        vec<Pa<ll,ll>> line;
        vec<query> Q;
        depth[c] = 0;
        sum[c] = 0;
        for(auto& l:L[c]) Q.push_back(l);
        for(auto& e:g[c]){
            if(CD.is_alive(e.to)){
                que.push(e.to);
                sum[e.to] = e.dist;
                depth[e.to] = 1;
                dfs(dfs,e.to,-1,e.dist,-1,line,Q);
            }
        }
        if(line.empty()) continue;
        sort(line.begin(),line.end());
        MonotoneCHT<ll> CHT(false,[](ll a,ll b){return a<b;});
        for(auto& l:line) CHT.add(l.first,l.second);
        for(auto& q:Q) if(q.l-depth[q.v]>=0){
            ans[q.id] = max(ans[q.id],sum[q.v]+CHT.get(q.l-depth[q.v]));
        }
    }
    for(auto& x:ans) cout << x << "\n";
}