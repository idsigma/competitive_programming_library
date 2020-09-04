#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T, class U> using Pa = pair<T, U>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;

template<class T>
class Compress {
    int N;
    map<T,int> idx;
    map<int,T> value;
    vec<T> v;
    vec<T> cmp;
public:
    Compress(){}
    void add(T x){v.push_back(x);}
    void build(){
        for(auto &x:v) cmp.push_back(x);
        sort(cmp.begin(),cmp.end());
        cmp.erase(unique(cmp.begin(),cmp.end()),cmp.end());
        N = cmp.size();
        for (int i=0;i<N;i++) idx[cmp[i]] = i;
    }
    int id(T val) {return idx[val];}
    T val(int id) {return cmp[id];}
    int size(){return N;}
};

int main() {
    int N;
    cin >> N;
    vec<int> A(N);
    Compress<int> cmp;
    for(int i=0;i<N;i++){
        cin >> A[i];
        cmp.add(A[i]);
    }
    cmp.build();
    for(int i=0;i<N;i++) cout << cmp.id(A[i]) << "\n";
}