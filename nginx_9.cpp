#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_usr(int signo)
{
	if (signo == SIGINT)
	{
		printf("%s\n", "捕捉到SIGINT信号！");
	}
}

int main(int argc, char* const* agrv)
{
	sigset_t newMask;
	sigset_t oldMask;

	if (signal(SIGINT, sig_usr) == SIG_ERR)
	{
		printf("%s\n", "注册SIGINT信号处理函数失败！");
	}

	sigemptyset(&newMask);
	sigaddset(&newMask, SIGINT);

	if (sigprocmask(SIG_BLOCK, &newMask, &oldMask) < 0)
	{
		printf("%s\n", "设置信号屏蔽集newMask失败！");
	}
	
	printf("%s\n", "SIGINT信号屏蔽中...");
    sleep(10);
	printf("%s\n", "SIGINT信号开始解除屏蔽...");

	if (sigprocmask(SIG_SETMASK, &oldMask, NULL) < 0)
	{
		printf("%s\n", "设置信号集oldMask失败！");
	}

	printf("%s\n", "SIGINT信号已接触屏蔽！");

	while (true)
	{
		sleep(1);
		printf("%s\n", "hello world!");
	}
	return 0;
}