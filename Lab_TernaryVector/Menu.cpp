#include <fstream>
#include <algorithm>
#include "Menu.h"

namespace Menu{
	const char *msgs[] = {"1 - Load truth table from file", "2 - Create new truth table and save it into file",
						  "3 - Show output values for given input", "4 - Print table",
						  "5 - Create table of summation 2 input value groups",
						  "6 - Create table of addition 2 input value groups",
						  "0 - Exit"};
	
	void menu(Ext::TruthTable &p) {
		void (*fptr[])(Ext::TruthTable&) = {nullptr, load, save, calc, print, createSum, createAdd};
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
	
	std::ofstream openSave(){
		std::ofstream fd;
		
		const char *msg = "";
		std::cout << "Input file name:" << std::endl;
		std::string fname;
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		
		do{
			std::cout << msg;
			std::getline(std::cin, fname);
			fd.open(fname, std::ios::trunc);
			msg = "Error opening file, try again:";
		}while(!fd.is_open());
		
		return fd;
	}
	
	std::ifstream openLoad(){
		std::ifstream fd;
		
		const char *msg = "";
		std::cout << "Input file name:" << std::endl;
		std::string str;
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		
		do{
			std::cout << msg;
			std::getline(std::cin, str);
			fd.open(str);
			msg = "Error opening file, try again:";
		}while(!fd.is_open());
		
		return fd;
	}
	
	void load(Ext::TruthTable &p){
		p.erase();
		std::ifstream fd = openLoad();
		
		int count = 8;

		fd >> count;
		fd.ignore();//"\n"
		
		p.setAZ(count);
		
		for(int i = 0;i < count;++i){
			std::string line;
			std::getline(fd, line);
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
//			std::cout << "\"" << line << "\"" << std::endl;
			Prog3::Vector v(line);
			p.inputVector(v);
		}
		
		fd.close();
	}
	
	std::string intToTer(int num, int count){
		std::string str;
		while(num > 0){
			switch(num % 3){
				case 0:
					str += '0';
					break;
				case 1:
					str += '1';
					break;
				case 2:
					str += 'X';
					break;
				default:
					std::cerr << "Can't be reached" << std::endl;
					break;
			}
			num = num / 3;
		}
		
		while(str.length() < count) str += '0';
		
		std::reverse(str.begin(), str.end());
		
		return str;
	}
	
	void save(Ext::TruthTable &p){
		p.erase();
		
		int num;
		std::ofstream fd = openSave();
		
		std::cout << "Input number of input values:" << std::endl;
		if(getNum(num, std::cin) < 0) return;
		num = (int) pow(3, num);
		p.setAZ(num);
		fd << num << std::endl;
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		
		for(int i = 0;i < num;++i){
			std::cout << "Input output values for " << intToTer(i, (int) cbrt(num)) << " :";
			std::string str;
			while(true){
				std::getline(std::cin, str);
				try{
					Prog3::Vector v(str);
					p.inputVector(v);
					
					fd << v;
					
					break;
				}catch(std::invalid_argument &ia){
					std::cout << "Try again!" << std::endl;
					continue;
				}
			}
		}
		
		fd.close();
	}
	
	int TertoInt(std::string &ter){
		int res = 0;
		int mltpl = 1;
		
		for(int i = (int) ter.length() - 1;i >= 0;--i){
			int curInt = 0;
			
//			std::cout << "ter[i] = " << ter[i] << std::endl;
			
			switch(ter[i]){
				case '1':
					curInt = 1;
					break;
				case '0':
					curInt = 0;
					break;
				case 'X':
					curInt = 2;
					break;
				case 'x':
					curInt = 2;
					break;
				default:
					std::cerr << "Can't be reached" << std::endl;
					break;
			}
			
			
			res += curInt * mltpl;
			mltpl *= 3;
		}
	
		return res;
	}
	
	void calc(Ext::TruthTable &p){
		if(p.isEmpty()) {
			std::cout << "Firstly create table" << std::endl;
			return;
		}
		
		std::cout << "Input input values:" << std::endl;
		std::string str;
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		Prog3::Vector inV;
		while(true){
			std::getline(std::cin, str);
			try{
				Prog3::Vector v(str);
				inV = std::move(v);
				break;
			}catch(std::invalid_argument &ia){
				std::cout << "Try again!" << std::endl;
				continue;
			}
		}
		int val = TertoInt(str);
//		std::cout << "Dec value:" << val << std::endl;
		if((int) (log(p.getAZ()) / log(3)) != (int) str.length()){
			std::cout << "Numbers of values dont match" << std::endl;
			return;
		}
		
		std::cout << "Output for:" << inV << "Is:" << p[val];
	}
	
	void print(Ext::TruthTable &p){
		int num = p.getAZ();
		int par = (int) (log(num)/log(3));
		
		for(int i = 0;i < num;++i){
			std::cout << intToTer(i, par) << "->" << p[i];
		}
	}
	
	void createSum(Ext::TruthTable &p){
		p.erase();
		
		std::ofstream fd = openSave();
		
		int inPar;
		std::cout << "Input number of input values in each group:" << std::endl;
		if(getNum(inPar, std::cin) < 0) return;
		int inNum = (int) pow(3, inPar);
		fd << inNum * inNum << std::endl;
		
		p.setAZ(inNum * inNum);
		
		for(int i = 0;i < inNum;++i){
			for(int j = 0;j < inNum;++j){
				Prog3::Vector out(Prog3::Vector(intToTer(i, inPar)) + Prog3::Vector(intToTer(j, inPar)));
				p.inputVector(out);
				
				fd << out;
			}
		}
		
		fd.close();
	}
	
	void createAdd(Ext::TruthTable &p){
		p.erase();
		
		std::ofstream fd = openSave();
		
		int inPar;
		std::cout << "Input number of input values in each group:" << std::endl;
		if(getNum(inPar, std::cin) < 0) return;
		int inNum = (int) pow(3, inPar);
		fd << inNum * inNum << std::endl;
		
		p.setAZ(inNum * inNum);
		
		for(int i = 0;i < inNum;++i){
			for(int j = 0;j < inNum;++j){
				Prog3::Vector out(Prog3::Vector(intToTer(i, inPar)) * Prog3::Vector(intToTer(j, inPar)));
				p.inputVector(out);
				
				fd << out;
			}
		}
		
		fd.close();
	}
	
	void inputVector(Ext::TruthTable &p){
		std::cout << "Input string:" << std::endl;
		std::string str;
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		while(true){
			std::getline(std::cin, str);
			try{
				Prog3::Vector v(str);
				p.inputVector(v);
				return;
			}catch(std::invalid_argument &ia){
				std::cout << "Try again!" << std::endl;
				continue;
			}
		}
	}
	
	void printAllVectors(Ext::TruthTable &p){
		std::cout << p;
	}
	
	void printSingleVector(Ext::TruthTable &p){
		std::cout << "Input vector's index" << std::endl;
		int num;
		if(getNum(num, std::cin) < 0) throw std::exception();
		
		try{
			std::cout << p[num];
		}catch (std::runtime_error &re){
			std::cout << re.what() << std::endl;
			return;
		}
	}
	
	void sumVectors(Ext::TruthTable &p){
		int num1, num2;
		
		std::cout << "Input 1 vector's index" << std::endl;
		if(getNum(num1, std::cin) < 0) throw std::exception();
		std::cout << "Input 2 vector's index" << std::endl;
		if(getNum(num2, std::cin) < 0) throw std::exception();
		
		Prog3::Vector v;
		try{
			v = p.sum(num1, num2);
		}catch(std::runtime_error &re){
			std::cout << re.what() << std::endl;
			return;
		}
		std::cout << v;
	}
	
	void addVectors(Ext::TruthTable &p){
		int num1, num2;
		
		std::cout << "Input 1 vector's index" << std::endl;
		if(getNum(num1, std::cin) < 0) throw std::exception();
		std::cout << "Input 2 vector's index" << std::endl;
		if(getNum(num2, std::cin) < 0) throw std::exception();
		
		Prog3::Vector v;
		try{
			v = p.add(num1, num2);
		}catch(std::runtime_error &re){
			std::cout << re.what() << std::endl;
			return;
		}
		std::cout << v;
	}
	
	void compVectors(Ext::TruthTable &p){
		int num1, num2;
		
		std::cout << "Input 1 vector's index" << std::endl;
		if(getNum(num1, std::cin) < 0) throw std::exception();
		std::cout << "Input 2 vector's index" << std::endl;
		if(getNum(num2, std::cin) < 0) throw std::exception();
		
		bool res; p.comp(num1, num2);
		try{
			res = p.comp(num1, num2);
		}catch(std::runtime_error &re){
			std::cout << re.what() << std::endl;
			return;
		}
		res ? std::cout << "Vectors are equal" << std::endl : std::cout << "Vectors are not equal" << std::endl;
	}
	
	void invVector(Ext::TruthTable &p){
		int num;
		
		std::cout << "Input vector's index" << std::endl;
		if(getNum(num, std::cin) < 0) throw std::exception();
		
		try{
			p.inv(num);
		}catch(std::runtime_error &re){
			std::cout << re.what() << std::endl;
			return;
		}
	}
}