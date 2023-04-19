#include <iostream>
#include "lib_S_2/PCB.h"
#include "lib_S_2/Menu.h"

int main() {
	Prog3_S_2::PCB pcb;

	try{
		Menu::menu(pcb);
	}catch(std::exception &err){
		std::cout << "Quiting" << std::endl;
		return 0;
	}
	
	return 0;
}
