#include"main_s.h"
#include"student.h"
//#include"change.h"
void main_s(void)
{
	for(;;)
	{
		switch(menu_s())
		{
			case '1': find_grade();break;
			case '2': change_s();break;
			case '3': show_infor();break;
			case '4': return;
		}
	}
}
