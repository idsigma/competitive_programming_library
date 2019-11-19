#include <iostream>
using namespace std;

int c1x,c1y,c1r,c2x,c2y,c2r;

int main(){
    cin >> c1x >> c1y >> c1r;
    cin >> c2x >> c2y >> c2r;
    int dx = c1x-c2x,dy = c1y-c2y;
    int d1r = c1r*c1r+2*c1r*c2r+c2r*c2r;
    int d2r = c1r*c1r-2*c1r*c2r+c2r*c2r;
    if(d1r<dx*dx+dy*dy) cout << 4 << endl;
    else if(d1r==dx*dx+dy*dy) cout << 3 << endl;
    else if(d2r<dx*dx+dy*dy && dx*dx+dy*dy<d1r) cout << 2 << endl;
    else if(d2r==dx*dx+dy*dy) cout << 1 << endl;
    else cout << 0 << endl;
}