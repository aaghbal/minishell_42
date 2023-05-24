#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	//fd[0] read
	//fd[0] write
	int save_out;
	int file_d;
	//if next node is pipe fork then send res to parent ?
//pipe
//change stdin to fd[0]
//greo
//switch back
int g_fd[2];
pipe(g_fd);
if(fork())
{

	save_out = dup(fileno(stdin));
	dup2(g_fd[1], 1);
	char *ppp[] = {"ls", NULL, NULL};
	execve("/bin/ls", ppp, ppp);
}
	// wait(0);
	// char *ppp[] = {"wc", "-l", NULL};
	// close(g_fd[1]);
	// dup2(g_fd[0], 0);
	// execve("/usr/bin/wc", ppp, ppp);
	while (1);
	
}