#ifndef LAB3_MENU_H
#define LAB3_MENU_H

#include "PCB.h"

namespace Menu{
	void menu(Prog3_S_2::PCB &p);
	int dialog();
	void inputCon(Prog3_S_2::PCB &p);
	void printPCB(Prog3_S_2::PCB &p);
	void checkCon(Prog3_S_2::PCB &p);
	void connectCon(Prog3_S_2::PCB &p);
	void printConSingleType(Prog3_S_2::PCB &p);
	void distCon(Prog3_S_2::PCB &p);
	void printContact(Prog3_S_2::PCB &p);
	void invertPCB(Prog3_S_2::PCB &p);
	void deleteLast(Prog3_S_2::PCB &p);
	int anotherDialog();
	void anotherMenu(Prog3_S_2::PCB &p);
	void mergePCB(Prog3_S_2::PCB &p2, Prog3_S_2::PCB &p);
	void comparePCB(Prog3_S_2::PCB &p2, Prog3_S_2::PCB &p);
	void sumPCB(Prog3_S_2::PCB &p2, Prog3_S_2::PCB &p);
}

#endif //LAB3_MENU_H
