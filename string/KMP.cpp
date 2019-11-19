#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(){
    int N;
    string S;
    cin >> N >> S;
    vector<int> cnt(26);
    for(int i=0;i<N;i++){
        cnt[S[i]-'a']++;
    }
    bool judge = false;
    for(int i=0;i<26;i++) if(cnt[i]>1) judge = true;
    if(!judge){
        cout << 0 << endl;
        return 0;
    }
    auto prekmp = [&](string x,int m,vector<int>& kmpnext){
        int i = 0,j = kmpnext[0] = -1;
        while(i<m){
            while(j>-1 && x[i]!=x[j]) j = kmpnext[j];
            i++; j++;
            if(x[i]==x[j]) kmpnext[i] = kmpnext[j];
            else kmpnext[i] = j;
        }
    };
    auto KMP = [&](string x,int m,string y,int n){
        vector<int> kmpnext(m+1);
        int i = 0,j = 0;
        prekmp(x,m,kmpnext);
        while(j<n){
            while(i>-1 && x[i]!=y[j]) i = kmpnext[i];
            i++; j++;
            if(i>=m){
                i = kmpnext[i];
                return true;
            }
        }
        return false;
    };
    auto ok = [&](int len){
        bool res = false;
        for(int i=0;i<=N-2*len;i++){
            string now = S.substr(i,len);
            string ne = "";
            for(int j=i+len;j<N;j++) ne += S[j];
            if(len>ne.size()) continue;
            res |= KMP(now,now.size(),ne,ne.size());
            if(res) return res;
        }
        return res;
    };
    int l = 0,r = N;
    while(l+1<r){
        int m = (l+r)/2;
        if(ok(m)) l = m;
        else r = m;
    } 
    cout << l << endl;
}