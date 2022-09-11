#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>

int main(int argc, char* argv[]){
    	int slugsInRace[4];
    	int slugsLeft=4;
    	struct timespec start;
    	struct timespec end;
    	struct timespec stop;
    	clock_gettime(CLOCK_REALTIME, &start);
    	
    	for(int i = 0; i < 4; i++){
    		int rc=fork();
    		if(rc == 0){
    			int p=getpid();
    			char numToPass[2];
    			sprintf(numToPass, "%d", i+1);
            		char *args[]={"./slug", numToPass, NULL};
            		printf("[Child PID: %d]: Executing '%s %s' command...\n", p, args[0], args[1]);
            		execv(args[0], args);
    		}else{
    			printf("[Parent]: I forked off child %d\n", rc);
    			slugsInRace[i]=rc;
    		}
    	}
    	while (slugsLeft>0){
    		
    		printf("The race is still going. The following children are still racing: ");
    		for (int i = 0; i < 4; i++){
    			if (slugsInRace[i]!=0){
    				printf("%d ",slugsInRace[i]);
    				pid_t pid = waitpid(slugsInRace[i], NULL, WNOHANG);
    				if (pid == slugsInRace[i]) {
    					clock_gettime(CLOCK_REALTIME, &stop);
                    			printf("Child %d has crossed the finish line! It took %f seconds\n", slugsInRace[i],(double) (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)/1000000000);
                    			slugsInRace[i] = 0;
                    			slugsLeft --;}
    			}	
    		}
    		usleep(250000);
    		
    		
    	}
    	
    	clock_gettime(CLOCK_REALTIME, &end);
    	printf("The race is over! It took %f \n",(double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000);
    	
     
    	
	

	return 0;
}
