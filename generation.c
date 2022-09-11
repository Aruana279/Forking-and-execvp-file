#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <wait.h>

int main(){
	FILE    *textFile;
    	char    *text;
    	int childStatus;
     
    	textFile = fopen("seed.txt", "r");
    	fscanf(textFile,"%[^\n]",text);
	int seed=atoi(text);
	srand(seed);
    	printf("Read seed value: %d\n", seed);
	int lifespan = rand() % ((14-1)-8) + 8;
	printf("Random Descendant Count: %d\n",lifespan);
	printf("Time to meet the kids/grandkids/great grandkids/...\n");
	
	while(lifespan>0){
		int rc=fork();
		if(rc==0){
			//child
            		int p = getpid();
			if(lifespan==0){
				exit(lifespan);
			}
            		printf("\t[Child, PID: %d]: I was called with descendant count=%d. I'll have %d descendant(s)\n",p,lifespan,lifespan-1);
            		lifespan--;
		}
		else{
			int p = getpid();
			printf("[Parent, PID: %d]: I am waiting for PID %d to finish.\n",p,rc);
			
	        	waitpid(rc, &childStatus, 0);
	        	printf("[Parent]: Child %d finished with status code %d. It's now my turn to exit.\n",rc, WEXITSTATUS(childStatus));
	        	exit(WEXITSTATUS(childStatus)+1);
		}
	
	}		
	
	return 0;
}
