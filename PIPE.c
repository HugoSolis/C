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
	int FD;
	char * Fifo_Server = "/pipes/server_pipe";
	mkfifo(Fifo_Server,0666);
	char Msg[100];
	int PID = fork();
	while (1)
	{
		if(PID == 0){
			printf("F");
		FD = open(Fifo_Server,O_WRONLY);
		fgets(Msg,100,stdin);
		write(FD,Msg,strlen(Msg)+1);
		//strcpy(Msg,"");
		close(FD);
		exit(0);}

		else{
			sleep(1);
			wait(NULL);
			printf("C");
			FD = open(Fifo_Server,O_RDONLY);
			read(FD,Msg,sizeof(Msg));
			printf("Message:\n %s\n",Msg);
			//strcpy(Msg,"");
			close(FD);
			if(strncmp(Msg, "EXIT",4) == 0)
			{
				printf("Abort process\n");
				break;
			}
		}
	}
	return 0;
}