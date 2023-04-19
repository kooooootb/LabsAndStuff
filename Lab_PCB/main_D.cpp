#include <iostream>
#include "lib_D/PCB.h"
#include "lib_D/Menu.h"

int main() {
	Prog3_D::PCB pcb;
	
	try{
		Menu::menu(pcb);
	}catch(std::exception &err){
		std::cout << "Quiting" << std::endl;
		return 0;
	}
	
	return 0;
}
