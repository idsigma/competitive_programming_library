#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <set>
using namespace std;

class strong_components{
private:
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
public:
    strong_components(int N,vector<vector<int>>& graph){
        v = graph;
        rv = vector<vector<int>>(N);
        visited = cmp = cmp_size = vector<int>(N,0);
        for(int i=0;i<N;i++) for(auto x:v[i]) rv[x].push_back(i);
        for(int i=0;i<N;i++) if(!visited[i]) dfs(i);
        for(int i=0;i<N;i++) visited[i] = 0;
        int now = 0;
        for(int i=(int) rs.size()-1;i>=0;i--) if(!visited[rs[i]]) rdfs(rs[i],now++);
        nv = vector<vector<int>>(now);
        for(int i=0;i<N;i++){
            for(auto x:v[i]){
                if(cmp[i]!=cmp[x]){
                    nv[cmp[i]].push_back(cmp[x]);
                    cmp_size[cmp[x]]++;
                }
            }
        }
    }
    int find(int n){return cmp[n];}
    bool is_same_group(int a,int b){return cmp[a]==cmp[b];}
};

class SAT{
private:
    int N;
    vector<vector<int>> v;
public:
    SAT(int N):N(N){
        v = vector<vector<int>>(2*N);
    }
    void add_closure(int x, int y ,bool bx, bool by){
        v[x+(!bx)*N].push_back(y+by*N);
        v[y+(!by)*N].push_back(x+bx*N);
    }
    vector<int> solve(){
        strong_components scc(2*N,v);
        //不可能か判定
        vector<int> res(N);
        for(int i=0;i<N;i++){
            //同じ強連結成分にあったらだめ
            if(scc.is_same_group(i,i+N)) return vector<int> {};
            res[i] = (scc.find(i)<scc.find(i+N));
        }
        return res;
    }
};

int main(){
    int N;
    cin >> N;
    vector<string> U(N);
    for(int i=0;i<N;i++) cin >> U[i];
    if(N>=60){
        cout << "Impossible" << endl;
        return 0;
    }
    SAT sat(N);
    for(int i=0;i+1<N;i++) for(int j=i+1;j<N;j++){
        for(int k=0;k<2;k++) for(int l=0;l<2;l++){
            set<string> s;            
            string s1 = U[i].substr(0,1+k),t1 = U[i].substr(1+k,2-k);
            string s2 = U[j].substr(0,1+l),t2 = U[j].substr(1+l,2-l);
            s.insert(s1),s.insert(s2),s.insert(t1),s.insert(t2);
            if(s.size()!=4) sat.add_closure(i,j,k,l);
        }
    }
    vector<int> res = sat.solve();
    if(res.empty()){
        cout << "Impossible" << endl;
        return 0;
    }
    for(int i=0;i<N;i++){
        if(res[i]) cout << U[i][0] << " " << U[i][1] << U[i][2] << endl;
        else cout << U[i][0] << U[i][1] << " " << U[i][2] << endl;
    }
}