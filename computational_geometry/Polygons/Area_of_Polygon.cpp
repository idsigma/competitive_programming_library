#include <iostream>
#include <stdio.h>
#include <complex>
using namespace std;
typedef complex<double> xy_t;

xy_t P[110];

double dot_product(xy_t a, xy_t b){
	return (conj(a)*b).real();
}

int main(){
		int N = 0;
		double x,y;
		while(scanf("%lf, %lf", &x, &y) != EOF){
			P[N++] = xy_t(x,y);
		}
		double sum = 0.0;
		for(int i=0;i+2<N;i++){
			xy_t a = P[0], b = P[i+1], c = P[i+2];
			sum += 0.5*dot_product(b,c);
		}
		printf("%.6f\n", abs(sum));
}