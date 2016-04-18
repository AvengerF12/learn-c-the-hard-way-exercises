#include <stdio.h> 

int main(int argc,char *argv[]){
	int i = argc-1;
	
	while(i>0){
		printf("arg %d: %s.\n",i,argv[i]);
		i--;
	}
	
	char *states[]={
		"California","Oregon","Washington","Texas"
	};
	
	int num_states = 4;
	i= 0;
	while(1){
		if(i>=num_states){
			break;
		}
		printf("arg %d: %s\n",i,states[i]);
		i++;
	}
	
	i = 0;
	while(i<num_states){
		states[i]=argv[i];
		printf("arg %d: %s\n",i,states[i]);
		i++;
	}
	return 0;
}
