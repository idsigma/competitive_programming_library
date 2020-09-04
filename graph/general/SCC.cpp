#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T,class U> using P = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

class strong_components{
public:
    vector<vector<int>> v,rv,nv;
    vector<int> rs,visited,cmp,cmp_size;
    void dfs(int n){
        visited[n] = 1;
        for(auto x:v[n]) if(!visited[x]) dfs(x);
        rs.push_back(n);
    }
    void rdfs(int n,int cnt){
        visited[n] = 1;
        cmp[n] = cnt;
        for(auto x:rv[n]) if(!visited[x]) rdfs(x,cnt);
    }
    strong_components(int N,vector<vector<int>>& graph){
        v = graph;
        rv = vector<vector<int>>(N);
        visited = cmp = cmp_size = vector<int>(N,0);
        for(int i=0;i<N;i++) for(auto x:v[i]) rv[x].push_back(i);
        for(int i=0;i<N;i++) if(!visited[i]) dfs(i);
        for(int i=0;i<N;i++) visited[i] = 0;
        int now = 0;
        for(int i=rs.size()-1;i>=0;i--) if(!visited[rs[i]]) rdfs(rs[i],now++);
        nv = vector<vector<int>>(now+1);
        for(int i=0;i<N;i++){
            for(auto x:v[i]){
                if(cmp[i]!=cmp[x]){
                    nv[cmp[i]].push_back(cmp[x]);
                }
            }
        }
        for(int i=0;i<N;i++) cmp_size[cmp[i]]++;
    }
    int find(int n){return cmp[n];}
    int size(int n){return cmp_size[cmp[n]];}
    bool is_same_group(int a,int b){return cmp[a]==cmp[b];}
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N,M,H;
    cin >> N >> M >> H;
    vec<int> A(N);
    vvec<int> g(N);
    set<P<int,int>> s;
    for(int i=0;i<N;i++) cin >> A[i];
    for(int i=0;i<M;i++){
        int a,b;
        cin >> a >> b;
        a--; b--;
        if((A[a]+1)%H==A[b] && !s.count({a,b})){
            s.insert({a,b});
            g[a].push_back(b);
        }
        if((A[b]+1)%H==A[a] && !s.count({b,a})){
            s.insert({b,a});
            g[b].push_back(a);
        }
    }
    strong_components scc(N,g);
    int si = 1e9,ans = -1;
    for(int i=0;i<N;i++) if(scc.nv[scc.find(i)].size()==0 && si>scc.size(i)){
        si = scc.size(i);
        ans = scc.find(i);
    }
    cout << si << endl;
    for(int i=0;i<N;i++) if(scc.find(i)==ans) cout << i+1 << " ";
    cout << endl;
}