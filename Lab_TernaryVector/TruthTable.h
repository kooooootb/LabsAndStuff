#ifndef EXTERNAL_CODE_VECTORARRAY_H
#define EXTERNAL_CODE_VECTORARRAY_H

#include "Vector.h"

namespace Ext{
	class TruthTable {
	private:
		static const int QUOTA = 5;//������ �����
		int AZ;//������� ������ ����������� �������
		Prog3::Vector* vectors;
		int count;//���������� ������� ���������
		
		void expand();//����������� AZ �� QUOTA
		void reduce();//��������� AZ �� QUOTA
	public:
		TruthTable();
		~TruthTable() { delete [] vectors; };
		
		TruthTable(const TruthTable&);
		
		void erase();
		bool isEmpty() const;
		int getAZ() { return AZ; };//���������� ���������� ������� ����������
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

//������ �������� - ������� ���������� ��� ����������� ��������
//x1 x2 x3 y1 y2
//0  0  0  0  1
//0  0  1  1  0
//...
//
//������� ������� ����������
//
//���������� �� � ����
//���������� �� �� �����
//
//������� �1�2�3
//������� y1y2

#endif //EXTERNAL_CODE_VECTORARRAY_H
