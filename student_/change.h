#ifndef CHANGE_H
#define CHANGE_H

#ifdef DEBUG
    #define debug(...) printf(__VA_ARGS__)
#else
    #define debug(...) 
#endif

//检测有无输入
int kbhit(void);
//输出空格补齐
void space(char *name);
void spacey(char *name);
//按任意键返回
void any(void);
//首次登录修改密码
void first(char *pass);
//修改密码
void change_pass(char *pass);


#endif//CHANGE_H
