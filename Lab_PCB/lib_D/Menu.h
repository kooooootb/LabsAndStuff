#ifndef LAB3_MENU_H
#define LAB3_MENU_H

#include "PCB.h"

namespace Menu{
	void menu(Prog3_D::PCB &p);
	int dialog();
	void inputCon(Prog3_D::PCB &p);
	void printPCB(Prog3_D::PCB &p);
	void checkCon(Prog3_D::PCB &p);
	void connectCon(Prog3_D::PCB &p);
	void printConSingleType(Prog3_D::PCB &p);
	void distCon(Prog3_D::PCB &p);
	void printContact(Prog3_D::PCB &p);
	void invertPCB(Prog3_D::PCB &p);
	void deleteLast(Prog3_D::PCB &p);
	int anotherDialog();
	void anotherMenu(Prog3_D::PCB &p);
	void mergePCB(Prog3_D::PCB &p2, Prog3_D::PCB &p);
	void comparePCB(Prog3_D::PCB &p2, Prog3_D::PCB &p);
	void sumPCB(Prog3_D::PCB &p2, Prog3_D::PCB &p);
}

#endif //LAB3_MENU_H
