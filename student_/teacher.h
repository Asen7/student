#ifndef TEACHER_H
#define TEACHER_H

#include <stdbool.h>
//在校教师最大数量
#define MAX_tch 100
//离校教师最大数量
#define MAX_tch2 100
//教师工号主干
#define t_id 2019*1000
//学生学号主干
#define s_id 2019*10000
//在校学生信息路径
#define student "student.txt"
//离校学生信息路径
#define student2 "student2.txt"
//在校老师信息路径
#define teacher "teacher.txt"
//离校老师信息路径
#define teacher2 "teacher2.txt"

//教师结构体声明
struct Teacher
{
	char name[20];	//姓名
	char sex;		//性别
	int id;			//工号
	char pass[10];	//密码
	int n;			//登录错误次数
};
//全局教师结构体变量声明，tch为在校教师，tch2为离校教师，t为方便赋值等操作的预设变量
extern struct Teacher tch[100],tch2[100],t;

//排头
void paitou(void);
//输出学生信息
void s_infor(int i);
//判断无效姓名
bool ifs_name(char *name);
//判断学号是否合法
bool ifs_id(int id);
//判断无效性别
bool ifs_sex(char sex);
//初始化（读取）学生数据
void init_t(void);
//登录账户密码判定
void passin_t(void);
//教师操作界面
char menu_t(void);
//添加学生（单个/批量）
void add_one(void);
void add_more(void);
void add(void);
//删除学生
void del(void);
//寻找学生（姓名/学号）
void find_name(void);
int find_id(void);
void find(void);
//修改学生（按姓名/学号）
void modify_name(int i);
void modify_score(int i);
void modify(void);
//录入成绩（单个/批量）
void std_inone(void);
void std_inmore(void);
void std_in(void);
//重置学生密码
void rebuilt(void);
//显示所有在校学生信息
void show_in(void);
//显示所有离校学生信息
void show_out(void);
//保存学生信息
void save_s(void);

#endif//TEACHER_H
