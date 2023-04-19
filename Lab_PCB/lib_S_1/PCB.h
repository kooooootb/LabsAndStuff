#ifndef LAB3_PCB_H
#define LAB3_PCB_H

#include <iostream>
#include <cmath>

template<class T>
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

namespace Prog3_S_1{
	struct Contact{
		bool type;//тип контакта 0 - выходной, 1 - входной
		double x,y;//координаты
		int index;//номер связанного контакта, -1 -> нет соединения
		
		Contact() : index(-1), x(0), y(0), type(false) {}
	};
	
	class PCB {
	private:
		static const int AZ = 10;//количество контактов
		Contact contacts[AZ];
		int count;//количество контактов
	public:
		PCB() : count(0) {}
		
		void createContact(bool, double, double);//создание контакта с типом и координатами
		std::istream & input(std::istream&);//ввод контакта с типом и координатами*
		std::ostream & print(std::ostream&) const;//вывод платы*
		bool check(int) const;//проверка корректности двух контактов
		void addContact(const Contact & ptr);//добавить контакт(передается уже готовая структура одного контакта)
		int makeConnection(int,int);//соединить два контакта
		PCB selType(bool) const;//выделить группу контактов заданного типа(функция выводит новый объект класса с контактами одного типа)
		double dist(int,int) const;//оценка длины трассы между контактами
	};
}
// ИНДЕКСАЦИЯ унарный(инверсия контакта) бинарный (инкрем или декрем) +=
// () сранение привед типов -> один из них

#endif //LAB3_PCB_H
