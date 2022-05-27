#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>
#include <wait.h>

#define UBUNTU 1

char flushChar;  //used for flusing

uint64_t get_gtod_clock_time ();
void * Admin_Login(void *socket_desc);
void accessEventWiseList();
int adminMenu(int skipper) ;
int authenticate(int caser,char pass[]);
void accessUserList();
void credits();
void changePassword(char pass[]);
void changeUserPass(char user[]);
int checkEventName(char event[]);
int checkPassword(char pass[]);
int checkUserID(char nm[]);
void createEvent();
int decrypt(char pass[]);
void display();
int enterPass(char pass[]);
int encrypt(char pass[]);
void fillEventInfo(char name[],char time[],char date[],char infor[]);
void getUserName(char nm[] , char id[]);
int OldUserMenu(char id[]);
void oldUser();
void modifyTime(char event[] );
void modifyDate(char event[]);
void modifyName(char event[]);
void modifyInfo(char event[]);
void modifyEventInfo();
int mainMenu();
void newUser();
int userMenu();
void viewRegisteredList(char id[]);
void viewList(int skipper,char id[]);
int viewEventInfo(int skipper,char id[]);
void registerUserEvent(char id[]);