#include <stdio.h>
#include "prime.h"
#include "gcd.h"
#include <stdbool.h>

int main()
{
	int x;
	int y;
	double avg;	
	bool xPrime;
	bool yPrime;
	int gcd;
	
	printf("Please type in two positive integers seperated by a comma. For example, \"2, 3\"\n");
	scanf("%d, %d", &x, &y);
	
//cast ints to double so integer division doesn't occur. Don't want to truncate
	avg =(double)(x + y) / 2;
	printf("The average is: %f\n", avg);
	
	xPrime = isPrime(x);
	yPrime = isPrime(y);

	gcd = findGCD(x, y);		

	if(xPrime == 1){
		printf("%d is prime\n", x);
	}
	else{
		printf("%d is not prime\n", x);
	}

	if(yPrime == 1){
		printf("%d is prime\n", y);
	}
	else{
		printf("%d is not prime\n", y);
	}
	if(gcd == 1){
		printf("%d and %d are relatively prime\n", x, y);
	}
	else{
		printf("%d and %d are not relatively prime. Their gcd is %d\n", 		x, y, gcd);
	}
	return 0;		
}
