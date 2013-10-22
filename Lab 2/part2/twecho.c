/*
 * twecho
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char **duplicateArgs(int argc, char **argv)
{
    char **duplicateArray =  malloc((sizeof(char*) * (argc + 1))); //+1 for null terminated array
    int i;
    int *length = (int *) malloc(sizeof(int) * argc);
    int lengthOfWord;

    if(duplicateArray == NULL){
	perror("malloc returned NULL");
	exit(1);
    }

    if(length == NULL){
	perror("malloc returned NULL");
	exit(1);
    }

    for(i = 0; i < argc; i++){
	lengthOfWord = 0;
	while(**argv){
	    lengthOfWord++;
	    (*argv)++;
	}
	*length = lengthOfWord;
	*argv -= lengthOfWord; //reset to head
	length++;
	argv++;
    }

    length -= argc; //reset to head
    argv -= argc; //reset to head

    for(i = 0; i < argc; i++){
	*duplicateArray = (char *) malloc(((*length) + 1) * sizeof(char));//+1 for null termination
	if(duplicateArray == NULL){
	    perror("malloc returned NULL");
	    exit(1);
	}
	length++;
	duplicateArray++;
    }

    length -= argc;
    duplicateArray -= argc;

    for(i = 0; i < argc; i++){
	while(**argv){
	    **duplicateArray = toupper(**argv);
	    (*duplicateArray)++;
	    (*argv)++;
	}
	**duplicateArray = '\0';
	*argv -= *length;
	*duplicateArray -= ((*length));
	length++;
	duplicateArray++;
	argv++;
    }

    length -= argc;
    duplicateArray -= argc;
    argv -= argc;

    *(duplicateArray + argc) = NULL;
    free(length);

return duplicateArray;    
}

static void freeDuplicatedArgs(char **copy)
{
   int length = 0;
   
   while(*(copy)){
       free(*copy);
       copy++;
       length++;
   }
   free(*copy);
   
   copy -= length;
   free(copy);
}

/*
 * DO NOT MODIFY main().
 */
int main(int argc, char **argv)
{
    if (argc <= 1)
        return 1;

    char **copy = duplicateArgs(argc, argv);
    char **p = copy;

    argv++;
    p++;
    while (*argv) {
        printf("%s %s\n", *argv++, *p++);
    }

    freeDuplicatedArgs(copy);

    return 0;
}
