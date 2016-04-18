#include <stdio.h> 

int main(int argc,char *argv[]){
	int i=0;
	if(argc == 2){
		printf("You only have one argument. You suck.\n");
	} else if(argc > 1 || argc < 4){
		printf("Here's your arguments:\n");
		for (i=1;i<argc;i++){
			printf("%s ",argv[i]);
// 			if(sizeof(argv[i])>20){
// 				printf("This one is fat!\n");
// 			}
		}
		printf("\n");
	}else {
		printf("You have too many arguments. You suck.\n");
	}
	return 0;
}