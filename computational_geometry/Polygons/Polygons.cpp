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

using Polygon = vec<P>;

R area_of_polygon(Polygon& v){
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

int main(){
    int N;
    cin >> N;
    Polygon v(N);
    for(int i=0;i<N;i++){
        cin >> v[i];
    }
    int Q;
    cin >> Q;
    for(int i=0;i<Q;i++){
        P p0,p1;
        cin >> p0 >> p1;
        L l = L(p0,p1);
        Polygon cut = convex_cut(v,l);
        cout << fixed << setprecision(10) << area_of_polygon(cut) << endl;
    }
}