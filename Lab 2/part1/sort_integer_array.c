#include "sort_integer_array.h"
#include "compareAsc.h"
#include "compareDesc.h"

void sort_integer_array(int *begin, int *end, int ascending){
    int diff = 0;
    while(end != begin){
	end--;
	diff++;
    }
    
    if(ascending == 1){//ascending
	qsort(begin, diff, sizeof(int), compareAsc);
    }
    else{
	qsort(begin, diff, sizeof(int), compareDesc);
    }
}
 

