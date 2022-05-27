#include "myHeader.h"

#ifdef UBUNTU
#include <unistd.h>   //_getch
    #include <termios.h>  //_getch	

char getch(){

    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
       perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;

 }

#endif


int viewEventInfo(int skipper,char id[])
{
    FILE *info;
    info=fopen("EventInfo.txt","r");
	char ch;
  
    system("clear");
    printf("\t\t************EVENT INFORMATION***********\n");
    while(!feof(info))
    {
        fscanf(info,"%c",&ch);
        printf("%c",ch);
    }
    printf("\b ");
    fclose(info);
	
    printf("\n\n\tPress Any Key ....");
	char c=getchar();
	
    if(skipper==1)
        OldUserMenu(id);
	if(skipper ==2)
		adminMenu(1);
	else
		userMenu();
    
    return 0;

}

int authenticate(int caser,char pass[])

{
	int passer=0,count=4;
	char userpass[13];
    switch(caser)
    {
     case 1: // this is admin 
		enterPass(userpass);
		passer=strcmp(pass,userpass);
		while(passer!=0&&count>=0)
		{
			system("clear");
			printf("\n\tWrong Password\n\tEnter again:");
			enterPass(userpass);
			passer=strcmp(pass,userpass);
			count--;
		}
		if(passer==0)
			return 1;
		else if(passer!=0||count==0)
			return 0;
		else
			return 1;
		break;
    case 2: // this is user
		printf("\n\tEnter User Password");
		enterPass(userpass);
		passer=strcmp(pass,userpass);
		while(passer!=0&&count>=0)
		{
			system("clear");
			printf("\n\tWrong Password\n\tEnter again:");
			enterPass(userpass);
			passer=strcmp(pass,userpass);
			count--;
		}
		if(passer==0)
			return 1;
		else if(passer!=0||count==0)
			return 0;
		else
			return 1;
    }
}

int checkEventName(char event[])
{
    FILE *ev;
    ev=fopen("EventList.txt","r");
    char check[30];
    while(!feof(ev))
    {
        fscanf(ev,"%s",check);
        if(strcmp(check,event)==0)
            return 0;
    }
    return 1;
}


int checkPassword(char pass[])
{
    int special=0,up=0,low=0,no=0;
    int i;
    for(i=0;i<strlen(pass);i++)
    {
        if(pass[i]=='@'||pass[i]=='_'||pass[i]=='#'||pass[i]=='$'||pass[i]=='%'||pass[i]=='^'||pass[i]=='&'||pass[i]=='*')
            special++;
        else if(pass[i]>=65&&pass[i]<=90)
            up++;
        else if(pass[i]>=97&&pass[i]<=122)
            low++;
        else if(pass[i]>=48&&pass[i]<=57)
            no++;
    }
    if(special>0&&up>0&&low>0&&no>0&&strlen(pass)>=8)
        return 1;
    else
        return 0;
}

int enterPass(char pass[])
{
	char ch;
	int i=0,j;
	printf("Enter password : ");
	while (1)
	{
		if (i < 0) {
			i = 0;
		}
	  ch = getch();

		if (ch ==0){
		 fflush(stdin);
		 break;
	    }
	  if (ch == 8)
	  {
		 printf("\b\b");
		 i--;
		 system("clear");
		 puts("Enter password :");
		 for(j=0;j<i;j++)
		 printf("*");
		 continue;
	  }
	  pass[i] = ch;
	  i++;
	  ch = '*';
	  printf("%c",ch);
	}
	pass[i] = '\0';
	return 0;
}
int encrypt(char pass[])
{
    int i;
    for(i=0;i<strlen(pass);i++)
            pass[i]=pass[i]+10;
	return 0;
}
int decrypt(char pass[])
{
    int i;
    for(i=0;i<strlen(pass);i++)
            pass[i]-=10;
	return 0;
}


