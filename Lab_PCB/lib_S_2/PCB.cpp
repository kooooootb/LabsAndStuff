#include "PCB.h"

namespace Prog3_S_2{
	std::ostream & operator<<(std::ostream& s, const Contact& con){
		s << "\tx = " << con.x << std::endl;
		s << "\ty = " << con.y << std::endl;
		s << "\ttype = ";
		con.type ? s << "input" : s << "output" ;
		s << std::endl;
		
		return s;
	}
	
	std::ostream & operator<<(std::ostream& s, const PCB& p){
		if(p.count == 0){
			s << "PCB is clear" << std::endl;
			return s;
		}
		
		for(int i = 0;i < p.count;++i){
			s << "Contact #" << i << std::endl;
			s << p[i];
		}
		return s;
	}
	
	std::istream & operator>>(std::istream& s, PCB& p){
		double x,y;
		bool type;
		
		std::cout << "Input x coordinate:";
		if(getNum(x, s) < 0) throw std::exception();
		std::cout << "Input y coordinate:";
		if(getNum(y, s) < 0) throw std::exception();
		
		bool fl = true;
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
		
		p.createContact(type, x, y);
		
		return s;
	}
	
	void PCB::createContact(bool type, double x, double y) {
		if(count >= AZ)
			throw std::runtime_error("Array overflow");
		
		contacts[count].x = x;
		contacts[count].y = y;
		contacts[count].type = type;
		count++;
	}
	
	bool PCB::check(int num) const{
		if(num >= count || num < 0)
			throw(std::runtime_error("Contact does not exist"));
		
		Contact const &c1 = contacts[num];
		if(c1.index == -1) return true;
		
		Contact const &c2 = contacts[c1.index];
		int result = 0;
		
		if(c1.type) ++result;
		if(c2.type) ++result;
		
		if(result == 1 && c2.index == num)
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
				dest += contacts[i];
		}
		
		return dest;
	}
	
	bool PCB::operator ==(const PCB &p) const{
		if(p.count != count)
			return false;
		
		for(int i = 0;i < count;++i){
			if(contacts[i] != p.contacts[i])
				return false;
		}
		
		return true;
	}
	
	Contact & PCB::operator [](int index){
		if(index >= count || index < 0)
			throw(std::runtime_error("Contact does not exist"));
		
		return contacts[index];
	}
	
	const Contact & PCB::operator [](int index) const{
		if(index >= count || index < 0)
			throw(std::runtime_error("Contact does not exist"));
		
		return contacts[index];
	}
	
	PCB & PCB::operator -(){
		for(int i = 0;i < count;++i){
			contacts[i].type = !contacts[i].type;
		}
		
		return *this;
	}
	
	PCB & PCB::operator +=(const PCB &p){
		PCB temp(p);
		
		int savedCount = count;
		
		int possible;//количество копируемых контактов
		
		if(AZ - count < temp.count){//все не вместятся
			possible = AZ - count;
			
			for(int i = possible;i < AZ;++i){//разъединение пары невместившихся контактов
				int pairIndex = temp.contacts[i].index;//индекс пары
				if(pairIndex != -1)
					temp.contacts[pairIndex].index = -1;
			}
		}
		else possible = temp.count;//все вместятся
		
		for(int i = 0;i < possible;++i){
			if(temp.contacts[i].index != -1)
				temp.contacts[i].index += savedCount;
			*this += temp.contacts[i];
		}
	
		return *this;
	}
	
	PCB & PCB::operator +=(const Contact& cont){
		if(count >= AZ)
			throw std::runtime_error("Array overflow");
		
		contacts[count++] = cont;
		
		return *this;
	}
	
	PCB & PCB::operator --(){
		if(count == 0) return *this;
		
		int pairIndex = contacts[--count].index;
		if(pairIndex != -1)
			contacts[pairIndex].index = -1;
		
		return *this;
	}
	
	const PCB PCB::operator --(int){
		PCB copy(*this);
		
		if(count == 0) return copy;
		
		int pairIndex = contacts[--count].index;
		if(pairIndex != -1)
			contacts[pairIndex].index = -1;
	
		return copy;
	}
	
	const PCB PCB::operator +(const PCB& p) const{
		PCB temp(*this);
		
		int possible = AZ - temp.count < p.count ? AZ - temp.count : p.count;
		
		for(int i = 0;i < possible;++i)
			temp += p.contacts[i];
		
		return temp;
	}
	
	int PCB::operator <=>(const PCB& p) const{
		if(count > p.count)
			return 1;
		else if(count == p.count)
			return 0;
		else return -1;
	}
}