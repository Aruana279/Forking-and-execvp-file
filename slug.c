#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]){


	int waitTime;
	int coinFlip;
	int randomSeed;
	char* seed_files[] = {"seed_slug_1.txt",
				"seed_slug_2.txt",
				"seed_slug_3.txt",
				"seed_slug_4.txt"};
	if(argc != 2){
		return 0;
	}
	
	int fileNum = atoi(argv[1]);
	if((fileNum >= 1) && (fileNum <= 4)){
		char *com1[]={"last" ,"-i", "-x", NULL};
		char *com2[] = {"id", "--group", NULL};	
		char *text;
		FILE* textFile = fopen(seed_files[fileNum-1], "r");
		fscanf(textFile,"%[^\n]", text);
		int seed=atoi(text);
		srand(seed);
		int p=getpid();
		printf("[Slug PID: %d]: Read seed value: %d\n", getpid(), seed);
		waitTime = rand() % (9+1-4) + 4;
		coinFlip = rand() % 2;
		printf("[Slug PID: %d] Delay time is %d seconds. Flipping coin... %d\n", p, waitTime, coinFlip);
		printf("[Slug PID: %d] I'll get the job done... Eventually...\n", p);
		sleep(waitTime);
		if(coinFlip){
			char *cmd = "id";
			printf("[Slug PID: %d]: Break time is over! I am running the ’id --group’ command.\n",p);
			execvp(cmd, com2);

    		}else{
			char *cmd = "last";
			printf("[Slug PID: %d]: Break time is over! I am running the ’last -d --fulltimes' command.\n",p);
			execvp(cmd, com1);
    		}
	}
	return 0;
	
}
