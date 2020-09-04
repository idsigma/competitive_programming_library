#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T,class U> using P = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

class QuickFind{
private:
    vec<int> G;
    vvec<int> comp;
public:
    QuickFind(int N){
        G.resize(N);
        comp.resize(N);
        iota(G.begin(),G.end(),0);
        for(int i=0;i<N;i++) comp[i].push_back(i);
    }

    void unite(int x,int y){
        x = G[x],y = G[y];
        if(is_same_set(x,y)) return ;
        if(comp[x].size()<comp[y].size()) swap(x,y);
        for(auto& e:comp[y]){
            comp[x].push_back(e);
            G[e] = x;
        }
        comp[y].clear();
    }
    bool is_same_set(int x,int y){return G[x]==G[y];}
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N,Q;
    cin >> N >> Q;
    QuickFind qf(N);
    for(int i=0;i<Q;i++){
        int t,x,y;
        cin >> t >> x >> y;
        if(t==0) qf.unite(x,y);
        else cout << qf.is_same_set(x,y) << endl;
    }
}