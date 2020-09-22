#ifndef STUDENT_H
#define STUDENT_H

#define MAX_stu 1000
#define MAX_stu2 1000

struct Student
{
	char name[20];
	int id;
	char sex;
	int g_chinese;
	int g_math;
	int g_english;
	int rank;
	char code[20];
	int count;
};

extern struct Student stu[1000],stu2[1000],s,s1;


void passin_s(void);
//查询成绩
void find_grade(void);
//修改密码
void change_s(void);
//查看个人信息
void show_infor(void);

char menu_s(void);

#endif//STUDENT_H
