#include"teacher.h"
#include"student.h"
#include"change.h"
#include"main_t.h"
#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<getch.h>
#include<unistd.h>
//定义教师结构体变量，tch为在校教师，tch2为离校教师
//t为方便赋值等操作的预设变量，t1为当前登录的教师信息
struct Teacher tch[MAX_tch],tch2[MAX_tch2],t,t1;
//全局学生结构体变量声明，stu为在校学生，stu2为离校学生，s为方便赋值等操作的预设变量
extern struct Student stu[MAX_stu],stu2[MAX_stu2],s;
//学生总人数
int stu_num=0;

//排头
void paitou(void)
{
	puts("-------------------------------------------------------");
	puts("姓名                 性别 学号      语文 数学 英语 排名");
	puts("-------------------------------------------------------");
}
//输出学生信息
void s_infor(int i)
{
	printf("%s",stu[i].name);
	spacey(stu[i].name);
	printf(" %s   %d   %d   %d   %d   %d\n",stu[i].sex=='w'?"女":"男",stu[i].id,stu[i].g_chinese,stu[i].g_math,stu[i].g_english,stu[i].rank);
}
//判断无效姓名
bool ifs_name(char *name)
{
	if(strlen(name)>19)							
	{
		puts("---------------------------");
		puts("无效姓名!");
		puts("---------------------------");
		any();
		return true;
	}
	else
		return false;
}
//判断学号是否合法
bool ifs_id(int id)
{
	if(id>s_id+MAX_stu || id<s_id)
	{
		puts("---------------------------");
		puts("非法学号!");
		puts("---------------------------");
		any();
		return true;
	}
	else
		return false;
}
//判断无效性别
bool ifs_sex(char sex)
{
	if(sex!='w'&&sex!='m')				//判断无效姓别
	{
		puts("---------------------------");
		puts("无效姓别!");
		puts("---------------------------");
		any();
		return true;
	}
	else
		return false;
}


//初始化（读取）学生数据
void init_t(void)
{
	int id=0;
	FILE *fp_s=fopen(student,"r");		//打开学生信息文件
	if(fp_s==NULL)						//路径错误或打开失败报错并退出
	{
		puts("学生信息数据路径错误!");
		puts("---------------------");
		any();
		return;
	}
	while(fread(&s,sizeof(s),1,fp_s)!=0)//读取学生数据至结构体stu，以备后续使用，计算学生数量
	{
		id=s.id-s_id-1;
		stu[id]=s;
		stu_num++;
	}
	fclose(fp_s);						//关闭文件						
}

void passin_t(void)
{
	int i=0;
	char c,pass[10]="123456";		//c用于吸收多余的换行符，pass为初始密码
	FILE *fp_t=fopen("teacher.txt","r+");
	if(fp_t==NULL)
	{
		puts("数据路径错误!");
		puts("-------------------");
		any();
		return;
	}
	system("clear");
	puts("教师模式");
	puts("-------------------");
	printf("请输入工号:\n");	
	scanf("%d%c",&t.id,&c);
	printf("请输入密码:\n");
	scanf("%s%c",t.pass,&c);
	puts("-------------------");
	i=t.id-t_id-1;	//设置循环次数上限，避免死循环
	t1.id=t.id-1;					//确保初始t1.id!=t.id
	while(i-->=0 && t1.id!=t.id)	//循环读取直至t1为本次登录的教师信息结构体（如果工号合法）
	{
		fread(&t1,sizeof(t),1,fp_t);
	}
	if(t1.sex==0 || t1.id!=t.id)	//非法工号报错退出
	{
		printf("无效工号!\n");
		puts("-------------------");
		any();
		return;
	}
	fseek(fp_t,-1*sizeof(t),SEEK_CUR);	  //文件结构指针回退一个结构体长度，为后续写入做准备
	if(t1.n==3)							  //判断账户是否锁定
	{
		printf("账户锁定,请联系校长!\n");
		puts("-------------------");
		any();
		return;
	}
	if(!strcmp(t.pass,t1.pass))			  //比对密码是否正确
	{
		if(!strcmp(t1.pass,pass))		  //比对密码是否是初始密码
		{
			puts("首次登录请重置密码!");
			puts("---------------------");
			first(t1.pass);			
		}
		t1.n=0;
		fwrite(&t1,sizeof(t),1,fp_t);	  //将新信息写入文件对应位置
		fseek(fp_t,-1*sizeof(t),SEEK_CUR);//文件结构指针回退一个结构体长度，为后续写入做准备
		init_t();
		main_t();
	}
	else
	{
		puts("密码错误!");				  
		puts("-------------------");
		any();
		t1.n++;
		fwrite(&t1,sizeof(t),1,fp_t);
	}
	fclose(fp_t);
	return;
}
//教师界面
char menu_t(void)
{
	system("clear");
	printf("教师模式|欢迎 %s !\n",t1.name);
	puts("-----------------------");
	puts("1、添加学生");
	puts("2、删除学生");
	puts("3、查找学生");
	puts("4、修改学生信息");
	puts("5、录入学生成绩");
	puts("6、重置学生密码");
	puts("7、显示所有在校学生信息");
	puts("8、显示所有退出学生信息");
	puts("9、退出系统");
	puts("-----------------------");
	printf("请输入指令:");
	char cmd=getch();
	return cmd;
}
//计算学生成绩排名
void rank(void)
{
	int sum=0;
	for(int i=0; i<MAX_stu; i++)
	{
		if(stu[i].sex==0)	continue;
		stu[i].rank=1;
		sum=stu[i].g_chinese+stu[i].g_math+stu[i].g_english;
		for(int j=0; j<MAX_stu; j++)
		{
			if(stu[j].sex==0)	continue;
			if(sum<stu[j].g_chinese+stu[j].g_math+stu[j].g_english)	stu[i].rank++;
		}
	}
}
//添加单个学生
void add_one(void)
{
	if(stu_num>=MAX_stu)				//判断学生是否已满，如果是，提示并退出
	{
		puts("学生已满!");
		puts("---------------");
		any();
		return;
	}
	int i=0;
	char c;
	while(stu[i].sex!=0)	i++; 		//调整学生结构体下标至空余位置
	while(1)
	{
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("---------------------------");
		printf("请输入学生姓名(18字节内):\n");
		fgets(s.name,100,stdin);
//		scanf("%s%c",s.name,&c);
		if(ifs_name(s.name))			//判断无效姓名
		{
			continue;
		}
		if(s.name[strlen(s.name)-1]=='\n')	s.name[strlen(s.name)-1]='\0';
		printf("请输入学生性别(w或m):\n");		//判断无效姓别
		scanf("%c%c",&s.sex,&c);
		if(ifs_sex(s.sex))
		{
			continue;
		}
		stu_num++;						//全部正常添加成功，学生数+1
		puts("添加成功!");
		puts("---------------------------");
		any();
		break;
	}
	stu[i]=s;							//写入stu结构体，并生成学号，初始密码
	stu[i].id=s_id+i+1;
	strcpy(stu[i].code,"123456");
}
//批量添加学生
void add_more(void)
{
	int i=0,n=0;
	char c,file[100]={};
	FILE *fp=NULL;
	if(stu_num>=MAX_stu)				//判断学生是否已满，如果是，提示并退出
	{
		puts("学生已满!");
		any();
		return;
	}
	while(1)
	{
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("--------------------------");
		printf("请输入待导入文件路径:\n");
		scanf("%s%c",file,&c);
		puts("--------------------------");
		fp=fopen(file,"r");
		if(NULL==fp)
		{
			puts("无效路径，请重输!");
			puts("--------------------------");
			any();
			continue;
		}
//		while(fscanf(fp,"%s",s.name)!=EOF&&fscanf(fp," %c",&s.sex)!=EOF)
		while(fscanf(fp,"\n%[^\n]",s.name)!=EOF&&fscanf(fp," %c",&s.sex)!=EOF)//循环读取信息
		{
//			printf("%d  %c",i,s.sex);
//			s.name(strlen(s,name))='\0';
			if(strlen(s.name)>=18 || (s.sex!='w'&&s.sex!='m'))//判断信息是否非法
			{
				printf("姓名: %s 性别: %c 非法\n",s.name,s.sex);
				continue;
			}
			else								//合法则写入
			{
				while(stu[i].sex!=0)	i++;	//调整学生结构体下标至空余位置
				stu[i]=s;						//写入stu结构体，并生成学号，初始密码，增加学生数
				stu[i].id=s_id+i+1;
				strcpy(stu[i].code,"123456");
				stu_num++;
				n++;
				if(stu_num>=MAX_stu)			//未能全部导入则输出提示信息及导入数量
				{
					printf("学生已满!仅导入%d名学生\n",n);
					puts("--------------------------");
					any();
					return;
				}
			}
		}
		break;
	}
	printf("导入完毕,共导入%d名学生\n",n);;
	fclose(fp);									//关闭文件
	puts("--------------------------");
	any();
	return;
}
//添加学生的界面
void add(void)
{
	while(1)
	{
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("---------------------");
		puts("1、单个添加");
		puts("2、批量导入");
		puts("3、退出");
		puts("---------------------");
		printf("请输入指令:");
		switch(getch())
		{
			case '1':add_one();break;
			case '2':add_more();break;
			case '3':return;
		}
		rank();//更新排名
	}
	
}
//删除学生
void del(void)
{
	system("clear");
	printf("教师模式|欢迎 %s !\n",t1.name);
	puts("---------------------------");
	int i=0,id1=0,id2=0;
	char c;
	FILE *fp;
	while(1)									//输入两次学号删除,不相同、非法学号输出提示信息
	{
		printf("请输入要删除学生学号:\n");
		scanf("%d%c",&id1,&c);
		printf("请再次输入要删除学生学号:\n");
		scanf("%d%c",&id2,&c);
		if(id1!=id2)
		{
			puts("---------------------------");
			puts("两次输入不相同，请重输!");
			puts("---------------------------");
			any();
		}
		else if(ifs_id(id1))
		{
		}
		else
		{
			break;
		}
	}
	i=id1-s_id-1;
	if(stu[i].sex!=0)							//输出学生信息，判断是否删除
	{
		fp=fopen(student2,"a");
		if(NULL==fp)
		{
			puts("---------------------------");
			puts("未发现离校学生档案!");
			puts("---------------------------");
			any();
			return;
		}
		paitou();
		s_infor(i);
		puts("-------------------------------------------------------");
		puts("确认删除?(Y/N)");					//确认删除，信息写入离校生文件，学生数-1
		while(1)
		{										//对应stu结构体的性别项置零
			c=getch();
			if(c=='Y')
			{
				fwrite(&stu[i],sizeof(s),1,fp);
				fclose(fp);
				stu[i].sex=0;
				stu_num--;
				puts("-------------------------");
				puts("已删除并转入离校学生档案。");
				rank();							//更新成绩排名
				break;
			}
			else if(c=='N')
			{
				break;
			}
		}
	}
	else
	{
		puts("---------------------------");	//未找到此学生输出查无此人
		puts("查无此人!");
	}
	puts("---------------------------");
	any();
}
//按姓名寻找学生，支持模糊查找
void find_name(void)
{
	int n=0,i=0,j=0;
	char name[100];
	system("clear");
	printf("教师模式|欢迎 %s !\n",t1.name);
	puts("---------------------------");
	printf("请输入姓名(18字节内):\n");
	fgets(name,100,stdin);
	if(ifs_name(name))							//判断姓名是否合法
	{
		return;
	}
	if(name[strlen(name)-1]=='\n')	name[strlen(name)-1]='\0';
	while(i<MAX_stu)							//输出符合要求的学生信息
	{		
		if(stu[i].sex!=0)
		{
			for( j=0; j<strlen(name); j++)
				if(name[j]!=stu[i].name[j])	break;
			if(j==strlen(name))
			{
				if(i==0)
				{
					system("clear");
					printf("教师模式|欢迎 %s !\n",t1.name);
					paitou();
				}
				s_infor(i);
				n++;
			}
		}
		i++;
	}
	if(n==0)									//未找到输出查无此人
	{
		puts("---------------------------");
		puts("查无此人");
		puts("---------------------------");
	}
	else	puts("-------------------------------------------------------");
	any();
}
//按学号寻找学生
int find_id(void)
{
	while(1)
	{
		int id=0;
		char c;
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("----------------------");
		printf("请输入学号:\n");
		scanf("%d%c",&id,&c);
		if(ifs_id(id))			//判断学号是否合法
		{
			continue;
		}
		id=id-s_id-1;				
		if(stu[id].sex!=0)						//判断该学号是否有学生信息，有则输出
		{
			system("clear");
			printf("教师模式|欢迎 %s !\n",t1.name);
			paitou();
			s_infor(id);
			puts("------------------------------------------------------");
			any();
			return id;
		}
		else									//没有则输出查无此人
		{
			puts("------------");
			puts("查无此人");
			puts("------------");
		}
		any();
	}
}
//查找学生的界面
void find(void)
{
	while(1)
	{
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("---------------------");
		puts("1、按姓名查找");
		puts("2、按学号查找");
		puts("3、退出");
		puts("---------------------");
		printf("请输入指令:");
		switch(getch())
		{
			case '1':find_name();break;
			case '2':find_id();break;
			case '3':return;
		}
	}
}
//修改学生基本信息
void modify_name(int i)
{
	char c;
	int id=0;
	while(1)
	{
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("----------------------");
		printf("输入新姓名(18字节内):\n");
		fgets(s.name,100,stdin);
		if(ifs_name(s.name))					//判断无效姓名
		{
			continue;
		}
		if(s.name[strlen(s.name)-1]=='\n')	s.name[strlen(s.name)-1]='\0';
		printf("输入新学号:\n");
		scanf("%d%c",&s.id,&c);
		if(ifs_id(id))							//判断学号是否合法
		{
			continue;
		}
		printf("输入新性别:\n");
		scanf("%c%c",&s.sex,&c);
		if(ifs_sex(s.sex))						//判断无效姓别
		{
			continue;
		}
		puts("----------------------");
		id=s.id-s_id-1;
		if(stu[id].sex!=0)						//判断输入学号是否已被使用
		{
			puts("该学号已有学生，请重输!");
			puts("----------------------");
			any();
		}
		else
		{
			stu[id]=s;
			stu[id].g_chinese=stu[i].g_chinese;
			stu[id].g_math=stu[i].g_math;
			stu[id].g_english=stu[i].g_english;
			stu[i].sex=0;
			puts("修改成功!");
			puts("----------------------");
			any();
			return;
		}
	}
}
//修改学生成绩信息
void modify_score(int i)
{
	char c;
	while(1)
	{
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("---------------------------");
		printf("输入新语文、数学、英语成绩:\n");
		scanf("%d %d %d%c",&s.g_chinese,&s.g_math,&s.g_english,&c);
		puts("---------------------------");
		if(s.g_chinese<0||s.g_math<0||s.g_english<0||s.g_chinese>100||s.g_math>100||s.g_english>100)//判断成绩是否合法
		{
			puts("无效成绩，请重输!");
			puts("---------------------------");
			any();
		}
		else
		{
			stu[i].g_chinese=s.g_chinese;
			stu[i].g_math=s.g_math;
			stu[i].g_english=s.g_english;
			puts("修改成功!");
			puts("---------------------------");
			rank();								//更新排名
			any();
			return;
		}
	}
}
//修改学生信息的界面
void modify(void)
{
	int i=0;
	while(1)
	{
		i=find_id();							//先按学号搜索学生
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		paitou();
		s_infor(i);
		puts("------------------------------------------------------");
		puts("1、修改基础信息");
		puts("2、修改成绩信息");
		puts("3、退出");
		puts("------------------------------------------------------");
		printf("请输入指令:");
		switch(getch())
		{
			case '1':modify_name(i);return;
			case '2':modify_score(i);return;
			case '3':return;
		}
	}
}
//单个输入成绩
void std_inone(void)
{
	int id=0;
	char c;
	system("clear");
	printf("教师模式|欢迎 %s !\n",t1.name);
	puts("---------------------------");
	printf("请输入学号:\n");
	scanf("%d%c",&id,&c);
	puts("---------------------------");
	if(ifs_id(id))								//判断学号是否合法
	{
		return;
	}
	id=id-s_id-1;				
	if(stu[id].sex!=0)							//判断该学号是否有学生
	{
		while(1)
		{
			system("clear");
			printf("教师模式|欢迎 %s !\n",t1.name);
			puts("---------------------------");
			printf("输入语文、数学、英语成绩:\n");
			scanf("%d %d %d%c",&s.g_chinese,&s.g_math,&s.g_english,&c);
			if(s.g_chinese<0||s.g_math<0||s.g_english<0||s.g_chinese>100||s.g_math>100||s.g_english>100)
			{
				puts("无效成绩，请重输!");
				puts("---------------------------");
				any();
			}
			else
			{
				stu[id].g_chinese=s.g_chinese;
				stu[id].g_math=s.g_math;
				stu[id].g_english=s.g_english;
				puts("录入成功!");
				puts("---------------------------");
				any();
				return;
			}
		}
		
	}
	else
		puts("查无此人");
	puts("---------------------------");
	any();
	return;
}
//批量输入成绩
void std_inmore(void)
{
	char c,file[100]={};
	int id=0;
	FILE *fp=NULL;
	while(1)
	{
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("----------------------");
		printf("请输入待导入文件路径:\n");
		scanf("%s%c",file,&c);
		fp=fopen(file,"r");
		if(NULL==fp)					//判断文件是否成功打开
		{
			puts("无效路径，请重输!");
			any();
			continue;
		}
		while(fscanf(fp,"%d",&s.id)!=EOF&&fscanf(fp,"%d",&s.g_chinese)!=EOF&&fscanf(fp,"%d",&s.g_math)!=EOF&&fscanf(fp,"%d",&s.g_english)!=EOF)//循环读取
		{
			id=s.id-s_id-1;
			stu[id].id=s.id;
			stu[id].g_chinese=s.g_chinese;
			stu[id].g_math=s.g_math;
			stu[id].g_english=s.g_english;
		}
		break;
	}
	puts("导入完毕");
	puts("----------------------");
	fclose(fp);							//关闭文件
	any();
	return;
}
//录入成绩主界面
void std_in(void)
{
	while(1)
	{
		system("clear");
		printf("教师模式|欢迎 %s !\n",t1.name);
		puts("----------------------");
		puts("1、单个录入成绩");
		puts("2、批量录入成绩");
		puts("3、退出");
		puts("----------------------");
		printf("请输入指令:");
		switch(getch())
		{
			case '1':std_inone();break;
			case '2':std_inmore();break;
			case '3':return;
		}
		rank();							//更新成绩排名
	}
}
//重置学生密码
void rebuilt(void)
{
	int id=0;
	char c;
	system("clear");
	printf("教师模式|欢迎 %s !\n",t1.name);
	puts("---------------------------");
	printf("请输入学号:\n");
	scanf("%d%c",&id,&c);
	if(ifs_id(id))						//判断学号是否合法
	{
		return;
	}
	puts("---------------------------");
	id=id-s_id-1;				
	if(stu[id].sex!=0)					//判断该学号是否有学生
	{
		strcpy(stu[id].code,"123456");	//重置密码
		stu[id].count=0;				//重置登录错误次数
		puts("重置密码成功!");
		puts("---------------------------");
		any();
		return;
	}
	else
		puts("查无此人");
	puts("---------------------------");
	any();
	return;
}
//输出所有在校学生信息
void show_in(void)
{
	int i=0;
	system("clear");
	printf("教师模式|欢迎 %s !\n",t1.name);
	paitou();
	for(; i<MAX_stu; i++)
	{
		if(stu[i].sex!=0)
		{
			s_infor(i);
		}	
	}
	puts("-------------------------------------------------------");
	any();
	return;
}
//输出所有离校学生信息
void show_out(void)
{
	int i=0;
	FILE *fp=fopen("student2.txt","r");   //打开离校学生信息文件
	if(NULL==fp)						  //判断是否成功打开
	{
		puts("未发现离校学生档案!");
		any();
		return;
	}
	while(fread(&s,sizeof(s),1,fp)!=0)	  //循环读取信息
	{
		stu2[i++]=s;
	}
	fclose(fp);
	system("clear");
	printf("教师模式|欢迎 %s !\n",t1.name);//输出
	puts("------------------------------------");
	puts("姓名                 性别 离校前学号");
	puts("------------------------------------");
	for(i=0; i<MAX_stu2; i++)
	{
		if(stu2[i].sex!=0)
		{
			printf("%s",stu2[i].name);
			spacey(stu2[i].name);
			printf(" %s   %d\n",stu2[i].sex=='w'?"女":"男",stu2[i].id);
		}
	}
	puts("------------------------------------");
	any();
	return;
}
//保存学生信息
void save_s(void)
{
	FILE *fp=fopen("student.txt","w");//打开离校学生信息文件，'w'模式顺便清空方便写入
	int i=0;
	if(NULL==fp)
	{
		puts("未发现学生档案!");
		any();
		return;
	}
	for( i=0; i<MAX_stu; i++)		//将结构体stu中有效的信息写入文件（sex!=0）
	{
		if(stu[i].sex!=0)
			fwrite(&stu[i],sizeof(s),1,fp);
	}
	fclose(fp);
/*	if(stu2[0].sex!=0)
	{
		fp=fopen("student2.txt","w");
		if(NULL==fp)
		{
			puts("未发现离校学生档案!");
			any();
			return;
		}
		for( i=0; i<MAX_stu; i++)
		{
			fwrite(&stu2[i],sizeof(s),1,fp);
		}
		fclose(fp);
	}*/
}
