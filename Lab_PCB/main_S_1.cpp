#include <iostream>
#include "lib_S_1/PCB.h"
#include "lib_S_1/Menu.h"

int main() {
	Prog3_S_1::PCB pcb;

	try{
		Menu::menu(pcb);
	}catch(std::exception &err){
		std::cout << "Quiting" << std::endl;
		return 0;
	}

    return 0;
}
