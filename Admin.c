#include "myHeader.h"


int adminMenu(int skipper)
    {
        if(skipper==1)
            goto skip;
        int j;
        FILE *adminpass;
        FILE *adminpass1;
        adminpass=fopen("AdminPassword.txt","r");
        int passer=0;
        char pass[13];
        fscanf(adminpass,"%s",pass);
        decrypt(pass);
        fclose(adminpass);
        passer=authenticate(1,pass);
            if(passer==0)
                {
                  system("clear");
                    printf("\n\tLimit Exceeded!! \n\tTry Again!!");
                    return 0;
                }
            else
                {
                    skip:
                      adminpass1=fopen("AdminPassword.txt","r");
                      char pass2[13];
                      fscanf(adminpass1,"%s",pass2);
                      decrypt(pass2);
                      fclose(adminpass1);
                    system("clear");
                    int choice;
                    printf("\n\n\t1.Create Event\n\t2.Modify Event Information\n\t3.Display ALl Users\n\t");
					printf("4.Display the List of registred user with event\n\t");
					printf("5.Display Event Information\n\t6.Change Password\n\t7.Log Out");
                    printf("\n\tEnter your Choice:");
                    scanf("%d",&choice);
					scanf("%c",&flushChar);
                    switch(choice)
                    {
                    case 1:
                        createEvent();
                        break;
                    case 2:
                        modifyEventInfo();
                        break;
                    case 3:
                        accessUserList();
						break;
                    case 4:
                        accessEventWiseList();
                        break;
					case 5:
						system("clear");
						viewEventInfo(2," ");
						break;
					case 6:
                       changePassword(pass2);
                        break;
                    case 7:
                        printf("\n\n\t\tLoading....\n");
						sleep(4);
						system("clear");
                        adminMenu(0);
                         break;
                    }
                }
             return 0;
    }
void accessUserList()
{
    FILE *access;
    char nm[100];
	system("clear");
    printf("\n\t********LIST OF ALL THE PARTICIPANTS IN THE SYNAPSE*******\n");
    access=fopen("MasterList.txt","r");
    while(!feof(access))
    {
        fscanf(access,"%s",nm);
        printf("%s ",nm);
		fscanf(access,"%s",nm);
        printf("%s\n",nm);
		fscanf(access,"%s",nm);fscanf(access,"%s",nm);fscanf(access,"%s",nm);
    }
    fclose(access);
    printf("\n\tPress Any Key... ");
    char c=getchar();
    adminMenu(1);
}

void changePassword(char pass[])
{
    system("clear");
    up:
    printf(" ");
    char checkpass[13];
    printf("\tEnter Your Old Password:");
     scanf("%s",checkpass);
    int length;
    int flag=0;
    printf("\n%s\n",pass);
    length=strlen(checkpass);
    int i;
    for(i=0;i<length;i++)
      {
           if(checkpass[i]!=pass[i])
              {
                   flag=1;
                   break;
              }
      }
    if(flag!=0)
    {
        printf("WRONG PASSWORD...!! \n ENTER AGAIN:\n\t");
        goto up;
    }
    FILE *password;
    password=fopen("AdminPassword.txt","w");
    system("clear");
    upper:
    printf("\n\t*************Enter New Password**********\nPassword must contain: an uppercase letter, a lowercase letter a number and \na special character\nEnter:");
    re:
    scanf("%s",pass);
    int check=checkPassword(pass);
    if(check!=1)
    {
        printf("\tINVALID PASSWORD\n\tPLEASE ENTER A VALID PASSWORD\n");
        printf("ENTER:");
        goto re;
    }
    printf("\n**VALID PASSWORD**\n");
    printf("\nEnter Password Again:");
    scanf("%s",checkpass);
    if(strcmp(checkpass,pass)!=0)
    {
        printf("PASSWORDS DO NOT MATCH ENTER NEW AGAIN");
        goto upper;
    }
    encrypt(pass);
    fprintf(password,"%s",pass);
    fclose(password);
    system("clear");
    printf("\t\t**********PASSWORD CHANGE SUCCESSFULL**********");
    sleep(5);
    adminMenu(1);
}

void accessEventWiseList()
{
    system("clear");
	FILE *events = fopen("EventList.txt","r");
    while(! feof(events))
    {
		
        FILE *access;
        //printf("\n\tEnter name of Event which Event's List you want (exactly same)\n");
        char event[20];
        fscanf(events, "%s",event);
		printf("\n\n\t **************** %s ********************\n",event);
        strcat(event,".txt");
        access=fopen(event,"r");
        char ch;
        //printf("\n\t\t*********List of Registered Users*********\n");
        while(!feof(access))
            {
            fscanf(access,"%c",&ch);
            printf("%c",ch);
            }
		fclose(access);
		printf("continue ... ");
		ch = getchar();
    }
	fclose(events);
	printf("Press any Key ... ");
	char c = getchar();
    system("clear");
    adminMenu(1);
}

void createEvent()
{
    char name[30],n;
    system("clear");
    printf("\n\tPlease Enter the name of event you want to create (Max Size 30): ");
    //fflush(stdin);
	//scanf("%c",&flushChar);
	scanf("%[^\n]",name);
    scanf("%c",&flushChar);
	
    FILE *create;
    FILE *registerevent;
    registerevent=fopen("EventList.txt","a");
    //int number=1;
    fprintf(registerevent,"\n%s",name);
    printf("\n\tCongratulations! Event Created \n\tPlease Enter Following Information about the event\n\t");
	char dt[10];
    printf("Enter date(dd-mm-yyyy): ");
	scanf("%s",dt);
	scanf("%c",&flushChar);
	
    char time[10];
    printf("\n\tEnter Time(with am or pm without spacing): ");
	scanf("%s",time);
	scanf("%c",&flushChar);
    char info[100];
    printf("\n\tEnter some Info about the event: ");
    //fflush(stdin);
	scanf("%[^\n]",info);
    //gets(info);
    fillEventInfo(name,dt,time,info);
    printf("\n\tCongratulations! Event Successfully Registered....\n\n");
    fclose(registerevent);
    strcat(name,".txt");
    create=fopen(name,"w");
    fclose(create);
    printf("\tPress Any Key...\n\n");
	flushChar=getchar();
    adminMenu(1);
}
  
void fillEventInfo(char name[],char dt[],char time[] ,char infor[])
{
    FILE *info;
    info=fopen("EventInfo.txt","a");
    fprintf(info,"\n");
    fprintf(info,"Name: %s\n",name);
	fprintf(info,"Date: %s\n",dt);
    fprintf(info,"Time: %s\n",time);
    fprintf(info,"Information: %s\n",infor);
    fclose(info);

}


void modifyInfo(char event[])
{

    FILE *change;
    change=fopen("EventInfo.txt","r+");
    printf("Enter the New Information of the event: ");
    char newinfo[100],newinfo1[100];
    char ch1; int i=0;
    while(1)
    {
        scanf("%c",&ch1);
        if(ch1=='\n')

            break;

        newinfo[i]=ch1;

        i++;
    }
    strcpy(newinfo1,newinfo);
    strcat(newinfo,"                     ");
    char check[30];
    while(!feof(change))
    {
        fscanf(change,"%s",check);
        if(strcmp(event,check)==0)
        {
            fscanf(change,"%s",check);
            fscanf(change,"%s",check);
			fscanf(change,"%s",check);
			fscanf(change,"%s",check);
			fscanf(change,"%s",check);
			fscanf(change,"%s",check);
            fseek(change,-strlen(check), SEEK_CUR);
            fprintf(change,"%s",newinfo);
            break;
        }
    }
	fclose(change);
    printf("\t\t*******EVENT INFORMATION SUCCESSFULLY CHANGED*******\n");
    printf("\tNew Information:%s",newinfo1);
}

void modifyTime(char event[])
{
    FILE *change;
    change=fopen("EventInfo.txt","r+");
    printf("Enter the New time of the event(e.g.08:00am): ");
    char newtime[50],newtime1[50];
    scanf("%s",newtime);
    strcpy(newtime1,newtime);
    char check[30];
    while(!feof(change))
    {
        fscanf(change,"%s",check);
        if(strcmp(event,check)==0)
        {

            fscanf(change,"%s",check);
            fscanf(change,"%s",check);
			fscanf(change,"%s",check);
			fscanf(change,"%s",check);
            fseek(change,-strlen(check), SEEK_CUR);
            fprintf(change,"%s",newtime);
            break;
        }
    }
	fclose(change);
    printf("\t\t*******EVENT TIME SUCCESSFULLY CHANGED*******");
    printf("\n\tOld time:%s\n",check);
    printf("\tNew Time:%s",newtime);
}

void modifyDate(char event[])
{
    FILE *change;
    change=fopen("EventInfo.txt","r+");
    printf("Enter the New Date (dd-mm-yyyy): ");
    char newtime[50],newtime1[50];
    scanf("%s",newtime);
    strcpy(newtime1,newtime);
    char check[30];
    while(!feof(change))
    {
        fscanf(change,"%s",check);
        if(strcmp(event,check)==0)
        {

            fscanf(change,"%s",check);
            fscanf(change,"%s",check);
            fseek(change,-strlen(check), SEEK_CUR);
            fprintf(change,"%s",newtime);
            break;
        }
    }
	fclose(change);
    printf("\t\t*******EVENT Date SUCCESSFULLY CHANGED*******");
    printf("\n\tOld Date:%s\n",check);
    printf("\tNew Date:%s",newtime);
}

void modifyName(char event[])
{
    FILE *change;
    change=fopen("EventList.txt","r+");
    printf("Enter the New Name of the event: ");
    char newname[50],newname1[50];
    scanf("%s",newname);
    strcpy(newname1,newname);
    char check[30];
   
    while(!feof(change))
    {

        fscanf(change,"%s",check);
        //printf("%s\n",check);
        if(strcmp(event,check)==0)
        {
            fseek(change, -strlen(check), SEEK_CUR);
            fprintf(change,"%s\n",newname);
            int counter=strlen(check)-strlen(newname);
            if(counter>0)
            while(counter--)
                fprintf(change," ");
            break;
        }
    }
	fclose(change);
    system("clear");
    printf("\t\t*******EVENT NAME SUCCESSFULLY CHANGED*******");
    printf("\n\tOld Name:%s\n",event);
    printf("\tNew Name:%s",newname1);
    fclose(change);
    sleep(3);
}
void modifyEventInfo()
{
    loop:
    system("clear");
    viewList(0," ");
    printf("\t\t****Enter which event you want to modify*******\n");
    char event[30];
    printf("\nEnter the name of event you want to modify:");
    scanf("%s",event);
    printf("\tEnter what do you want to modify:\n\t");
    printf("1.Date\n\t2.Time\n\t3.Information\n\tEnter:");
    int choice;
    scanf("%d",&choice);
	scanf("%c",&flushChar);
    switch(choice)
    {
	case 1:
		modifyDate(event);
		break;
    case 2:
        modifyTime(event);
        break;
    case 3:
        modifyInfo(event);
    }
    printf("\n\n\n\tDo you wish to modify any more events?\n\t1.Yes\n\t2.No\n\tEnter: ");
    int looper;
    scanf("%d",&looper);
    if(looper==1)
        goto loop;
    adminMenu(1);
    return;
}





