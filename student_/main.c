#include<stdio.h>
#include<getch.h>
#include<stdlib.h>
#include<unistd.h>
#include"teacher.h"
#include"student.h"
#include"master.h"
#include"change.h"

int main()
{
	int i=0;
	char yun[]="欢迎访问信标学院信息管理系统";
	for(;;)
	{
		system("clear");
//		gun();
		printf("%s",yun+i);
		printf("   ");
		printf("%s",yun);
		printf("\33[0;32H                                    \n");
		puts("-------------------------------");
		puts("1、校长端");
		puts("2、教师端");
		puts("3、学生端");
		puts("4、退出");
		puts("-------------------------------");
		printf("请输入指令:");
		fflush(stdout);
		i=(i+3)%45;
		sleep(1);
		if(!kbhit())
			continue;
		else
		{
			switch(getch())
			{
				case '1':passin_m();break;
				case '2':passin_t();break;
				case '3':passin_s();break;
				case '4':return 0;
			}
		}
		
	}
}
