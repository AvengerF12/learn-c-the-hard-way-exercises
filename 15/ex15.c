#include <stdio.h>

int print_1st_way(int count,int ages[],char *names[])
{
	int i=0;
	// first way using indexing
	i=count-1;
	while(i>=0){
		printf("%s has %d years alive.\n",*(names+i),*(ages+i));
		i--;
	}
	return 0;
}

int print_2nd_way(int count,char **cur_name,int *cur_age)
{
	int i=0;
	// second way using pointers
	i=count-1;
	while(i>=0){
		printf("%s is %d years old.\n",*(cur_name+i),*(cur_age+i));
		i--;
	}
	return 0;
}

int print_3rd_way(int count,char **cur_name,int *cur_age)
{
	int i=0;
	//third way, pointers are just arrays
	i=count-1;
	while(i>=0){
		printf("%s is %d years old again.\n",*(cur_name+i),*(cur_age+i));
		i--;
	}
	return 0;
}

int print_4th_way(int count,int ages[],char *names[],char **cur_name,int *cur_age)
{
	//fourth way with pointers in a stupid complex way
	cur_name=names+(count-1);
	cur_age=ages+(count-1);
// 	printf("%p %d\n",cur_age,ages);
	while(cur_age >= ages){
		printf("%s lived %d years so far.\n",*cur_name,*cur_age);
		cur_name--;
		cur_age--;
	}
	return 0;
}

int print_adresses(int count,char **cur_name,int *cur_age)
{
	int i=count-1;
	while(i>=0){
		printf("Name: %p	Age: %p\n",cur_name+i,cur_age+i);
		i--;
	}
	return 0;
}

int main(int argc,char *argv[])
{
	//creates two arrays we care about
	int ages[]={23,43,12,89,2};
	char *names[]={
		"Alan","Frank","Mary","John","Lisa"
	};

	// safely get the size of ages
	int count=sizeof(ages)/sizeof(int);
	
	print_1st_way(count,ages,names);

	printf("---\n");
	
	//setup the pointers to the start of the arrays
	int *cur_age=ages;
	char **cur_name=names;
	
	print_2nd_way(count,cur_name,cur_age);
	
	printf("---\n");
	
	print_3rd_way(count,cur_name,cur_age);
	
	printf("---\n");
	
	print_4th_way(count,ages,names,cur_name,cur_age);
	
	printf("---\n");
	
	print_adresses(count,cur_name,cur_age);
	
	return 0;
}
