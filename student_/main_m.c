
#include"master.h"
#include"main_m.h"

void main_m(void)
{
	for(;;)
	{
		switch(menu_m())
		{
			case '1':rebuilt_self();break;
			case '2':rebuilt_tch();break;
			case '3':add_tch();break;
			case '4':del_tch();break;
			case '5':tch_in();break;
			case '6':tch_out();break;
			case '7':{save_t();return;}
			case '8':red();return;
		}
	}
}
