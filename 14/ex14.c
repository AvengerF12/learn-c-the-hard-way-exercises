#include <stdio.h>
#include <ctype.h>
#include <string.h>


//forward declarations aka function prototype
void print_letters(char arg[],int str_len);


void print_arguments(int argc,char *argv[])
{
	int i=0;
	for(i=1;i<argc;i++){
		print_letters(*(argv+i),strlen(*(argv+i)));
	}
}


void print_letters(char arg[],int str_len)
{
	int i=0;
	for(i=0;i<str_len;i++){
		char ch=arg[i];
		if(isdigit(ch) || isblank(ch)){
			printf("'%c' == %d, ",ch,ch);
		}
	}
}


int main(int argc,char *argv[])
{
	char **pargv = argv;
	print_arguments(argc,pargv);
	return 0;
}
