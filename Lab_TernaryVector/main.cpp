#include <iostream>
#include "Vector.h"
#include "Menu.h"

int main() {
	Ext::TruthTable v;
	
	try{
		Menu::menu(v);
	}catch(std::exception &err){
		std::cout << "Quiting" << std::endl;
		return 0;
	}
	return 0;
}
