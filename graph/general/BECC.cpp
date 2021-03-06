#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
using P = pair<int,int>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

class BECC{
private:
    int N;
    vvec<int> G;
    vec<int> order,inS;
    stack<int> S,roots;
    vec<int> cmp;
public:
    vec<P> bridge;
    vvec<int> bccs;
    vvec<int> dcmp;
    BECC(int n,vvec<int> graph){
        N = n;
        G = graph;
        order = inS = cmp = vec<int>(N,0);
    }
    void dfs(int cur,int prev,int k){
        order[cur] = ++k; //訪問順に番号付け
        S.push(cur); inS[cur] = true;//訪問した頂点の集合に追加
        roots.push(cur);//各bccの根を管理
        for(auto to:G[cur]){
            if(order[to]==0) dfs(to,cur,k);
            else if(to!=prev && inS[to]){//後退辺なら
                while(order[roots.top()]>order[to]) roots.pop();//(to,cur]を捨てる
            }
        }
        if(cur==roots.top()){
            if(prev!=-1) bridge.emplace_back(minmax(prev,cur));//根でないなら橋になる
            vec<int> bcc;
            while(true){
                int node = S.top(); S.pop(); inS[node] = false;//nodeを捨てる
                bcc.emplace_back(node);//nodeをbccに追加
                cmp[node] = bccs.size();
                if(node==cur) break;
            }
            bccs.emplace_back(bcc);
            roots.pop();
        }
    }
    void bridge_detection(){
        int k = 0;
        for(int i=0;i<N;i++) if(order[i]==0) dfs(i,-1,k);
    }
    int find(int n){return cmp[n];}
    int cmp_size(int n){return bccs[cmp[n]].size();}
    void decomposition(){
        int k = 0;
        for(int i=0;i<N;i++) if(order[i]==0) dfs(i,-1,k);
        dcmp = vvec<int>(bccs.size()+1);
        for(auto x:bridge){
            dcmp[cmp[x.first]].push_back(cmp[x.second]);
            dcmp[cmp[x.second]].push_back(cmp[x.first]);
        }
    }
};

int N,M;
int main(){
    cin >> N >> M;
    vector<vector<int>> v(N+1);
    int a,b;
    for(int i=0;i<M;i++){
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    BECC becc(N,v);
    becc.bridge_detection();
    for(auto& x:becc.bridge) if(x.first>x.second) swap(x.first,x.second);
    sort(becc.bridge.begin(),becc.bridge.end());
    for(auto& x:becc.bridge) cout << x.first << " " << x.second << endl;
}