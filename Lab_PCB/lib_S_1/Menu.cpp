#include "Menu.h"

namespace Menu{
	void menu(Prog3_S_1::PCB &p) {
		void (*fptr[])(Prog3_S_1::PCB &p) = {nullptr, inputCon, printCon, checkCon, connectCon, printConSingleType, distCon};
		int rc = dialog();
		while(rc){
			fptr[rc](p);
			rc = dialog();
		}
	}
	
	int dialog() {
		const char *msgs[] = {"1 - Input contact", "2 - Print current PCB", "3 - Check contact is connected correctly",
							  "4 - Connect 2 contacts", "5 - Print all contacts of chosen type", "6 - Print distance between two contacts", "0 - Quit"};
		const int Nmsgs = sizeof(msgs) / sizeof(msgs[0]);
		const char *errmsg = "";
		int rc;
		do {
			std::cout << errmsg;
			errmsg = "Error, repeat:\n";
			for (auto & msg : msgs)
				std::cout << msg << std::endl;
			std::cout << "Make your choice: ";
			if(getNum(rc, std::cin) < 0) throw(std::exception());
		} while (rc < 0 || rc >= Nmsgs);
		return rc;
	}
	
	void inputCon(Prog3_S_1::PCB &p){
		try{
			p.input(std::cin);
		}catch (std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}
	
	void printCon(Prog3_S_1::PCB &p){
		p.print(std::cout);
	}
	
	void checkCon(Prog3_S_1::PCB &p){
		int n;
		std::cout << "Contact's index:";
		if(getNum(n, std::cin) < 0) throw(std::exception());
		
		bool ch;
		try{
			ch = p.check(n);
		}catch (std::runtime_error &err){
			std::cout << err.what() << std::endl;
			return;
		}
		
		if(ch)
			std::cout << "Connection is correct" << std::endl;
		else
			std::cout << "Connection is incorrect" << std::endl;
	}
	
	void connectCon(Prog3_S_1::PCB &p){
		int n1, n2;
		std::cout << "First contact's index:";
		if(getNum(n1, std::cin) < 0) throw(std::exception());
		std::cout << "Second contact's index:";
		if(getNum(n2, std::cin) < 0) throw(std::exception());
		
		try{
			p.makeConnection(n1, n2);
		}catch(std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}
	
	void printConSingleType(Prog3_S_1::PCB &p){
		int choise;
		bool fl = true, type;
		const char *msg = "Input 0 if selected type is output, 1 - input:";
		do{
			std::cout << msg;
			msg = "Error, repeat:";
			if(getNum(choise, std::cin) < 0) throw std::exception();
			switch (choise) {
				case 1:
					type = true;
					fl = false;
					break;
				case 0:
					type = false;
					fl = false;
					break;
				default:
					break;
			}
		}while(fl);
		
		Prog3_S_1::PCB temp = p.selType(type);
		temp.print(std::cout);
	}
	
	void distCon(Prog3_S_1::PCB &p){
		int n1, n2;
		std::cout << "Enter first contact's index:";
		if(getNum(n1, std::cin) < 0) throw(std::exception());
		std::cout << "Enter second contact's index:";
		if(getNum(n2, std::cin) < 0) throw(std::exception());
		
		try{
			double dist = p.dist(n1, n2);
			std::cout << "Distance = " << dist << std::endl;
		}catch(std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}
}