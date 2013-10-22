#include "gcd.h"

//Euclid's GCD Algorithm pulled from wikipedia. Recursive implementation
int findGCD(int x, int y){
	if (y == 0){
		return x;
	}
	else{
		return findGCD(y, x % y);
	}
}
