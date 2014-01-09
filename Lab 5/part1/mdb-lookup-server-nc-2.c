#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

static void die(const char *s){
    perror(s);
    exit(1);
}

int main(){
    char portNumber[100];
    int intPortNumber;
start:
	printf("port number: ");
    	fgets(portNumber, sizeof(portNumber), stdin);
	intPortNumber = atoi(portNumber);

	if(portNumber[0] == '\n'){
		goto getUpdate;	
	}	

	if(intPortNumber > 65535 || intPortNumber < 1024){
	    die("Invalid port range");
	}

    	pid_t pid = fork();
    	if(pid < 0){
		die("fork failed");
   	 }		
    	else if (pid == 0){
		//child process
		fprintf(stderr, "[pid = %d] ", (int)getpid());
		fprintf(stderr, "mdb-lookup-server started on port %s\n", portNumber);
		execl("./mdb-lookup-server-nc.sh", "mdb-lookup-server-nc.sh", portNumber, (char *)0);
		die("execl failed");
    	}
    	else{
		//parent process
		    sleep(1);
getUpdate:
		    pid = waitpid((pid_t) -1, NULL, WNOHANG);
		    while(pid != 0){
			fprintf(stderr, "[pid = %d] ", (int)pid);
			fprintf(stderr, "mdb-lookup-server terminated\n");
			pid = waitpid((pid_t) -1, NULL, WNOHANG);
		    }
		   goto start;
    	}
    return 0;
}
