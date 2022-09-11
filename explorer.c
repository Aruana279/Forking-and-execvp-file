#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void){
	FILE    *textFile;
    	char    *text;
    	int childStatus;
    	char s[256];
    	char* toVisit[6];
    	char* command[] = {"ls", "-tr", NULL};
     
    	textFile = fopen("seed.txt", "r");
    	fscanf(textFile,"%[^\n]",text);
	int seed=atoi(text);
	srand(seed);
    	printf("Read seed value: %d\n", seed);
	printf("It’s time to see the world/file system!\n");
	char* directories[6] = { "/home", "/proc", "/proc/sys", "/usr", "/boot", "/sbin" };
	for(int i = 0; i < 5; i++) {
        	toVisit[i] = directories[rand() % 6];
        	printf("Selection #%d: %s [SUCCESS]\n",i+1, s);
        	printf("Current reported directory: %s\n", getcwd(s, 100));
        	int rc=fork();
        	if(rc==0){
			//child
            		int p = getpid();
			printf("[Child, PID: %d]: Executing 'ls -tr' command...\n",p);
            		execvp("ls", command);
            		exit(0);
		}else{
			printf("[Parent]: I am waiting for PID %d to finish.\n", rc);
	        	waitpid(rc, &childStatus, 0);
	        	printf("[Parent]: Child %d finished with status code 0. Onward!\n",rc);
			
		}
	
        	return 0;
    	}
	
}
