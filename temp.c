#include <stdio.h>

void main(){
	FILE *file = fopen("F:\\DA\\2-SP\\Ubuntu\\prj\\Tech-fest-portal-master\\Database\\log.txt","r");
	if(file == NULL)
		printf("1 . Error...\n");
	FILE *file2 = fopen("Events\\Lan23.txt","w");
	if(file2 == NULL)
		printf("2 . Error...\n");
	FILE *file3 = fopen("Database\\EventList.txt","r");
	if(file3 == NULL)
		printf("3 . Error...\n");
}