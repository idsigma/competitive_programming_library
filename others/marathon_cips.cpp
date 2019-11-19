#include <iostream>
#include <random>
#include <chrono>
#include <cassert>
#include <vector>
#include <stdio.h>

int main(){
	mt19937 mt{random_device{}()};
	uniform_int_distribution<int> xrd(1,M-2),yrd(1,M-2),mark(3,5),an(0,1000);
	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();
	auto dur = end-start;
	auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
	random_device seed_gen;
 	mt19937 engine(seed_gen());
 	shuffle(now.begin(),now.end(),engine);
}