#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

//   *****************************************************************************************
//   *
//   *
//   *
//   *       僵尸进程
//   *       (1) 产生：子进程结束，父进程活着，父进程没调用wait/waitpid
//   *      （2）解决：父进程调用wait/waitpid、杀掉父进程、系统重启
//   *
//   *
//   *
//   *
//   *
//   *
//   *
//   *
//   *
//   *
//   *
//   *
//   ******************************************************************************************

void sig_usr(int signo)
{
	if (signo == SIGINT)
	{
		printf("%s\n", "捕捉到SIGINT信号！");
	}
	else if (signo == SIGCHLD)
	{
		int status;
		pid_t pid = waitpid(-1, &status, WNOHANG);
	}
}

int main(int argc, char* const* agrv)
{
	pid_t pid;

	if (signal(SIGINT, sig_usr) == SIG_ERR)
	{
		printf("%s\n", "注册SIGINT信号处理函数失败！");
	}

	if(signal(SIGCHLD, sig_usr) == SIG_ERR)
	{
		printf("%s\n", "注册SIGCHLD信号处理函数失败！");
	}

	pid = fork();

	if (pid < 0)
	{
		printf("%s\n", "fork子进程失败！");
	}

	while (true)
	{
		sleep(1);
		printf("%s进程id=%d\n", "hello world!", getpid());
	}
	return 0;
}