#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <wait.h>

int main(void){
	FILE    *textFile;
    	char    *text;
    	int childStatus;
     
    	textFile = fopen("seed.txt", "r");
    	fscanf(textFile,"%[^\n]",text);
	int seed=atoi(text);
	srand(seed);
    	printf("Read seed value: %d\n", seed);
	int numChild = rand() % (11+1-5) + 5;
	printf("Random child count:%d\n",numChild);
	int childrenArray[numChild];
	for (int i = 0; i < numChild; ++i) {
        	childrenArray[i] = rand();
    	}
	
	
	for(int n=0; n<numChild; ++n){
		int rc=fork();
		if(rc==0){
			//child
			int exitCode = (childrenArray[n] % 50) + 1;
			int exitTime = (childrenArray[n] % 3)+1;
            		int p = getpid();
			printf("[Child, PID: %d]: I am the child and I will wait %d seconds and exit with code %d\n", p, exitTime,exitCode);
            		sleep(exitTime);
            		printf("[Child, PID: %d]: Now exiting...\n",p);
            		exit(exitCode);
		}
		else{
			printf("[Parent]: I am waiting for PID %d to finish.\n", rc);
	        	waitpid(rc, &childStatus, 0);
	        	printf("[Parent]: Child %d finished with status code %d. Onward!\n",rc, WEXITSTATUS(childStatus));
		}
	}
	return 0;
}
