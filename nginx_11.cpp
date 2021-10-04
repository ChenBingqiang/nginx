#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

//   *****************************************************************************************
//   *
//   *
//   *       守护进程书写规则：
//   *       (1) 调用umask(0)
//   *      （2）fork子进程，setsid改子进程为session leader，父进程退出
//   *       (3) 标准输入、标准输出，重定向到空设备
//   *
//   *        概念：
//   *      （1）文件描述符：一个常量，标识一个文件
//   *            1.1 STDIN_FILENO （0）: 标准输入（键盘）
//   *            1.2 STDOUT_FILENO（1）: 标准输出（屏幕）
//   *            1.3 STDERR_FILENO（2）: 标准错误（屏幕）
//   *            注：程序运行起来，文件描述符 0、1、2会自动被打开，指向对应的设备
//   *      （2）输入输出重定向
//   *            2.1 输出重定向：命令行中加 > 即可
//   *            2.2 输入重定向：命令行中加 < 即可
//   *      （3）空设备：/dev/null
//   *      （4）守护进程不会收到的信号
//   *           4.1 来自内核的SIGHUP信号（ 一般用该信号来表示配置文件已改动，守护进程需要读取该文件）
//   *           4.2 来自内核的SIGINT、SIGWINCH信号 （终端大小改变信号）
//   *      （5）守护进程与后台进程的区别 
//   *           6.1 后台进程能在屏幕输出，守护进程不能
//   *           6.2 后台进程受终端影响，守护进程不受终端影响
//   *
//   *
//   ******************************************************************************************

int ngx_demo()
{
	int fd;

	switch (fork())
	{
	case -1:
		printf("%s\n", "fork子进程失败！");
		return -1;
	case 0:
		printf("%s\n", "子进程，接着执行...");
		break;
	default:
		printf("%s\n", "父进程，直接退出...");
		exit(0);
	}

	if (setsid() == -1)
	{
		printf("%s\n", "更改子进程为session leader失败！");
		return -1;
	}

	umask(0);

	fd = open("/dev/null", O_RDWR);
	if (-1 == fd)
	{
		printf("%s\n", "打开空设备失败！");
		return -1;
	}

	if (-1 == dup2(fd, STDIN_FILENO))
	{
		printf("%s\n", "输入重定向失败！");
		return -1;
	}

	if (-1 == dup2(fd, STDOUT_FILENO))
	{
		printf("%s\n", "输出重定向失败！");
		return -1;
	}

	if (fd > STDERR_FILENO)
	{
		if (-1 == close(fd))
		{
			printf("%s\n", "关闭文件描述符失败！");
			return -1;
		}
	}

	return 1;
}

int main(int argc, char* const* agrv)
{

	if (ngx_demo() != 1)
	{
		printf("%s\n", "守护进程创建失败！");
		return 1;
	}

	printf("%s\n", "守护进程创建成功！");

	while (true)
	{
		sleep(1);
		printf("%s%s%d\n", "hello world!", " 守护进程运行中，进程id = ", getpid());
	}
	return 0;
}