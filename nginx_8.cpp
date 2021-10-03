#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_usr(int signo)
{
	if (signo == SIGUSR1)
	{
		printf("%s\n", "捕捉到SIGUSR1信号！");
	}
	else if(signo == SIGUSR2)
	{
		printf("%s\n", "捕捉到SIGUSR2信号！");
	}
}

int main(int argc, char* const* agrv)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		printf("%s\n", "无法捕捉到SIGUSR1信号！");
	}
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
	{
		printf("%s\n", "无法捕捉到SIGUSR1信号！");
	}
	while (true)
	{
		sleep(1);
		printf("%s\n", "hello world!");
	}
	return 0;
}