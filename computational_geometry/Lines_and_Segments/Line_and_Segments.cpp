#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;
using R = double;
using P = complex<R>;
#define x real()
#define y imag()
const R eps = 1e-9,PI = acos(-1);

bool equal(R a,R b){return abs(b-a)<eps;}
bool equal0(R a){return equal(a,0.0);}

P operator*(const P& p,const R& d){
    return P(p.x*d,p.y*d);
}

istream &operator>>(istream& is,P& p){
    R a,b;
    is >> a >> b;
    p = P(a,b);
    return is;
}

ostream &operator<<(ostream& os,P& p){
    os << fixed << setprecision(10) << p.real() << " " << p.imag();
}
//内積
double dot(P a,P b) {return (conj(a)*b).real();}
//外積
double cross(P a,P b) {return (conj(a)*b).imag();}

struct L{
    P a,b;
    L(P a,P b):a(a),b(b){}
    L(R A,R B,R C){
        if(equal(A,0)) a = P(0,C/B),b = P(1,C/B);
        else if(equal(B,0)) b = P(C/A,0),b = P(C/A,1);
        else a = P(0,C/B),b = P(C/A,0);
    }
};

//pをbに射影
P projection(P p,P b) {return b*dot(p,b)/norm(b);}

//pとp1 to p2 に射影
P projection(L l,P p){
    p -= l.a; l.b -= l.a;
    P proj = projection(p,l.b);
    return l.a+proj;
}

struct S:L{
    S(P a,P b):L(a,b){}
};

//点の回転方向を判定
int ccw(P p0,P p1,P p2){
    p1 -= p0,p2 -= p0;
    if(cross(p1,p2)>eps) return 1; //"COUNTER_CLOCKWISE"
    if(cross(p1,p2)<-eps) return -1; //"CLOCKWISE"
    if(dot(p1,p2)<0) return 2; //"ONLINE_BACK"
    if(norm(p1)<norm(p2)) return -2; //"ONLINE_FRONT"
    return 0; //"ON_SEGMENT"
}

bool is_parallel(L l1,L l2){
    return equal0(cross(l1.b-l1.a,l2.b-l2.a));
}

bool is_orthogonal(L l1,L l2){
    return equal0(dot(l1.b-l1.a,l2.b-l2.a));
}

//pをlに関して対称移動
P reflection(L l,P p){
    P pj = projection(l,p);
    return 2.0*pj-p;
}

//pがl上にあるか
bool is_online(L l,P p){
    return abs(ccw(l.a,l.b,p))!=1;
}

bool is_onsegment(S s,P p){
    return ccw(s.a,s.b,p)==0;
}

//線分の交差判定
bool intersect(S s,S t){
    return ccw(s.a,s.b,t.a)*ccw(s.a,s.b,t.b)<=0 && ccw(t.a,t.b,s.a)*ccw(t.a,t.b,s.b)<=0;
}

//2直線の交点
P crosspoint(L l1,L l2){
    R a = cross(l1.b-l1.a,l2.b-l2.a);
    R b = cross(l1.b-l1.a,l1.b-l2.a);
    if(equal0(abs(a)) && equal0(abs(b))) return l2.a;
    return l2.a+(l2.b-l2.a)*b/a;
}

P crosspoint(S s1, S s2){
    return crosspoint(L(s1),L(s2));
}

R dist(P a,P b){
    return abs(a-b);
}

R dist(L l,P p){
    return abs(p-projection(l,p));
}

R dist(L l1,L l2){
    return is_parallel(l1,l2)? 0:dist(l1,l2.a);
}

R dist(S s,P p){
    P r = projection(s,p);
    if(is_onsegment(s,r)) return abs(r-p);
    return min(dist(s.a,p),dist(s.b,p));
}

R dist (S s1,S s2){
    if(intersect(s1,s2)) return 0;
    return min({dist(s1,s2.a),dist(s1,s2.b),
    dist(s2,s1.a),dist(s2,s1.b)});
}

int main(){
    int Q;
    cin >> Q;
    for(int i=0;i<Q;i++){
        P p1,p2,p3,p4;
        cin >> p1 >> p2 >> p3 >> p4;
        R d = dist(S(p1,p2),S(p3,p4));
        cout << fixed << setprecision(10) << d << endl;
    }
}