#include"master.h"
#include"main_m.h"
#include"teacher.h"
#include"change.h"
#include<stdio.h>
#include<string.h>
#include<getch.h>
#include<stdlib.h>
#include<unistd.h>

static char m_id[10]="Admin",m_pass[10]={};
int tch_num=0;
void init_m(void)
{
	int id=0;
	FILE *fp=fopen(teacher,"r");
	if(fp==NULL)
	{
		puts("未发现教师档案!");
		any();
		return;
	}
	while(fread(&t,sizeof(t),1,fp)!=0)
	{
		id=t.id-t_id-1;
		tch[id]=t;
		tch_num++;
	}
	fclose(fp);
}
void passin_m(void)
{
	char c,pass[10]="123456",passin[10]={},id[10]={};
	FILE *fp=fopen("master.txt","r+");
	if(fp==NULL)
	{
		puts("数据路径错误!");
		any();
		return;
	}
	fread(&m_pass,sizeof(m_pass),1,fp);
//	fscanf(fp,"%s",m_pass);
//	fseek(fp,-1*sizeof(m_pass),SEEK_CUR);//文件结构指针回退一个长度，为后续做准备
	fclose(fp);
	system("clear");
	puts("校长模式");
	puts("-------------------");
	while(1)
	{
		printf("请输入用户名:\n");
		scanf("%s%c",id,&c);
		printf("请输入密码:\n");
		scanf("%s%c",passin,&c);
		puts("-------------------");
		if(!strcmp(m_pass,passin)&&!strcmp(id,m_id))
		{
			if(!strcmp(passin,pass))
			{
				puts("首次登录请重置密码!");
				puts("-------------------");
				first(m_pass);//初次登录改密码
				fp=fopen("master.txt","w");
				fwrite(&m_pass,sizeof(m_pass),1,fp);
				fclose(fp);
//				fseek(fp,-1*sizeof(m_pass),SEEK_CUR);
			}
			init_m();
			main_m();
			break;
		}
		else
		{
			system("clear");
			puts("非法入侵!\n");
			sleep(1);
			puts("非法入侵!\n");
			sleep(1);
			puts("报警系统已受理!\n");
			sleep(1);
			puts("校警部队驻东校区第六集团军已出动!\n");
			sleep(1);
			puts("校警部队驻西校区第九独立装甲旅已出动!\n");
			sleep(1);
			puts("饱和火力覆盖部署完毕!\n");
			sleep(1);
			puts("信标学院人道主义关怀部门温馨提醒:\n     道路千万条，自首第一条\n     投降不及时，罪犯两行泪");
			sleep(5);
			exit(0);
		}
	}
//	fclose(fp);
	return;
}
char menu_m(void)
{
	system("clear");
	puts("欢迎 校长");
	puts("-------------------");
	puts("1、重置自身密码");
	puts("2、重置教师密码");
	puts("3、添加教师");
	puts("4、删除教师");
	puts("5、显示所有在职教师");
	puts("6、显示所有离职教师");
	puts("7、退出");
	puts("8、×××红色小按钮×××");
	puts("-------------------");
	printf("请输入指令:");
	char cmd=getch();
	return cmd;
}
void rebuilt_self(void)
{
	char c;
	FILE *fp;
	system("clear");
	puts("欢迎 校长");
	puts("-------------------");
	printf("确认重置？(Y/N)");
	while(1)
	{
		c=getch();
		if(c=='Y')
		{
			strcpy(m_pass,"123456");
			fp=fopen("master.txt","w");
			fwrite(&m_pass,sizeof(m_pass),1,fp);
			printf("\n");
			puts("-------------------");
			puts("重置成功!");
			puts("-------------------");
			any();
			break;
		}
		if(c=='N')	return;
	}
	fclose(fp);
}
void rebuilt_tch(void)
{
	int id=0;
	char c;
	system("clear");
	puts("欢迎 校长");
	puts("-------------------");
	printf("请输入工号:\n");
	scanf("%d%c",&id,&c);
	id=id%2019-1;				
	if(tch[id].sex!=0)
	{
		strcpy(tch[id].pass,"123456");
		tch[id].n=0;
//		printf("%d %d",tch[0].n,id);
		puts("-------------------");
		puts("重置密码成功!");
		puts("-------------------");
		any();
		return;
	}
	else
	{
		puts("-------------------");
		puts("查无此人");
		puts("-------------------");
	}
	any();
	return;
}
//添加教师
void add_tchone(void)
{
	if(tch_num>=MAX_tch)
	{
		puts("教师已满!");
		any();
		return;
	}
	int i=0;
	char c;
	while(tch[i].sex!=0)	i++;
	while(1)
	{
		system("clear");
		puts("欢迎 校长");
		puts("-------------------");
		printf("请输入教师姓名(18字节内):\n");
		scanf("%s%c",t.name,&c);
		if(strlen(t.name)>=20)
		{
			puts("无效姓名!");
			any();
			continue;
		}
		printf("请输入教师性别:\n");
		scanf("%c%c",&t.sex,&c);
		if(t.sex!='w'&&t.sex!='m')
		{
			puts("无效姓别!");
			any();
			continue;
		}
		tch_num++;
		puts("-------------------");
		puts("添加成功!");
		puts("-------------------");
		any();
		break;
	}
	tch[i]=t;
	tch[i].id=t_id+i+1;
//初始化学生密码
	strcpy(tch[i].pass,"123456");
}
void add_tchmore(void)
{
	int i=0,n=0;
	char c,file[100]={};
	FILE *fp=NULL;
	if(tch_num>=MAX_tch)
	{
		puts("教师已满!");
		any();
		return;
	}
	while(1)
	{
		system("clear");
		puts("欢迎 校长");
		puts("--------------------------");
		printf("请输入待导入教师文件路径:\n");
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
		while(fscanf(fp,"%s",t.name)!=EOF&&fscanf(fp," %c",&t.sex)!=EOF)
		{
			while(tch[i].sex!=0)	i++;
			tch[i]=t;
			tch[i].id=t_id+i+1;
//初始化教师密码
			strcpy(tch[i].pass,"123456");
			tch_num++;
			n++;
			if(tch_num>=MAX_tch)
			{
				printf("教师已满!仅导入%d名教师\n",n);
				puts("--------------------------");
				any();
				return;
			}
		}
		break;
	}
	puts("导入完毕");
	puts("--------------------------");
	fclose(fp);
	any();
	return;
}
void add_tch(void)
{
	while(1)
	{
		system("clear");
		puts("欢迎 校长");
		puts("---------------------------");
		puts("1、单个添加");
		puts("2、批量导入");
		puts("3、退出");
		puts("---------------------------");
		printf("请输入指令:");
		switch(getch())
		{
			case '1':add_tchone();break;
			case '2':add_tchmore();break;
			case '3':return;
		}	
	}
}
//删除教师
void del_tch(void)
{
	int i=0,id1=0,id2=0;
	char c;
	FILE *fp;
	while(1)
	{
		system("clear");
		puts("欢迎 校长");
		puts("------------------------------");
		printf("请输入要删除教师的工号:\n");
		scanf("%d%c",&id1,&c);
		printf("请再次输入要删除教师的工号:\n");
		scanf("%d%c",&id2,&c);
		puts("------------------------------");
		if(id1!=id2)
		{
			puts("两次输入不相同，请重输!");
			puts("------------------------------");
			any();
		}
		else
		{
			break;
		}
	}
	i=id1%2019-1;
	if(tch[i].sex!=0)
	{
		fp=fopen(teacher2,"a");
		if(NULL==fp)
		{
			puts("未发现离校教师档案!");
			puts("------------------------------");
			any();
			return;
		}
		fwrite(&tch[i],sizeof(t),1,fp);
		fclose(fp);
		tch[i].sex=0;
		tch_num--;
		puts("已删除并转入离校教师档案。");
		puts("------------------------------");
		any();
		return;
	}
	else
		puts("查无此人!");
	puts("------------------------------");
	any();
}
//
void tch_in(void)
{
	int i=0;
	system("clear");
	puts("欢迎 校长");
	puts("----------------------------------------");
	puts("姓名                 性别  工号");
	for(; i<MAX_tch; i++)
	{
		if(tch[i].sex!=0)
		{
			printf("%s",tch[i].name);
			space(tch[i].name);
			printf(" %s    %d\n",tch[i].sex=='w'?"女":"男",tch[i].id);
		}	
	}
	puts("----------------------------------------");
	any();
	return;
}
void tch_out(void)
{
	int i=0;
	FILE *fp=fopen(teacher2,"r");
	if(NULL==fp)
	{
		puts("未发现离职教师档案!");
		any();
		return;
	}
	while(fread(&t,sizeof(t),1,fp)!=0)
	{
		tch2[i++]=t;
	}
	fclose(fp);
	system("clear");
	puts("欢迎 校长");
	puts("----------------------------------------");
	puts("姓名                 性别  离职前工号");
	for(i=0; i<MAX_tch2; i++)
	{
		if(tch2[i].sex!=0)
		{
			printf("%s",tch2[i].name);
			space(tch2[i].name);
			printf(" %s    %d\n",tch2[i].sex=='w'?"女":"男",tch2[i].id);
		}	
	}
	puts("----------------------------------------");
	any();
	return;
}
//保存教师信息
void save_t(void)
{
	FILE *fp=fopen(teacher,"w");
	int i=0;
	if(NULL==fp)
	{
		puts("未发现教师档案!");
		any();
		return;
	}
	for( i=0; i<MAX_tch; i++)
	{
		if(tch[i].sex!=0)
			fwrite(&tch[i],sizeof(t),1,fp);
	}
	fclose(fp);
}
void red(void)
{
/*	FILE *fp=NULL;
	fp=fopen(student,"w");
	fclose(fp);
	fp=fopen(student2,"w");
	fclose(fp);
	fp=fopen(teacher,"w");
	fclose(fp);
	fp=fopen(teacher2,"w");
	fclose(fp);
	fp=fopen(master,"w");
	fclose(fp);*/
	system("clear");
	for(int i=4; i>=0; i--)
	{
		printf("%d\n",i+1);
		sleep(1);
	}
	for(int i=4; i>=0; i--)
	{
		printf("\33[%d;1H \33[%d;0H",i+1,i+1);
		fflush(stdout);
		sleep(1);
	}
	printf("\33[1;1H删");
	fflush(stdout);
	sleep(1);
	printf("\33[2;3H库");
	fflush(stdout);
	sleep(1);
	printf("\33[3;5H成");
	fflush(stdout);
	sleep(1);
	printf("\33[4;7H功");
	fflush(stdout);
	sleep(3);
}
