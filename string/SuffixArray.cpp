#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T,class U> using Pa = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

class SuffixArray{
public:
    vec<int> SA;
    const string S;
    int N;
    SuffixArray(const string& S):S(S){
        N = S.size();
        SA.resize(N);
        iota(SA.begin(),SA.end(),0);
        sort(SA.begin(),SA.end(),[&](int i,int j){
            return S[i]==S[j]? i>j:S[i]<S[j];
        });
        vec<int> classes(N),C(S.begin(),S.end()),cnt(S.size());
        for(int len=1;len<N;len<<=1){
            for(int i=0;i<N;i++){
                if(i>0 && C[SA[i-1]]==C[SA[i]] && 
                SA[i-1]+len<N && C[SA[i-1]+len/2]==C[SA[i]+len/2]){
                    classes[SA[i]] = classes[SA[i-1]];
                }else{
                    classes[SA[i]] = i;
                }
            }
            iota(cnt.begin(),cnt.end(),0);
            copy(SA.begin(),SA.end(),C.begin());
            for(int i=0;i<N;i++){
                int sl = C[i]-len;
                if(sl>=0) SA[cnt[classes[sl]]++] = sl;
            }
            classes.swap(C);
        }
    }

    int operator[](int k)const{
        return SA[k];
    }

    int size()const{
        return N;
    }

    bool lt_substr(const string& T,int si=0,int ti=0){
        int sn = N,tn = T.size();
        while(si<sn && ti<tn){
            if(S[si]<T[ti]) return true;
            if(S[si]>T[ti]) return false;
            si++; ti++;
        }
        return si>=sn && ti<tn;
    }

    int lower_bound(const string& T,int si=0,int ti=0){
        int l = -1,r = N;
        while(l+1<r){
            int m = (l+r)>>1;
            (lt_substr(T,SA[m])? l:r) = m;
        }
        return r;
    }

    Pa<int,int> lower_upper_bound(string& T){
        int id = lower_bound(T);
        int l = id-1,r = N;
        T.back()++;
        while(l+1<r){
            int m = (l+r)>>1;
            (lt_substr(T,SA[m])? l:r) = m;
        }
        T.back()--;
        return {id,r};
    }
};

class LongestCommonPrefixArray{
    const SuffixArray &SA;
    vec<int> LCP,rank;
    int N;
public:
    LongestCommonPrefixArray(const SuffixArray& SA):SA(SA),LCP(SA.size()){
        int N = SA.size();
        rank.resize(N);
        for(int i=0;i<N;i++) rank[SA[i]] = i;
        for(int i = 0, h = 0; i < SA.size(); i++) {
        if(rank[i]+1<SA.size()) {
            for(int j=SA[rank[i]+1]; max(i,j)+h<SA.size() && SA.S[i+h]==SA.S[j+h]; ++h);
                LCP[rank[i]+1] = h;
                if(h>0) --h;
            }
        }
    }

    int operator[](int k)const{
        return LCP[k];
    }

    int size()const{
        return N;
    }
};

ll largest_rectangle(vector<ll>& A){
    int N = A.size()-1;
    ll ans = 0;
    stack<P<ll,ll>> s;
    for(ll i=0;i<=N;i++){
        ll pos = i;
        while(!s.empty() && s.top().first>=A[i]){
            P<ll,ll> p = s.top(); s.pop();
            ans = max(ans,p.first*(i-p.second+1));
            pos = p.second;
        }
        s.push({A[i],pos});
    }
    return ans;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    string S,T;
    cin >> S >> T;
    reverse(S.begin(),S.end());
    reverse(T.begin(),T.end());
    SuffixArray SA(S);
    LongestCommonPrefixArray LCP(S);
    vec<ll> A;
    ll ans = 0,h = 1e9;
    for(int i=0;i<N;i++){
        if(T[SA[i]]!='1') ans = max(ans,(ll) N-SA[i]);
        if(i==0) continue;
        if(T[SA[i]]=='1'){
            if(T[SA[i-1]]!='1'){
                h = min(h,(ll) LCP[i]);
            }
        }else{
            if(T[SA[i-1]]=='1'){
                h = min(h,(ll) LCP[i]);
                A.push_back(h);
            }else{
                h = LCP[i];
                A.push_back(h);
            }
        }
    }
    A.push_back(0);
    ans = max(ans,largest_rectangle(A));
    cout << ans << endl;
}