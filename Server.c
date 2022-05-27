
#include "myHeader.h"

#define	MAXLINE	 100
#define LISTENQ  1000

int ids[2][20] ;
static int count;
int chld,prnt;

void quitHandler(){
	int status;
	if(getpid() == prnt)
		printf("Killing all the clients....\n");
	sleep(2);
	for(int i=0;i<count;i++){
		if(ids[1][i]){
			kill(ids[0][i] , SIGUSR1);
		}
	}
	if(getpid() == prnt){
		wait(&status);
		printf("\n\n All killed..");
	}
	kill( -prnt , SIGKILL);
	exit(0);
}

void* clientFunction(void *sck){
	int connfd = *(int*)sck;
	char buf[100];
	//printf("New User Connected \n");
	read(connfd , buf,MAXLINE);
	ids[0][count]= atoi(buf);
	ids[1][count]=1;
	count++;
	
	read(connfd , buf,MAXLINE);
	int temp = atoi(buf);
	for(int i=0;i<count;i++)
	{
		if(ids[0][i] == temp)
			ids[1][i]=0;
	}
	pthread_exit(NULL);
}

int open_listenfd(char *port) 
{
    struct addrinfo hints, *listp, *p;
    int listenfd, optval=1;
	char host[MAXLINE],service[MAXLINE];
    int flags;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;             
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; 
    hints.ai_flags |= AI_NUMERICSERV;            
    getaddrinfo(NULL, port, &hints, &listp);

    /* Walk the list for one that we can bind to */
    for (p = listp; p; p = p->ai_next) {
        /* Create a socket descriptor */
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue;  /* Socket failed, try the next */

        /* Eliminates "Address already in use" error from bind */
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,    //line:netp:csapp:setsockopt
                   (const void *)&optval , sizeof(int));

		flags = NI_NUMERICHOST | NI_NUMERICSERV; /* Display address string instead of domain name and port number instead of service name */
		getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
		sleep(2);
        printf("Server Started at : host:%s, service:%s\n", host, service);
		
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break; 
        close(listenfd);
    }

    freeaddrinfo(listp);
    if (!p) 
        return -1;

    if (listen(listenfd, LISTENQ) < 0) {
        close(listenfd);
	return -1;
    }
	
    return listenfd;
}


int main(int argc, char **argv)
{
	if (argc!=2) {
		printf ("Program parameters: <Port number>");
		exit(1);
    }
    int listenfd, connfd;
    socklen_t clientlen;
	pthread_t thread_id;
    struct sockaddr_storage clientaddr; 
    char client_hostname[MAXLINE], client_port[MAXLINE];
	printf("\nStarting Server.....\n");
    listenfd = open_listenfd(argv[1]);
	clientlen = sizeof(struct sockaddr_storage); 

	signal(SIGINT , quitHandler); //handling signal

	printf("\n\tPress Any Key ...");
	flushChar=getchar();
	system("clear");
	
	if((chld=fork() )== 0){
		while(1) 
		{
			FILE *fp = fopen("log.txt","a");
			time_t t; 
			time(&t);
			char *ts=ctime(&t);
			ts[strlen(ts)-1]='\0'; //removing \n

			connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
			getnameinfo((struct sockaddr *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
			fprintf(fp ,"%s - Connected to (%s, %s)\n",ts, client_hostname, client_port);
			
			if( pthread_create( &thread_id , NULL , clientFunction , (void*) &connfd) < 0)
			{
			  perror("Failed to create a thread");
			  return 1;
			}
			fclose(fp);
		}
	}
    else{
		char in[20];
		prnt=getpid();
		do{
			printf("Type admin to open Admin Panel...\n");
			scanf("%s",in);
			if(strcmp(in,"admin") == 0)
				adminMenu(0);
		}while(1);
	}
    exit(0);
}

