#ifndef LAB3_MENU_H
#define LAB3_MENU_H

#include "PCB.h"

namespace Menu{
	void menu(Prog3_S_1::PCB &p);
	int dialog();
	void inputCon(Prog3_S_1::PCB &p);
	void printCon(Prog3_S_1::PCB &p);
	void checkCon(Prog3_S_1::PCB &p);
	void connectCon(Prog3_S_1::PCB &p);
	void printConSingleType(Prog3_S_1::PCB &p);
	void distCon(Prog3_S_1::PCB &p);
}

#endif //LAB3_MENU_H
