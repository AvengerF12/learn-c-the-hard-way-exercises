#include <stdio.h>

int main(int argc,char *argv[]){
	int i = 0;
	int n = 0;
	argc = 2;
	char *states[]={
		"California","Oregon","Washington","Texas",NULL
	};
	
	// go through each string in argv
	for(i=1;i<argc;i++){
		argv[1] = states[0];
		printf("arg %d: %s\n",i,argv[i]);
	}
	
	int num_states = 5;
	
	for(i=0,n=0;i<num_states && n<num_states;i++,n++){
		states[0] = argv[0];
		printf("state %d: %s\n",i,states[i]);
		//printf("%d",n);
	}
	return 0;
}
