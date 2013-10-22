#include <stdio.h>
#include <stdbool.h>

int main()
{
    int x; //input is stored here
    int xTemp; 	//Modifies x but perhaps doesn't matter due to how c is implemented?
    int binaryX[32] = {};
    int i;
    bool done = 0; 

   // printf("Please enter a signed decimal integer: ");
  scanf("%d", &x);

//Attempt to work with a positive number. Will negate later if necessary
    if(x >= 0){
        xTemp = x;
    }
    else{
        xTemp = -x;
    }
 //Algorithm for converting from base 10 to base 2
    for(i = 31; i >= 0; i--){
	if(xTemp == 0){
		binaryX[i] = 0;
	}
	else{
                if(xTemp % 2 == 0 && xTemp != 1){
                        binaryX[i] = 0;
                        xTemp = xTemp / 2;
                }
                else{
                        binaryX[i] = 1;
                        xTemp = (xTemp - 1) / 2;
                }
        }
     }

//Convert to two's complement. Input string XORed with a string of all 1s to negate
     if(x < 0){
	for(i = 0; i < 32; i++){
		binaryX[i] = binaryX[i] ^ 1;
	}
     
     	for(i = 31; i >= 0 && !done; i--){
		if(binaryX[i] == 1){
			binaryX[i] = 0;
		}		
		else{
			binaryX[i] = 1;
			done = 1;
		}
     	}
     }

    printf("signed dec:   %d\n", x);
    printf("unsigned dec: %u\n", x);
    printf("hex:          %x\n", x);
    printf("binary:       ");
//for spacing
    for(i = 0; i <= 31; i++){
	if((i % 4) == 0 && i != 0){
		printf(" ");
	}
        printf("%d", binaryX[i]);
	}
    printf("\n");

    return 0;
}
