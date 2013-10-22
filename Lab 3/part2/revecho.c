#include <stdio.h>
#include "mylist.h"
#include <string.h>

static void printChar(void *p){
    printf("%s\n", (char *)p);
}

int main(int argc, char** argv){
    int i;
    char *dudeData = "dude";

    struct List list;
    initList(&list);

    char** argvCopy = argv;
    argvCopy++; //1st element of array is name of program so skip

    for(i = 1; i < argc; i++){
       addFront(&list, *argvCopy);//addFront automatically reverses input
       argvCopy++;
    }

    traverseList(&list, &printChar);


    if(findNode(&list, dudeData, (const void *) strcmp)){
	    printf("\ndude found\n");
    }
    else{
	printf("\ndude not found\n");
    }
 
    removeAllNodes(&list);

    return 0;
}
