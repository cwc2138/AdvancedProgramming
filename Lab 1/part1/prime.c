#include "prime.h"
#include <math.h>
#include <stdbool.h>

bool isPrime(int x)
{
	double upperBound = sqrt(x); //slight optimization by not testing all values
	int i;

	if(x == 1){
		return 1; 
	}
	else{
		for(i = 1; i <= upperBound; i++){
			if(x % i == 0 && i != 1){
				return 0;
			}
		}
	return 1;
	}
}
