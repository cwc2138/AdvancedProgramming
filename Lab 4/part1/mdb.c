#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //use for Macro
#include "mdb.h"
#include "mylist.h"

int counter = 0;
char parseUserInput[6] = "";

static void findAndPrint(void *p){
    if(strstr(((struct MdbRec *)p)->name, parseUserInput) != NULL ||  strstr(((struct MdbRec *)p)->msg, parseUserInput) != NULL){
	    printf("%d: {%s} said ", counter, ((struct MdbRec *)p)->name );
	    printf("{%s}\n", ((struct MdbRec *)p)->msg);
	    }
    else{
	counter++;
    }
}

static void printAll(void *p){
    printf("%d: {%s} said ", counter, ((struct MdbRec *)p)->name);
    printf("{%s}\n", ((struct MdbRec *)p)->msg);
    counter++;
}

static void freeMdbp(void *p){
   free((struct MdbRec *)p);
} 

int main(int argc, char** argv){
    char *fileName = *(argv+1);
    struct List list;
    initList(&list);
    struct Node *node = NULL;
    char mdbBuffer[100] = "";
    char userInput[1000] = "";
    FILE *fp = fopen(fileName, "r");
    struct MdbRec *mdBp;

    if(argc > 2){
	printf("usage: mdb-lookup <database_file>\n");
	exit(1);
    }

    if(access(fileName, F_OK) == -1){//F_OK is a macro
	printf("%s: No such file or directory\n", fileName);
	exit(1);
    }

    while(fread(mdbBuffer, 1, 40, fp) == 40){
	mdBp = malloc(sizeof(struct MdbRec));
	if(mdBp == NULL){
	    perror("malloc returned NULL");
	    exit(1);
	}
	memcpy(mdBp->name, mdbBuffer, 16);
	memcpy(mdBp->msg, mdbBuffer + 16, 24);
	node = addAfter(&list, node, mdBp);
    }

    fclose(fp);

    printf("lookup: ");

    while(fgets(userInput, sizeof(userInput), stdin)){
	
	if(userInput[0] == '\n') {
	    counter = 1;
	    traverseList(&list, &printAll);
       	}
	else{
	    counter = 1;
	    if(strlen(userInput) > 5){
		 memcpy(parseUserInput, userInput, 5);
		 parseUserInput[5] = '\0';
		 traverseList(&list, &findAndPrint);
		 }
	    else{
		strcpy(parseUserInput, userInput);
		parseUserInput[strlen(userInput) - 1] = '\0';
		traverseList(&list, &findAndPrint);
	    }
	}
	printf("\nlookup: ");
    }

    traverseList(&list, &freeMdbp);
    removeAllNodes(&list);

    return 0;
}
   
