#include "myHeader.h"
char flushChar;

void display(){
	printf("\n\n===========================================================================\n");
	printf("    _______                        _______    ______   _______  ________ \n");
	printf("    |        \\      /  |\\      |  |       |  |      |  |        |        \n");
	printf("    |         \\    /   | \\     |  |       |  |      |  |        |        \n");
	printf("    |          \\  /    |  \\    |  |       |  |     /   |        |        \n");
	printf("    ------|     \\/     |   \\   |  |-------|  |____/    ------|  |-----   \n");
	printf("          |     /      |    \\  |  |       |  |               |  |        \n");
	printf("          |    /       |     \\ |  |       |  |               |  |        \n");
	printf("    ______|   /        |      \\|  |       |  |         ______|  |_______ \n");
	printf("\n\n===========================================================================\n\n");
}

void changeUserPass(char user[])
{
	FILE *password;
	char pass[15],usr[15];
	system("clear");
    password=fopen("UserDetails.txt","r+");
	while(!feof(password))
	{
		fscanf(password,"%s",usr);
		fscanf(password ,"%s",pass);
		if(strcmp(user,usr)==0)
			break;
	}
    up:
    printf(" ");
    char checkpass[13];
    printf("\tEnter Your Old Password:");
	scanf("%[^\n\t]s",checkpass);
	scanf("%c",&flushChar);
    //scanf("%s",checkpass);
    if(strcmp(checkpass,pass)!=0)
    {
        printf("WRONG PASSWORD!! ENTER AGAIN:\n\t");
        goto up;
    }
    system("clear");
	fseek(password,-strlen(pass), SEEK_CUR);
    upper:
    printf("\n\t*************Enter New Password**********\nPassword must contain: an uppercase letter, a lowercase letter a number and \na special character\nEnter:");
    re:
	scanf("%c",&flushChar);
	scanf("%[^\n\t]s",pass);
    //scanf("%s",pass);
    int check=checkPassword(pass);
    if(check!=1)
    {
        printf("\tINVALID PASSWORD\n\tPLEASE ENTER A VALID PASSWORD\n");
        printf("ENTER:");
        goto re;
    }
    printf("\n**VALID PASSWORD**\n");
    printf("\nEnter Password Again:");
    scanf("%c",&flushChar);
	scanf("%[^\n\t]s",checkpass);
	//scanf("%s",checkpass);
    if(strcmp(checkpass,pass)!=0)
    {
        printf("PASSWORDS DO NOT MATCH ENTER NEW AGAIN");
        goto upper;
    }
    //encrypt(pass);
    fprintf(password,"%s",pass);
    fclose(password);
    printf("\n\t\t**********PASSWORD CHANGE SUCCESSFULL**********\n");
    printf("Press Any key....\n\n");
	char c=getchar();
	system("clear");
    OldUserMenu(user);
}

int userMenu()
{
    system("clear");
	display();
    printf("\n\t1.New user\n\t2.Old User\n\t3.Event Information\n\t4.Exit");
    int choice;
    printf("\n\tEnter your choice:");
    scanf("%d",&choice);
	scanf("%c",&flushChar);
    switch(choice)
    {
    case 1:
        system("clear");
        newUser();
        break;
		
    case 2:
        system("clear");
        oldUser();
        break;
    case 3:
        system("clear");
        viewEventInfo(0," ");
        break;
    case 4:
		kill(getpid() , SIGINT);
		exit(0);
	}
return 0;
}

void getUserName(char nm[] , char id[]){
	char chckid[20],last[20],tmp[20];
	FILE *mstr = fopen("MasterList.txt","r");
	while(! feof(mstr)){
		fscanf(mstr,"%s",nm);
		fscanf(mstr,"%s",last);
		fscanf(mstr,"%s",tmp);
		fscanf(mstr,"%s",chckid);
		fscanf(mstr,"%s",tmp);
		if(strcmp(chckid,id) ==0){
			strcat(nm," ");strcat(nm,last);
			fclose(mstr);
			return;
		}
	}
	fclose(mstr);
}

void registerUserEvent(char id[])
{
	system("clear");
    printf("\n\t***********EVENT REGISTRATION*************\n");
    FILE *master;
	char name[20],eventname[10];
	char ch;
    master=fopen("RegisteredEvents.txt","r+");
	
    char checkid[15];
	char events[1000];
    int skipper=0;
    while(!feof(master))
    {
        fscanf(master,"%s",checkid);
        if(strcmp(checkid,id)==0)
        {
            fscanf(master,"%c",&ch);
            fscanf(master,"%s",events);
            skipper=1;
            break;
        }
    }
    if(skipper==0)
		
    {
        printf("Wrong ID! Enter Valid one!");
        return;
    }
	
	getUserName(name,id);
	fseek(master, -strlen(events), SEEK_CUR);
	if(strcmp("none",events) == 0)
		strcpy(events,"");
    
    printf("\n\tEnter which event you want to register :  \n\t");
	viewList(0," ");
	
	reg:
    printf("\n\n*****************WARNING: ENTER THE NAME OF EVENT AS IT IS!**************************\n");
    	
	printf("\n\tEnter the name of event (Same as given in list):");
	
	scanf("%[^\n\t]s",eventname);
	scanf("%c",&flushChar);
	
	if(checkEventName(eventname))
	{
		printf("\n\tEvent Name Not Valid!!\n\tPlease Enter a Valid EVENT name");
		goto reg;
	}
	strcat(events,eventname);
	strcat(events,",");
	strcat(eventname,".txt");
	FILE *eventfile1=fopen(eventname,"a");
	fprintf(eventfile1,"%s\n",name);
	fclose(eventfile1);
	
	printf("\n\n\tDo you wish to register for more events?\n\t1.Yes 2.No\n\t");
	printf("Enter: ");
	int choice;
	scanf("%d",&choice);
	
	if(choice ==1)
		goto reg;
	
    fprintf(master,"%s",events);
    
    printf("\n\t\t******EVENTS SUCCESSFULLY REGISTERED********");
	printf("\n\n\t Press Any Key ....\n\n");
	char c = getchar();
	fclose(master);
    OldUserMenu(id);
}

int OldUserMenu(char id[])
{

    system("clear");
    printf("\t***********LOGGED IN**********");
    printf("\n\n\t1.Register for new Events\n\t2.List of Events Registered\n\t3.Display Event Information\n\t");
    printf("4.View Event List\n\t5.Change password\n\t6.LogOut\n\tEnter:");
    int choice;
    scanf("%d",&choice);
	scanf("%c",&flushChar);
    switch(choice)
    {
    case 1:
        registerUserEvent(id);
        system("clear");
        break;
    case 2:
        viewRegisteredList(id);
        system("clear");
        break;
    case 3:
        viewEventInfo(1,id);
        system("clear");
        break;
    case 4:
        viewList(1,id);
        system("clear");
        break;
    case 5:
        changeUserPass(id);
        break;
    case 6:
        system("clear");
        int i;
        printf("Loading....\n");
        sleep(4);
        userMenu();
    }
    return 0;
}

void Timeout(){
	printf("\n\n Sorry, You haven't Entered Password in given time...\n\n");
	fflush(stdin);
	kill(getpid() , SIGINT );
	exit(0);
}

void oldUser()
{
    system("clear");
    printf("\n\n\t\tEnter UserName:");
    char user[20];
    loop:
	scanf("%[^\n\t]s",user);
	scanf("%c",&flushChar);
    FILE *search;
    int finder=0;
    search=fopen("UserDetails.txt","r");
    char pass[15];
    while(!feof(search))
    {
        char uname[20];
        fscanf(search,"%s",uname);
		//printf("%s",uname);
        if(strcmp(uname,user)==0)
        {
            char ch;
            fscanf(search,"%c",&ch);
            fscanf(search,"%s",pass);
            finder=1;
            break;
        }

    }
    if(finder==0)
    {
        printf("\n\tWrong UserName! Please Enter a correct UserName : ");
        goto loop;
    }
    loop1:
    system("clear");
    char userpass[13];
	signal(SIGALRM , Timeout);
	alarm(10);
    enterPass(userpass);
	signal(SIGALRM ,SIG_IGN);
    printf("\n\n\n\tVerifying.....\n\n");
    sleep(4);
    if(strcmp(userpass,pass)!=0)
    {
        printf("\n\tWrong Password! Enter Correct Password\n\tEnter: ");
        goto loop1;
    }
    /*FILE *passf;
    passf=fopen("CurrentPassword.txt","w");
    fprintf(passf,"%s",pass);
    fclose(passf);*/
    OldUserMenu(user);
	
}

int checkUserID(char nm[]){
	char check[20];
	FILE *access = fopen("UserDetails.txt","r");
	while(!feof(access)){
		fscanf(access,"%s",check);
		if(strcmp(check,nm) == 0){
			fclose(access);
			return 1;
		}
		fscanf(access,"%s",check);
	}
	fclose(access);
	return 0;
}

void newUser()
{
    printf("\n\t*************Enter following Details*************\n\t");
    FILE *master;
	FILE *udetails;
	FILE *userEvents;
  
    master=fopen("MasterList.txt","a");
	userEvents = fopen("RegisteredEvents.txt","a");
	
    printf("\n\tEnter your first name(15 letters max) : ");
    char name[21],lastname[10],username[20],email[20];
	//scanf("%c",&flushChar);
	scanf("%[^\n\t]s",name);
    //scanf("%s",name);
    printf("\n\tEnter your last name(10 letters max) : ");
    scanf("%c",&flushChar);
	scanf("%[^\n\t]s",lastname);
	//scanf("%s",lastname);
    strcat(name," ");
    strcat(name,lastname);
	
	printf("\n\tEnter your Email  : ");
	scanf("%c",&flushChar);
	scanf("%[^\n\t]s",email);
	
	askuname:
	printf("\n\tEnter your UserName : ");
    scanf("%c",&flushChar);
	scanf("%[^\n\t]s",username);
	
	if(checkUserID(username)){
		printf("\n\tThat user name already exists enter diffrent username....");
		goto askuname;
	}
	
	udetails = fopen("UserDetails.txt","a");
    fprintf(master,"\n%s ",name);
    fprintf(master,"%s ",email);
	fprintf(master , "%s ", username);
	fprintf(userEvents , "\n%s none", username);
	fprintf(udetails,"\n%s ",username);
	
	fclose(userEvents);
    fflush(stdin);
    printf("\n\tEnter your College name : ");
    char college[100];
    
    scanf("%c",&flushChar); // temp statement to clear buffer
    scanf("%[^\n]",college);

    //gets(college);
    fprintf(master,"%s ",college);
    printf("\n\tEnter a password for your account \n\t(Min.8 Max. 13 characters..Must contain: a special character ,a uppercase letter,a lower case letter and a number)\n\tEnter::");
    int checker=0;
    char pass[13];
    while(checker!=1)
    {
    scanf("%c",&flushChar);
	scanf("%[^\n\t]s",pass);
	//scanf("%s",pass);

    checker=checkPassword(pass);

    if(checker==1)

        printf("\n\tPassword Acceptable!");
    else
        printf("\n\tINVALID PASSWORD!!!\n\tEnter different password:");
    }
    
	fprintf(udetails,"%s",pass);
    fclose(udetails);
	
	printf("\t********USER REGISTRATION SUCCESSFULL*******");
    printf("\n\t\tPress any key to Login ....\n");
	scanf("%c",&flushChar);
	flushChar = getchar();

    system("clear");
	
	fclose(master);
    userMenu();
    return;
}

void viewRegisteredList(char id[])
{
    system("clear");
    FILE *master;
    master=fopen("RegisteredEvents.txt","r");
    char events[100];
    char checkid[20];
    int skipper=0;
	int i,cnt=1;
    while(!feof(master))
    {
        fscanf(master,"%s",checkid);
		fscanf(master,"%s",events);
        if(strcmp(checkid,id)==0)
        {   
            skipper=1;
            break;
        }
    }
	
    if(skipper==0)
    {
        printf("Wrong ID! Enter Valid one!");
        return;
	}
	
	printf("\n%d : ",cnt++);
	for(i=0;i<strlen(events)-1;i++){
		if(events[i] == ',')
			printf("\n%d : ",cnt++);
		else
			printf("%c",events[i]);
	}
	
    fclose(master);
    
    printf("\n\n\tPress Any Key....\n");
	char c=getchar();
    OldUserMenu(id);

}

void viewList(int skipper,char id[])
{
    int num=1;
    if(skipper==1)
        system("clear");
    printf("\t***********LIST OF ALL EVENTS***********\n");
    FILE *view;
    view=fopen("EventList.txt","r");
    char event[20];
	int i=1;
    while(!feof(view))
    {
        //fscanf(view," %[^\n\t]s",event);
		fgets(event , 20, view);
        printf("%d : %s",i++,event);
    }
	printf("\n");
    if(skipper==1)
    {
		printf("\n\n\t Press any key...\n");
		char c=getchar();
        OldUserMenu(id);

    }
	fclose(view);
	return ;
}


