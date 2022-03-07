#include <stdio.h>

int main(int argc, char const *argv[])
{
	printf("Starting server\n");
	int FD;
	char * Fifo_Server = "/pipes/server_pipe";
	mkfifo(Fifo_Server,0666);
	char Msg[100];

	while (TRUE)
	{
		FD = open(Fifo_Server,O_WRONLY);
		fgets(Msg,100,stdin);
		write(FD,Msg,stlen(Msg)+1);
		close(FD);
	}
	return 0;
}