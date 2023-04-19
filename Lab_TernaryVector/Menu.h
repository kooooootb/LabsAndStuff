#ifndef MENU_H
#define MENU_H

#include "Vector.h"
#include "TruthTable.h"
#include <limits>

template<class T>//шаблон для ввода чисел
int getNum(T &a, std::istream &s) {
	while(true){
		s >> a;
		if(s.good() == 1)
			break;
		if(std::cin.eof() == 1)
			return -1;
		std::cout << "Error, repeat:";
		s.clear();
		s.ignore(std::numeric_limits<int>::max(), '\n');
	}
	return 1;
}

namespace Menu{
	void menu(Ext::TruthTable &v);
	int dialog();
	void inputVector(Ext::TruthTable &p);
	void printAllVectors(Ext::TruthTable &p);
	void printSingleVector(Ext::TruthTable &p);
	void sumVectors(Ext::TruthTable &p);
	void addVectors(Ext::TruthTable &p);
	void compVectors(Ext::TruthTable &p);
	void invVector(Ext::TruthTable &p);
	
	void load(Ext::TruthTable &p);
	void save(Ext::TruthTable &p);
	void calc(Ext::TruthTable &p);
	void print(Ext::TruthTable &p);
	void createSum(Ext::TruthTable &p);
	void createAdd(Ext::TruthTable &p);
}

#endif //MENU_H
