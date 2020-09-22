#include"main_t.h"
#include"teacher.h"
void main_t(void)
{
	for(;;)
	{
		switch(menu_t())
		{
			case '1':add();break;
			case '2':del();break;
			case '3':find();break;
			case '4':modify();break;
			case '5':std_in();break;
			case '6':rebuilt();break;
			case '7':show_in();break;
			case '8':show_out();break;
			case '9':{save_s();return;}
		}
	}
}
