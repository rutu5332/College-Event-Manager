#include "myHeader.h"
#define	MAXLINE	 6000  /* Max text line length */

int clientfd;

void quitHandler()
{
	char buf[10];
	sprintf(buf , "%d" , getpid());
	write(clientfd , buf,strlen(buf)); 
	printf("\n\n\t\tThank you .... !!!\n\n\n");
	sleep(3);
	system("clear");
	signal(SIGINT , SIG_DFL);
	kill(getpid() , SIGINT);
}

void killHandler() //handling signal sent by server
{
	printf("\n\n\tSORRY :: Error occured at server side....\n");
	sleep(2);
	printf("\n\n\tServer is not Running ... \n");
	sleep(3);
	system("clear");
	signal(SIGINT , SIG_DFL);
	kill(getpid() , SIGINT);
}

int open_clientfd(char *hostname, char *port) {
    int clientfd;
    struct addrinfo hints, *listp, *p;
	char host[MAXLINE],service[MAXLINE];
    int flags;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;  
    hints.ai_flags = AI_NUMERICSERV; 
    hints.ai_flags |= AI_ADDRCONFIG; 
    getaddrinfo(hostname, port, &hints, &listp);
  
    for (p = listp; p; p = p->ai_next) {
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue; 

		flags = NI_NUMERICHOST | NI_NUMERICSERV; 		
		getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
        printf("host:%s, service:%s\n", host, service);
		
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) 
		{
			printf("Connected to server %s at port %s\n", host, service);
            break; 
		}
        close(clientfd);
    } 

    freeaddrinfo(listp);
    if (!p) 
        return -1;
    else    
        return clientfd;
}




int main(int argc, char **argv)
{
    int pid;
	char spid[10];
    char *host, *port, buf[MAXLINE];
	if (argc!=3) {
		printf ("Program parameters: <host> <Port number>");
		exit(1);
    }

    //setting signals
	signal(SIGINT , quitHandler); 
	signal(SIGUSR1 , killHandler);

	//getting host and port number
    host = argv[1];
    port = argv[2];
    clientfd = open_clientfd(host, port);

	if(clientfd == -1){
		printf("Server is not Running....\n");
		exit(0);
	}
	pid = getpid();
	sprintf(spid , "%d" , pid);
	write(clientfd , spid , strlen(spid));
	printf("Process Id : %d \n\n" ,pid);
	sleep(2);
	userMenu(); 
    exit(0);
}
