#include "PCB.h"

namespace Prog3_S_1{
	void PCB::createContact(bool type, double x, double y) {
		if(count >= AZ)
			throw std::runtime_error("Array overflow");
		
		contacts[count].x = x;
		contacts[count].y = y;
		contacts[count].type = type;
		count++;
	}
	
	void PCB::addContact(const Contact & ptr) {
		if(count >= AZ)
			throw std::runtime_error("Array overflow");

		contacts[count++] = ptr;
	}
	
	std::istream& PCB::input(std::istream &s) {
		if(count >= AZ)
			throw(std::runtime_error("Array overflow"));
		
		double x,y;
		std::cout << "Input x coordinate:";
		if(getNum(x, s) < 0) throw std::exception();
		std::cout << "Input y coordinate:";
		if(getNum(y, s) < 0) throw std::exception();
		
		bool type, fl = true;
		int choise;
		
		do{
			std::cout << "Input 0 if contact's type is output, 1 - input:";
			if(getNum(choise, s) < 0) throw std::exception();
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
					std::cout << "Error" << std::endl;
					break;
			}
		}while(fl);
		
		createContact(type,x,y);
		
		return s;
	}
	
	std::ostream & PCB::print(std::ostream &s) const {
		if(count == 0){
			s << "PCB is clear" << std::endl;
			return s;
		}
		
		Contact const *ptr = contacts;
		for(int i = 0;i < count;++i){
			s << "Contact #" << i << std::endl;
			s << "\tx = " << ptr->x << std::endl;
			s << "\ty = " << ptr->y << std::endl;
			s << "\ttype = ";
			ptr->type ? s << "input" : s << "output" ;
			s << std::endl;
			
			++ptr;
		}
		return s;
	}
	
	bool PCB::check(int num) const{
		if(num >= count || num < 0)
			throw(std::runtime_error("Contact does not exist"));
		
		Contact const *c1 = contacts + num;
		if(c1->index == -1) return true;
		
		Contact const *c2 = contacts + c1->index;
		int result = 0;
		
		if(c1->type) ++result;
		if(c2->type) ++result;
		
		if(result == 1)
			return true;
		else return false;
	}
	
	int PCB::makeConnection(int num1, int num2) {
		if(num1 >= count || num2 >= count || num1 < 0 || num2 < 0)
			throw(std::runtime_error("Contact does not exist"));
		
		Contact *c1 = contacts + num1;
		Contact *c2 = contacts + num2;
		if(c1->index != -1 || c2->index != -1) throw(std::runtime_error("Contact is already connected"));
		
		int check = 0;
		if(c1->type) ++check;
		if(c2->type) ++check;
		
		if(check == 1){
			c1->index = num2;
			c2->index = num1;
		}
		else throw(std::runtime_error("Contacts are of the same type or matches"));
		
		return 1;
	}
	
	double PCB::dist(int num1, int num2) const{
		if(num1 >= count || num2 >= count || num1 < 0 || num2 < 0)
			throw(std::runtime_error("Contact does not exist"));
		
		Contact const *c1 = contacts + num1;
		Contact const *c2 = contacts + num2;
		if(c1->index != num2) throw(std::runtime_error("Contacts are not connected"));
		
		return sqrt(pow(c1->x - c2->x, 2) + pow(c1->y - c2->y, 2));
	}
	
	PCB PCB::selType(bool req) const{
		PCB dest;
		
		for(int i = 0;i < count;++i){
			if(contacts[i].type == req)
				dest.addContact(contacts[i]);
		}
		
		return dest;
	}
}