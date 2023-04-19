#include "Menu.h"

namespace Menu{
	const int ReservedOptions = 20;
	
	const char *msgs[] = {"1 - Input contact", "2 - Print current PCB", "3 - Check contact is connected correctly",
						  "4 - Connect 2 contacts", "5 - Print all contacts of chosen type", "6 - Print distance between two contacts",
						  "7 - Print contact with given index", "8 - Inverse all contact's type",
						  "9 - Delete last contact", "10 - Create another PCB and work with it", "0 - Quit"};
	
	void menu(Prog3_D::PCB &p) {
		void (*fptr[])(Prog3_D::PCB&) = {nullptr, inputCon, printPCB, checkCon, connectCon, printConSingleType, distCon,
										   printContact, invertPCB, deleteLast, anotherMenu};
		int rc = dialog();
		while(rc){
			fptr[rc](p);
			rc = dialog();
		}
	}
	
	int dialog() {
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
	
	void inputCon(Prog3_D::PCB &p){
		try{
			std::cout << "Input contact in format: x coord, y coord, type(0 for output, 1 for input)" << std::endl;
			std::cin >> p;
		}catch (std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}
	
	void printPCB(Prog3_D::PCB &p){
		std::cout << p;
	}
	
	void checkCon(Prog3_D::PCB &p){
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
	
	void connectCon(Prog3_D::PCB &p){
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
	
	void printConSingleType(Prog3_D::PCB &p){
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
		
		Prog3_D::PCB temp = p.selType(type);
		std::cout << temp;
	}
	
	void distCon(Prog3_D::PCB &p){
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
	
	void printContact(Prog3_D::PCB &p){
		int n;
		std::cout << "Enter contact's index:";
		if(getNum(n, std::cin) < 0) throw(std::exception());
		
		try{
			std::cout << p[n];
		}catch(std::runtime_error &err){
			std::cout << err.what() << std::endl;
		}
	}
	
	void invertPCB(Prog3_D::PCB &p){
		-p;
		std::cout << "New PCB:" << std::endl << p;
	}
	
	void deleteLast(Prog3_D::PCB &p){
//		std::cout << p-- << std::endl;//проверка для постфиксного оператора
		--p;
	}
	
	void anotherMenu(Prog3_D::PCB &p) {
		Prog3_D::PCB p2;
		
		void (*fptr[])(Prog3_D::PCB&) = {nullptr, inputCon, printPCB, checkCon, connectCon, printConSingleType, distCon,
										   printContact, invertPCB, deleteLast, anotherMenu};
		void (*fptr2[])(Prog3_D::PCB&, Prog3_D::PCB&) = {mergePCB, comparePCB, sumPCB};
		int rc = anotherDialog();
		while(rc){
			if(rc >= ReservedOptions){
				fptr2[rc - ReservedOptions](p2, p);
			}
			else fptr[rc](p2);
			rc = anotherDialog();
		}
	}
	
	int anotherDialog() {
		std::cout << "Working with additional PCB:" << std::endl;
		const char *msgs2[] = {"20 - Add all second PCB's contacts to primary PCB",
							   "21 - Compare numbers of contacts in primary and secondary PCB",
							   "22 - Print classes' union"};
		const int Nmsgs = sizeof(msgs) / sizeof(msgs[0]);
		const int Nmsgs2 = sizeof(msgs2) / sizeof(msgs2[0]);
		const char *errmsg = "";
		int rc;
		do {
			std::cout << errmsg;
			errmsg = "Error, repeat:\n";
			for (auto & msg : msgs)
				std::cout << msg << std::endl;
			for (auto & msg : msgs2)
				std::cout << msg << std::endl;
			std::cout << "Make your choice: ";
			if(getNum(rc, std::cin) < 0) throw(std::exception());
		} while (rc < 0 || rc >= Nmsgs && rc < ReservedOptions || rc > Nmsgs2 + ReservedOptions);
		return rc;
	}
	
	void mergePCB(Prog3_D::PCB &p2, Prog3_D::PCB &p){
		p += p2;
	}
	
	void comparePCB(Prog3_D::PCB &p2, Prog3_D::PCB &p){
		int res = p <=> p2;
		if(res > 0)
			std::cout << "Primary PCB has more contacts than second PCB";
		else if(res == 0)
			std::cout << "Numbers of contacts are equal";
		else std::cout << "Primary PCB has less contacts than second PCB";
		std::cout << std::endl;
	}
	
	void sumPCB(Prog3_D::PCB &p2, Prog3_D::PCB &p){
		Prog3_D::PCB p3(p + p2);
		
		std::cout << p3 << std::endl;
	}
}