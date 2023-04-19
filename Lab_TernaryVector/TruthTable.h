#ifndef EXTERNAL_CODE_VECTORARRAY_H
#define EXTERNAL_CODE_VECTORARRAY_H

#include "Vector.h"

namespace Ext{
	class TruthTable {
	private:
		static const int QUOTA = 5;//размер квоты
		int AZ;//текущий размер размеченной области
		Prog3::Vector* vectors;
		int count;//количество занятых контактов
		
		void expand();//увеличивает AZ на QUOTA
		void reduce();//уменьшает AZ на QUOTA
	public:
		TruthTable();
		~TruthTable() { delete [] vectors; };
		
		TruthTable(const TruthTable&);
		
		void erase();
		bool isEmpty() const;
		int getAZ() { return AZ; };//количество комбинаций входных параметров
		void setAZ(int);
		void inputVector(Prog3::Vector &);
		friend std::ostream & operator<<(std::ostream&, const TruthTable&);
		const Prog3::Vector & operator[](int) const;
		Prog3::Vector sum(int,int) const;
		Prog3::Vector add(int,int) const;
		bool comp(int,int) const;
		void inv(int);
	};
}

//массив векторов - таблица истинности для логического элемента
//x1 x2 x3 y1 y2
//0  0  0  0  1
//0  0  1  1  0
//...
//
//вводишь таблицу истинности
//
//сохраняешь ее в файл
//загружаешь ее из файла
//
//вводишь х1х2х3
//выводит y1y2

#endif //EXTERNAL_CODE_VECTORARRAY_H
