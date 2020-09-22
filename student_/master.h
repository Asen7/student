#ifndef MASTER_H
#define MASTER_H

//校长密码路径
#define master "master.txt"

//初始化教师信息
void init_m(void);
//密码判断
void passin_m(void);
//界面
char menu_m(void);
//重置自身密码
void rebuilt_self(void);
//重置教师密码
void rebuilt_tch(void);
//添加教师
void add_tchone(void);
void add_more(void);
void add_tch(void);
//删除教师
void del_tch(void);
//显示所有在校教师
void tch_in(void);
//显示所有离职教师
void tch_out(void);
//保存教师信息
void save_t(void);
//红色小按钮
void red(void);

#endif//MASTER_H
