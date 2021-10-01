#include <stdio.h>
#include <unistd.h>
//#include <signal.h>

//          ********************************************************************************
//          *                                                                              *
//          *                                                                              *
//          *                                                                              *
//          *        （bash）              (nginx)                                         *
//          *     **************        *************                   **************     *      
//          *     *            *        *           *                   *            *     *
//          *     *            *        *           *                   *            *     *
//          *     *            *        *           *     ..........    *            *     *
//          *     *            *        *           *                   *            *     *
//          *     **************        *************                   **************     *
//          *    (session leader)      (group leader)                                      *
//          *    （group leader)                                                           *
//          *                                                                              *
//          *                                                                              *
//          *                                                                              *
//          ********************************************************************************         

//nginx进程不随着bash进程退出而退出的方式
//（1）nginx进程拦截bash进程发送的SIGHUP信号(SIG_IGN)
//（2）nginx进程设置到新的session里（setsid()函数，但该函数对进程组组长无效）
//（3）启动nginx进程时，使用setsid命令
// (4) 启动nginx进程时，使用nohup命令（会重定位输出，从屏幕输出改成文件输出）

int main(int agrc, char* const* agrv)
{
	//signal(SIGHUP, SIG_IGN);  //SIG_IGN标志可以使该进程忽略SIGHUP信号

	//pid_t pid;

	//pid = fork(); //系统函数，用来创建子进程

	//if (pid < 0)
	//{
	//	printf("%s\n", "子进程创建失败！");
	//}
	//else if (pid > 0)    //父进程
	//{
	//	printf("%s\n", "父进程退出！");
	//	return 0;
	//}
	//else if (pid == 0)   //子进程
	//{
	//	printf("%s\n", "子进程开始执行！");
	//}

	//setsid();  //新建立一个session，进程组的组长调用该函数无效

	while (1)
	{
		sleep(1);
		printf("%s\n", "hello world!");
	}
	return 0;
}