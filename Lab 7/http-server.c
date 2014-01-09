#include<stdio.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <signal.h>
#include <netdb.h>

#define BUF_SIZE 4096

const char *OK_HEADER = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\n"; 
const char *NOT_IMPLEMENTED_HEADER = "HTTP/1.0 501 Not Implemented\r\n\n<html><body><h1>501 Not Implemented</h1></body></html>";
const char *BAD_REQUEST_HEADER = "HTTP/1.0 400 Bad Request\r\n\n<html><html><body><h1>400 Bad Request</h1></body></html>";
const char *NOT_FOUND_HEADER = "HTTP/1.0 404 Not Found\r\n\n<html><html><body><h1>404 Not Found</h1></body></html>";

const char *form = 
	"<h1>mdb-lookup</h1>\n"
	"<p>\n"
	"<form method=GET action=/mdb-lookup>\n"
	"lookup: <input type=text name=key>\n"
	"<input type=submit>\n"
	"</form>\n"
	"<p>\n";
	
 static void die(const char *msg) {
     perror(msg);
     exit(1);
 }

int parseCheck(int clntSock, char *method, char *requestURI, char *httpVersion, char *statusCode, char *reasonPhrase){
    if(method == 0 || requestURI == 0 || httpVersion == 0){
	if(send(clntSock, BAD_REQUEST_HEADER, strlen(BAD_REQUEST_HEADER), 0) != strlen(BAD_REQUEST_HEADER)){
	    die("send failed");
	}

	snprintf(statusCode, sizeof("400"), "%s", "400");
	snprintf(reasonPhrase, sizeof("Bad Request"), "%s", "Bad Request");

	return 0;
    }
    else if((strcmp(method, "GET") != 0) || ((strcmp(httpVersion, "HTTP/1.0") != 0 && strcmp(httpVersion, "HTTP/1.1") != 0 ))){
	if(send(clntSock, NOT_IMPLEMENTED_HEADER, strlen(NOT_IMPLEMENTED_HEADER), 0) != strlen(NOT_IMPLEMENTED_HEADER)){
	    die("send failed");
	}

	snprintf(statusCode, sizeof("501"), "%s", "501");
	snprintf(reasonPhrase, sizeof("Not Implemented"), "%s", "Not Implemented");

	return 0;
    }
    else if(requestURI[0] != '/'){
	if(send(clntSock, BAD_REQUEST_HEADER, strlen(BAD_REQUEST_HEADER), 0) != strlen(BAD_REQUEST_HEADER)){
	    die("send failed");
	}

	snprintf(statusCode, sizeof("400"), "%s", "400");
	snprintf(reasonPhrase, sizeof("Bad Request"), "%s", "Bad Request");

	return 0;
    }
    return 1;
}

void appendHTML(char *servedFilePath){
    char newfilePath[1000];
    char *slash;

    slash = strrchr(servedFilePath, '/');
    if(*slash == '/' && *(slash + 1) == 0){
	snprintf(newfilePath, sizeof(newfilePath), "%s%s", servedFilePath, "index.html");
	strncpy(servedFilePath, newfilePath, sizeof(newfilePath));
    }
}

int fileExists(int clntSock, FILE * fdServedFile, char *statusCode, char *reasonPhrase){
    if(fdServedFile == 0){
	if(send(clntSock, NOT_FOUND_HEADER, strlen(NOT_FOUND_HEADER), 0) != strlen(NOT_FOUND_HEADER)){
	    die("send failed");
	}

	snprintf(statusCode, sizeof("404"), "%s", "404");
	snprintf(reasonPhrase, sizeof("Not found"), "%s", "Not found");

	return 0;
    }
    return 1;
}

void goLookup(char *requestURI, char *lookupBuf){
    char *lookupPointer = strrchr(requestURI, '=') + 1; //gets rid of equal sign
    strncpy(lookupBuf, lookupPointer, strlen(lookupPointer));
    *(lookupBuf + strlen(lookupBuf)) = '\0';
}

int main(int argc, char **argv)
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR){
	die("signal() failed");
    }
    if(argc != 5){
	fprintf(stderr, "Usage: %s <Server Port> <Web Root> <mdb-lookup-host> <mdb-lookup-port>\n", argv[0]);
    }

    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort;     /* Server port */
    char *web_root;
    char buffer[BUF_SIZE];

    echoServPort = atoi(argv[1]);
    web_root = argv[2];

    if((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
	die("socket() failed");
    }
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */
   
    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0){
       	die("bind() failed");
    }

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, 5) < 0){
       	die("listen() failed");
    }

    int mdbServSock;
    struct sockaddr_in mdbServAddr;
    unsigned short mdbServPort;
    char *mdbServIP;
    char *mdbServHost;
    struct hostent *mdbHost;

    mdbServHost = argv[3];
    mdbServPort = atoi(argv[4]);

    if((mdbServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
	die("socket() failed");
    }

    if((mdbHost = gethostbyname(mdbServHost)) == NULL){
	die("gethostbyname failed");
    }

    memset(&mdbServAddr, 0, sizeof(mdbServAddr));
    mdbServAddr.sin_family = AF_INET;
    mdbServIP = inet_ntoa(*(struct in_addr *)mdbHost->h_addr);
    inet_pton(AF_INET, mdbServIP, &mdbServAddr.sin_addr);
    mdbServAddr.sin_port = htons(mdbServPort);

    if(connect(mdbServSock, (struct sockaddr *) &mdbServAddr, sizeof(mdbServAddr)) < 0){
	die("connect() failed");
    }

    char requestBuffer[1000];
    char servedFilePath[1000];
    char statusCode[10];
    char reasonPhrase[10];
    char msg[1000];
    FILE *fdclntSock;
    FILE *fdservedFile;
    FILE *fdmdblookup;
    char *token_seperators;
    char *method;
    char *requestURI;
    char *httpVersion;

    char *clientIP;
    unsigned int clntLen;

    fdmdblookup = fdopen(mdbServSock, "r");

    for(;;){
	clntLen = sizeof(echoClntAddr);

	if((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0){
	    die("accept() failed");
	}

	clientIP = inet_ntoa(echoClntAddr.sin_addr);

	if((fdclntSock = fdopen(clntSock, "r")) == 0){
	    die("fdopen failed");
	}

	if(fgets(requestBuffer, sizeof(requestBuffer), fdclntSock) == 0){
	    if(ferror(fdclntSock)){
		die("IO error");
	    }
	    else{
		fprintf(stderr, "Request not sent\n");
		close(clntSock);
	    }
	}

	while((requestBuffer[strlen(requestBuffer) - 1]) == '\n' || requestBuffer[strlen(requestBuffer) - 1] == '\r'){
	    requestBuffer[strlen(requestBuffer) - 1] = '\0';
	}

	char requestBufferCopy[1000];
	strncpy(requestBufferCopy, requestBuffer, strlen(requestBuffer));
	requestBufferCopy[strlen(requestBuffer)] = '\0';
	token_seperators = "\t \r\n";
	method = strtok(requestBuffer, token_seperators);
	requestURI = strtok(NULL, token_seperators);
	httpVersion = strtok(NULL, token_seperators);

	if(parseCheck(clntSock, method, requestURI, httpVersion, statusCode, reasonPhrase)){
	    if(strncmp(requestURI, "/mdb-lookup", 11 ) != 0){
		snprintf(servedFilePath, sizeof(servedFilePath), "%s%s", web_root, requestURI);
		appendHTML(servedFilePath);
		fdservedFile = fopen(servedFilePath, "r");

		if(fileExists(clntSock, fdservedFile, statusCode, reasonPhrase)){
		    if(send(clntSock, OK_HEADER, strlen(OK_HEADER), 0) != strlen(OK_HEADER)){
			    die("send failed");
		    }

		    int bytesRead;

		    while((bytesRead = fread(buffer, 1, sizeof(buffer), fdservedFile)) > 0){
			send(clntSock, buffer, bytesRead, 0);
		    }
		    
		    snprintf(statusCode, sizeof("200"), "%s", "200");
		    snprintf(reasonPhrase, sizeof("OK"), "%s", "OK");
		}
		if(fdservedFile != 0){
		    fclose(fdservedFile);
		}
	    }
	    else if(strncmp(requestURI, "/mdb-lookup", 11) == 0){
		char tableBuffer[1000];
		char lookupBuffer[1000];

		char *table1 = "<table border = 1>";
		char *table2 = "<tr style = 'background:#3300FF;'><td>";
		char *table3 = "<tr style = background:#00FF66;'><td>";
		char *table4 = "</td></tr>";

		send(clntSock, OK_HEADER, strlen(OK_HEADER), 0);
		send(clntSock, form, strlen(form), 0);
		send(clntSock, table1, strlen(table1), 0);
		memset(lookupBuffer, '\0', sizeof(lookupBuffer));

		if(strncmp(requestURI, "/mdb-lookup?key=", 16) == 0){
		    goLookup(requestURI, lookupBuffer);
		    send(mdbServSock, lookupBuffer, strlen(lookupBuffer), 0);
		    send(mdbServSock, "\n", strlen("\n"), 0); //new line for end of query
		    fgets(buffer, BUF_SIZE, fdmdblookup);

		    int flag = 0;
		    while(strcmp(buffer, "\n") != 0){
			if(flag == 0){
			    snprintf(tableBuffer, sizeof(tableBuffer), "%s%s%s", table2, buffer, table4);
			}
			else{
			    snprintf(tableBuffer, sizeof(tableBuffer), "%s%s%s", table3, buffer, table4);
			}
			send(clntSock, tableBuffer, strlen(tableBuffer), 0);
			fgets(buffer, BUF_SIZE, fdmdblookup);
			flag = (flag + 1)%2;
		    }
		    snprintf(msg, sizeof(msg), "Looking up [%s]: ", lookupBuffer);
		}
		send(clntSock, "</table>", strlen("</table>"), 0);
		snprintf(statusCode, sizeof("200"), "%s", "200");
		snprintf(reasonPhrase, sizeof("OK"), "%s", "OK");
	    }
	}
	printf("%s \"%s\" %s %s\n", clientIP, requestBufferCopy, statusCode, reasonPhrase);
	memset(msg, '\0', sizeof(msg));
	fclose(fdclntSock);
    }

    return 0;
}
