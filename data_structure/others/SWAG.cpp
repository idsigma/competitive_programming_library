#include <iostream>
#include <vector>
#include <stack>
#include <functional>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

template<class T> class SWAG{
private:
    struct node{
        T val,sum;
        node(const T& val, const T& sum):val(val),sum(sum){}
    };

    using F = function<T(T,T)>;
    stack<node> front_stack,back_stack;
    F op;
public:
    SWAG(const F op):op(op),front_stack(),back_stack(){};

    void push(const T& x){
        if(back_stack.empty()) back_stack.emplace(x,x);
        else{
            T s{op(back_stack.top().sum,x)};
            back_stack.emplace(x,s);
        }
    }

    void pop(){
        if(front_stack.empty()){
            front_stack.emplace(back_stack.top().val,back_stack.top().val);
            back_stack.pop();
            while(!back_stack.empty()){
                T s{op(back_stack.top().val,front_stack.top().sum)};
                front_stack.emplace(back_stack.top().val,s);
                back_stack.pop();
            }
        }
        front_stack.pop();
    }

    T result(){
        if(front_stack.empty()) return back_stack.top().sum;
        else if(back_stack.empty()) return front_stack.top().sum;
        else return op(front_stack.top().sum,back_stack.top().sum);
    }
};

int main(){
    int N,L;
    cin >> N >> L;
    SWAG<int> S([](int a,int b){return min(a,b);});
    for(int i=0;i<N;i++){
        int a;
        cin >> a;
        S.push(a);
        if(L-1<=i){
            cout << S.result() << (i!=N-1? " ":"\n");
            S.pop();
        }
    }  
}