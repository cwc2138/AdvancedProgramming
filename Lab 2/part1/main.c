#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort_integer_array.h"

int main(){
    int sizeOfArray;
    int *random_array;
    int *ascending_array;
    int *descending_array;
    int i; //used as counter

    srandom(time(NULL));
    printf("Please input a positive number: \n");
    scanf("%d", &sizeOfArray);
    random_array = (int*)malloc(sizeof(int) * sizeOfArray);
    if(random_array == NULL){
	perror("malloc returned NULL");
	exit(1);
    }

    printf("Random Array: ");
    for(i = 0; i < sizeOfArray; i++){
	*random_array = random() % 100;
	if(i < sizeOfArray - 1){
	    printf("%d, ", *random_array);
	}
	else{
	    printf("%d\n", *random_array);
	}
	random_array++;
    }

    random_array--; //points to last element of random
    ascending_array = (int*)malloc(sizeof(int) * sizeOfArray);
    if(ascending_array == NULL){
	perror("malloc returned NULL");
	exit(1);
    }

    for(i = 0; i < sizeOfArray; i++){
	*ascending_array = *random_array;
	random_array--;
	ascending_array++;
    }

    random_array++; //points to first element of random_array
    descending_array = (int*)malloc(sizeof(int) * sizeOfArray);
    if(descending_array == NULL){
	perror("malloc returned NULL");
	exit(1);
    }

    for(i = 0; i < sizeOfArray; i++) {
	*descending_array = *random_array;
	random_array++;
	descending_array++;
    }

    random_array = random_array - sizeOfArray; //points to head of random_array
	
    ascending_array = ascending_array - sizeOfArray; //points to head of ascending_array
    sort_integer_array(ascending_array, ascending_array + sizeOfArray, 1);
      //PRINTING ASSUMES ASCENDING ARRAY POINTS TO HEAD
      printf("Ascending Array: ");
      for(i = 0; i < sizeOfArray; i++){
	  if(i < sizeOfArray - 1){
	      printf("%d, ", ascending_array[i]);
	  }
	  else{
	      printf("%d\n", ascending_array[i]);
	  }
      }

    descending_array = descending_array - sizeOfArray; //points to head of descending_array
    sort_integer_array(descending_array, descending_array + sizeOfArray, 0);
    //PRINTING ASSUMES DESCENDING ARRAY POINTS TO HEAD
    printf("Descending Array: ");
    for(i = 0; i < sizeOfArray; i++){
	if(i < sizeOfArray - 1){
	    printf("%d, ", descending_array[i]);
	}
	else{
	    printf("%d\n", descending_array[i]);
	}
    }

    free(random_array);
    free(ascending_array);
    free(descending_array);

    return 0;
}
