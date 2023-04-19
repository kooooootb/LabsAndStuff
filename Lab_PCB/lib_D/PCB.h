#ifndef LAB3_PCB_H
#define LAB3_PCB_H

#include <iostream>
#include <cmath>

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

//Функции кидают std::exception при вводе EOF(для выхода из программы) или при ошибке выделения памяти; std::runtime_error при неправильных входных данных или других случаях
//Память выделяется по QUOTA контактов
//
namespace Prog3_D{
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
		static const int QUOTA = 5;//размер квоты
		int AZ;//текущее количество размеченных контактов
		Contact* contacts;
		int count;//количество занятых контактов
		
		void expand();//увеличивает AZ на QUOTA
		void reduce();//уменьшает AZ на QUOTA
	public:
		PCB();
		
		PCB(const PCB&);//копирующий конструктор
		PCB(PCB&&) noexcept;//перемещающий контруктор
		~PCB(){delete [] contacts;}
		
		void createContact(bool, double, double);//создание контакта с типом и координатами
		bool check(int) const;//проверка корректности двух контактов
		int makeConnection(int,int);//соединить два контакта
		PCB selType(bool) const;//выделить группу контактов заданного типа(функция выводит новый объект класса с контактами одного типа)
		double dist(int,int) const;//оценка длины трассы между контактами
		
		PCB & operator =(const PCB&);//копирующий
		PCB & operator =(PCB&&) noexcept;//перемещающий
		
		Contact & operator [](int);//индексация
		const Contact & operator [](int) const;//индексация
		PCB & operator -();//инверсия всех контактов на печатной плате
		PCB & operator +=(const PCB&);//копирует контакты из объекта-операнда в адресат до тех пор пока массив не переполнится
		PCB & operator +=(const Contact&);//копирует контакт в плату-адресат
		PCB & operator --();//удаляет последний контакт(префиксный)
		const PCB operator --(int);//удаляет последний контакт(постфиксный)
		PCB operator +(const PCB&) const;//создает новый объект с объединением контактов адресата и операнда
		int operator <=>(const PCB&) const;//сравнение количества контактов(1 - у адресата контактов больше чем у операнда, 0 - равно, -1 - ост)
		friend std::ostream & operator<<(std::ostream&, const PCB&);//вывод платы*
		friend std::istream & operator>>(std::istream&, PCB&);//ввод контакта с типом и координатами*
		bool operator ==(const PCB&) const;
	};
}
// ИНДЕКСАЦИЯ унарный(инверсия контакта) бинарный (инкрем или декрем) +=
// () сранение привед типов -> один из них

#endif //LAB3_PCB_H
