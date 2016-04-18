#include <stdio.h> 

int main(int argc,char *argv[]){
	if(argc < 2){
		printf("ERROR: You need at least one argument.\n");
		return 1;
	}
	int i=0;
	int a=0;
	char letter = argv[a][i];
	for(a=1;a<argc;a++){
		for(i=0,letter=argv[a][i];argv[a][i] != '\0';i++){
// 			printf("'%c'\n",65);
			letter = (argv[a][i]);
 			if(letter<97){
 				letter = (argv[a][i] + 32);
 			}
 			if(letter=='a' || letter=='e' || letter=='i' || letter=='o' || letter=='u' || (letter=='y' && i>2)){
				printf("%d: '%c' is a vowel.\n",i,letter-32);
			} else {
				printf("%d: '%c' is not a vowel\n",i,letter-32);
			}
// 			switch(letter){
// 				case 'a':
// // 				case 'A':
// 					printf("%d: 'A'\n",i);
// 					break;
// 				case 'e':
// // 				case 'E':
// 					printf("%d: 'E'\n",i);
// 					break;
// 				case 'i':
// // 				case 'I':
// 					printf("%d: 'I'\n",i);
// 					break;
// 				case 'o':
// // 				case 'O':
// 					printf("%d: 'O'\n",i);
// 					break;
// 				case 'u':
// // 				case 'U':
// 					printf("%d: 'U'\n",i);
// 				case 'y':
// // 				case 'Y':
// 					if(i>2){
// 						printf("%d: 'Y'\n",i);
// 					}
// 					break;
// 				default:
// 					printf("%d: %c is not a vowel\n",i,letter);
// 			}
		}
		printf("\n");
	}
	return  0;
}
