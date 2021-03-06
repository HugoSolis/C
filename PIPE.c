#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	printf("Starting server\n");
	int FDW,FDR;
	char * Fifo_Server = "/pipes/server_pipe";
	mkfifo(Fifo_Server,0666);
	char Msg[100];
	//strcpy(Msg,"");
	int PID = fork();
	int ret,value;
	while (1)
	{
		if(PID == 0){
			printf("F\n");
		FDW = fopen(Fifo_Server,"w");
		fgets(Msg,100,stdin);
		write(FDW,Msg,strlen(Msg)+1);
		//strcpy(Msg,"");
		close(FDW);
		unlink(FDW);		
		exit(0);}

		else{
			sleep(1);
			wait(0);
			FDR = fopen(Fifo_Server,"r");
			printf("C\n");
			//fgets(Msg,100,FD);
			//ret=fscanf(FD,"%d",&value);
			//printf("This is the parent. Received value %d from child on fifo \n", value);
			value = read(FDR,Msg,sizeof(Msg));
			printf("%i",value);
			printf("Message:\n %s\n",Msg);
			//strcpy(Msg,"");
			close(FDR);
			if(strncmp(Msg, "EXIT",4) == 0)
			{
				printf("Abort process\n");
				break;
			}
		exit(0);}
	}
	return 0;
}