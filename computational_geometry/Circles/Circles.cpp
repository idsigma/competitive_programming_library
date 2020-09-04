#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;
using R = double;
using P = complex<R>;
#define x real()
#define y imag()
const R eps = 1e-8,PI = acos(-1);

bool equal(R a,R b){return abs(b-a)<eps;}
bool equal0(R a){return equal(a,0.0);}

P operator*(const P& p,const R& d){
    return P(p.x*d,p.y*d);
}

namespace std{
    bool operator<(const P& a,const P& b){
        return abs(a.x-b.x)>eps? a.x<b.x:a.y<b.y;
    }
};

istream &operator>>(istream& is,P& p){
    R a,b;
    is >> a >> b;
    p = P(a,b);
    return is;
}

ostream &operator<<(ostream& os,P& p){
    os << fixed << setprecision(10) << p.real() << " " << p.imag();
    return os;
}
//内積
double dot(P a,P b) {return (conj(a)*b).real();}
//外積
double cross(P a,P b) {return (conj(a)*b).imag();}

struct L{
    P a,b;
    L(){};
    L(P a,P b):a(a),b(b){}
    L(R A,R B,R C){
        if(equal(A,0)) a = P(0,C/B),b = P(1,C/B);
        else if(equal(B,0)) b = P(C/A,0),b = P(C/A,1);
        else a = P(0,C/B),b = P(C/A,0);
    }
};

struct S:L{
    S(){}
    S(P a,P b):L(a,b){}
};

using Polygon = vec<P>;

P crosspoint(L l1,L l2);
P rotate(P p,R theta);

struct C{
    P p;
    R r;
    C(P p,R r):p(p),r(r){}
    C(P a,P b,P c){
        P d1 = rotate(P(b-a),PI/2),m1 = (a+b)*0.5;
        L l1(m1,m1+d1);
        P d2 = rotate(P(c-b),PI/2),m2 = (b+c)*0.5;
        L l2(m2,m2+d2);
        p = crosspoint(l1,l2);
        r = abs(a-p);
    }
};

//pを原点中心に反時計回りにtheta回転する
P rotate(P p,R theta){
    return P(cos(theta)*p.x-sin(theta)*p.y,sin(theta)*p.x+cos(theta)*p.y);
}

//p1をp2中心にtheta回転する
P rotate(P p1,P p2,R theta){
    return p1+rotate(p2-p1,theta);
}

//a-b-cの角度のうち小さい方
R get_angle(P a,P b,P c){
    P v(b-a),w(c-b);
    R alpha = atan2(v.y,v.x),beta = atan2(w.y,w.x);
    if(alpha>beta) swap(alpha,beta);
    R theta = beta-alpha;
    return min(theta,2*PI-theta);
}

//a-b-cの角度
R get_signed_angle(P a,P b,P c){
    return arg((c-b)*conj(a-b));
}

//pをbに射影
//P projection(P p,P b) {return b*dot(p,b)/norm(b);}

//pとp1 to p2 に射影
P projection(L l,P p){
    R t = dot(p-l.a,l.a-l.b)/norm(l.a-l.b);
    return l.a+(l.a-l.b)*t;
}

P projection(S l,P p){
    R t = dot(p-l.a,l.a-l.b)/norm(l.a-l.b);
    return l.a+(l.a-l.b)*t;
}

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
    return pj*2.0-p;
}


R dist(L l,P p);
R dist(P a,P b);
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

//円と直線の交差判定
bool intersect(C c,L l){
    return dist(l,c.p)<=c.r+eps;
}

//点が円周上にあるか
bool on_circle(C c,P p){
    return abs(abs(p-c.p)-c.r)<eps;
}

//点が円の内部(周上含む)にあるか
bool in_circle(C c,P p){
    return abs(c.p-p)<c.r+eps;
}

/*円と線分の関係
交点をいくつもつか？
*/
bool intersect(C c,S s){
    if(norm(projection(s,c.p)-c.p)-c.r*c.r>eps) return 0;
    R d1 = dist(c.p,s.a),d2 = dist(c.p,s.b);
    if(d1<c.r+eps && d2<c.r+eps) return 0;
    if(d1<c.r-eps && d2>c.r+eps || d1>c.r-eps && d2<c.r+eps) return 1;
    const P h = projection(s,c.p);
    if(dot(s.a-h,s.b-h)<0) return 2;
    return 0;
}

/*円と円の関係
4:交点を持たない
3:外接する
2:2つの相異なる交点をもつ
1:内接する
0:一方がもう一方の内部にある
*/

int intersect(C c1,C c2){
    if(c1.r<c2.r) swap(c1,c2);
    R d = dist(c1.p,c2.p);
    if(c1.r+c2.r<d) return 4;
    if(equal(c1.r+c2.r,d)) return 3;
    if(c1.r-c2.r<d) return 2;
    if(equal(c1.r-c2.r,d)) return 1;
    return 0;
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

R area(Polygon& v){
    int n = v.size();
    R res = 0;
    for(int i=0;i+2<n;i++){
        res += cross(v[i+1]-v[0],v[i+2]-v[0]);
    }
    return res/2;
}

bool is_convex(Polygon& v){
    int n = v.size();
    for(int i=0;i<n;i++){
        P a = v[i%n],b = v[(i+1)%n],c = v[(i+2)%n];
        if(cross(b-a,c-a)<-eps) return false;
    }
    return true;
}

enum{
    OUT,ON,IN
};

//点pと多角形vの関係
int contains(Polygon& v,P p){
    bool in = false;
    int n = v.size();
    for(int i=0;i<n;i++){
        P a = v[i]-p,b = v[(i+1)%n]-p;
        if(a.y>b.y) swap(a,b);
        if(a.y<=0 && 0<b.y && cross(a,b)<0) in = !in;
        if(is_onsegment(S(a,b),P(0,0))) return ON;
    }
    return in? IN:OUT;
}

Polygon convex_hull(Polygon& v){
    int n = v.size();
    Polygon res;
    sort(v.begin(),v.end(),[](P& a,P& b){
        return (a.x!=b.x? a.x<b.x:a.y<b.y);
    });
    for(int i=0;i<n;i++){
        if(i<2){
            res.push_back(v[i]);
            continue;
        }
        while(true){
            int s = res.size();
            if(s<2){
                res.push_back(v[i]);
                break;
            }
            R c = cross(res[s-1]-res[s-2],v[i]-res[s-2]);
            if(c<-eps){
                res.pop_back();
            }else{
                res.push_back(v[i]);
                break;
            }
        }
    }
    reverse(v.begin(),v.end());
    for(int i=0;i<n;i++){
        while(true){
            int s = res.size();
            if(v[i]==res.back()) break;
            if(s<2){
                res.push_back(v[i]);
                break;
            }
            R c = cross(res[s-1]-res[s-2],v[i]-res[s-2]);
            if(c<-eps){
                res.pop_back();
            }else{
                res.push_back(v[i]);
                break;
            }
        }
    }
    res.pop_back();
    return res;
}

R convex_diameter(Polygon v){
    int n = v.size();
    int l = 0,r = 0;
    for(int i=1;i<n;i++){
        if(v[i].y>v[l].y) l = i;
        if(v[i].y<v[r].y) r = i;
    }
    R res = abs(v[l]-v[r]);
    int i = l,mai = l,j = r,maj = r;
    do{
        if(cross(v[(i+1)%n]-v[i],v[(j+1)%n]-v[j])>=0) j = (j+1)%n;
        else i = (i+1)%n;
        if(abs(v[i]-v[j])>res){
            res = abs(v[i]-v[j]);
            mai = i; maj = j;
        }
    }while(i!=l || j!=r);
    return res;
}

Polygon convex_cut(Polygon& v,L l){
    Polygon res;
    int n = v.size();
    for(int i=0;i<n;i++){
        P now = v[i],ne = v[(i+1)%n];
        if(ccw(l.a,l.b,now)!=-1) res.push_back(now);
        if(ccw(l.a,l.b,now)*ccw(l.a,l.b,ne)<0){
            res.push_back(crosspoint(L(now,ne),l));
        }
    }
    return res;
}

//円と直線の交点
pair<P,P> crosspoint(C c,L l){
    P pr = projection(l,c.p);
    P e = (l.b-l.a)/dist(l.b,l.a);
    if(equal(dist(l,c.p),c.r)) return {pr,pr};
    R base = sqrt(c.r*c.r-norm(pr-c.p));
    pair<P,P> res = {pr-e*base,pr+e*base};
    return res;
}

//円と線分の交点
pair<P,P> crosspoint(C c,S s){
    L l(s.a,s.b);
    if(intersect(c,s)==2) return crosspoint(c,l);
    auto res = crosspoint(c,l);
    if(dot(s.a-res.first,s.b-res.first)<0) res.second = res.first;
    else res.first = res.second;
    return res;
}

pair<P,P> crosspoint(C c1,C c2){
    R d = dist(c1.p,c2.p);
    R a = acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*c1.r*d));
    R t = atan2(c2.p.y-c1.p.y,c2.p.x-c1.p.x);
    P p1 = c1.p+P(cos(t+a)*c1.r,sin(t+a)*c1.r);
    P p2 = c1.p+P(cos(t-a)*c1.r,sin(t-a)*c1.r);
    return {p1,p2};
}

/*
点pを通る円cの接線
2つの接点を返す(傾きは自明なので)
*/
pair<P,P> tangent(C c,P p){
    return crosspoint(c,C(p,sqrt(norm(c.p-p)-c.r*c.r)));
}

/*
円と円の共通接線
これは直線を返す
*/

vec<L> tangent(C c1,C c2){
    vec<L> res;
    if(c1.r<c2.r) swap(c1,c2);
    R g = norm(c1.p-c2.p);
    if(equal0(g)) return res;
    P u = (c2.p-c1.p)/sqrt(g);
    P v = rotate(u,PI*0.5);
    for(int s:{-1,1}){
        R h = (c1.r+s*c2.r)/sqrt(g);
        if(equal0(1-h*h)){
            res.emplace_back(c1.p+u*c1.r,c1.p+(u+v)*c1.r);
        }else if(1-h*h>0){
            P uu = u*h,vv = v*sqrt(1-h*h);
            res.emplace_back(c1.p+(uu+vv)*c1.r,c2.p-(uu+vv)*c2.r*s);
            res.emplace_back(c1.p+(uu-vv)*c1.r,c2.p-(uu-vv)*c2.r*s);
        }
    }
    return res;
}

R area(Polygon v,C c){
    int n = v.size();
    if(n<3) return 0;
    auto area2 = [&](auto&& self,P a,P b,C c)->R{
        P va = a-c.p,vb = b-c.p;
        R at = cross(va,vb)*0.5;
        R theta = get_signed_angle(va,P(0,0),vb);
        if(equal0(at)) return 0;
        if(in_circle(c,a) && in_circle(c,b)) return at;
        if(dist(S(a,b),c.p)>c.r-eps) return c.r*c.r*theta*0.5;
        auto u = crosspoint(c,S(a,b));
        R res = 0;
        vec<P> divide = {a,u.first,u.second,b};
        for(int i=0;i+1<divide.size();i++) res += self(self,divide[i],divide[i+1],c);
        return res;
    };
    R res = 0;
    for(int i=0;i<n;i++){
        res += area2(area2,v[i],v[(i+1)%n],c);
    }
    return res;
}

int main(){
    int N;
    R r;
    cin >> N >> r;
    Polygon A(N);
    for(int i=0;i<N;i++) cin >> A[i];
    C c(P(0.0,0.0),r);
    cout << fixed << setprecision(10) << area(A,c) << endl;
}