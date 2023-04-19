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

namespace Prog3_S_2{
	struct Contact{
		bool type;//тип контакта 0 - выходной, 1 - входной
		double x,y;//координаты
		int index;//номер связанного контакта, -1 -> нет соединения
		
		Contact() : index(-1), x(0), y(0), type(false) {}
		Contact(bool t, double xx, double yy) : index(-1), x(xx), y(yy), type(t) {}
		
		friend std::ostream & operator<<(std::ostream&,const Contact&);
		bool operator ==(const Contact& c) const
		{
			return (x == c.x && y == c.y && type == c.type && index == c.index);
		}
	};
	
	class PCB {
	private:
		static const int AZ = 5;//количество контактов
		Contact contacts[AZ];
		int count;//количество контактов
	public:
		PCB() : count(0) {}
		PCB(int num, Contact *ptr) : count(num){//конструктор нужен только для проверки функций не меняющих состояние класса
			for(int i = 0;i < count;++i)
				contacts[i] = ptr[i];
		}
		
		void createContact(bool, double, double);//создание контакта с типом и координатами
		bool check(int) const;//проверка корректности двух контактов
		int makeConnection(int,int);//соединить два контакта
		PCB selType(bool) const;//выделить группу контактов заданного типа(функция выводит новый объект класса с контактами одного типа)
		double dist(int,int) const;//оценка длины трассы между контактами
		
		const Contact & operator [](int) const;//индексация
		Contact & operator [](int);//индексация
		PCB & operator -();//инверсия всех контактов на печатной плате
		PCB & operator +=(const PCB&);//копирует контакты из объекта-операнда в адресат до тех пор пока массив не переполнится
		PCB & operator +=(const Contact&);//копирует контакт в плату-адресат
		PCB & operator --();//удаляет последний контакт(префиксный)
		const PCB operator --(int);//удаляет последний контакт(постфиксный)
		const PCB operator +(const PCB&) const;//создает новый объект с объединением контактов адресата и операнда
		int operator <=>(const PCB&) const;//сравнение количества контактов(1 - у адресата контактов больше чем у операнда, 0 - равно, -1 - ост)
		friend std::ostream & operator<<(std::ostream&, const PCB&);//вывод платы*
		friend std::istream & operator>>(std::istream&, PCB&);//ввод контакта с типом и координатами*
		bool operator ==(const PCB&) const;
	};
}
// ИНДЕКСАЦИЯ унарный(инверсия контакта) бинарный (инкрем или декрем) +=
// () сранение привед типов -> один из них
//прверить работу на контантном классе

#endif //LAB3_PCB_H
