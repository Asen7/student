#include"change.h"
#include"student.h"
#include<string.h>
#include<getch.h>
//
#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
int kbhit(void)
{
struct termios oldt, newt;
int ch;
int oldf;
tcgetattr(STDIN_FILENO, &oldt);
newt = oldt;
newt.c_lflag &= ~(ICANON | ECHO);
tcsetattr(STDIN_FILENO, TCSANOW, &newt);
oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
ch = getchar();
tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
fcntl(STDIN_FILENO, F_SETFL, oldf);
if(ch != EOF)
{
ungetc(ch, stdin);
return 1;
}
return 0;
}
//


//空格补齐
void space(char *name)
{
	int i=0;
	for(; i<20-strlen(name)*2/3; i++)	printf(" ");
}
void spacey(char *name)
{
	int i=0;
	for(; i<20-strlen(name); i++)	printf(" ");
}
//按任意键继续
void any(void)
{
	puts("按任意键继续");
	getch();
	return;
}

//首次登录修改密码
void first(char *pass)
{
	char new1[10]={},new2[10]={},c;
	while(1)
	{
		printf("请输入新密码(最高9位):\n");
		scanf("%s%c",new1,&c);
		printf("请再输入新密码:\n");
		scanf("%s%c",new2,&c);
		if(strlen(new1)>9||strlen(new2)>9)
		{
			puts("无效密码，请重输!");
			any();
		}
		else if(!strcmp(pass,new1))
		{
			puts("与原密码相同，请重输!");
			any();
		}
		else if(!strcmp(new1,new2))
		{
			strcpy(pass,new1);
			puts("更改密码成功!");
			any();
			return;
		}
		else
		{
			puts("两次密码不相同，请重输!");
			any();
		}
	}
}
//修改密码
void change_pass(char *pass)
{
	char old[10]={};
	while(1)
	{
		printf("请输入原密码:\n");
		scanf("%s",old);
		if(!strcmp(old,pass))
		{
			first(pass);
			break;
		}	
		else
		{
			puts("错误密码");
			any();
		}
	}
}

