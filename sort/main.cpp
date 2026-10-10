#include "add.h"

int main()
{
	int choise = 0;

	do
	{
		main_menu();
		cin >> choise;

		switch (choise)
		{
		case 1: run_test("photos_100.txt");		break;
		case 2: run_test("photos_1000.txt");	break;
		case 3: run_test("photos_10000.txt");	break;
		case 4: 
			run_test("photos_100.txt");
			run_test("photos_1000.txt");
			run_test("photos_10000.txt");
			break;
		default: break;
		}
	}
	while (choise != 0);
}