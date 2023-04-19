#include "Vector.h"

namespace Prog3 {

	//Copy constructor
	Vector::Vector(const Vector& st) :top(st.top), SZ(st.SZ){
		c = new char[SZ];
		for (int i = 0; i < top; i++)
			c[i] = st.c[i];
	}

	//Move constructor
	Vector::Vector(Vector&& st) noexcept : top(st.top) , SZ(st.SZ) , c(st.c){
		st.c = nullptr;
	}

	// Overloaded assignment operator
	Vector& Vector::operator=(const Vector& st){
		if (this != &st) {
			top = st.top;
			SZ = st.SZ;
			delete[] c;
			c = new char[SZ];
			for (int i = 0; i < top; i++)
				c[i] = st.c[i];
		}
		return *this;
	}

	// Move assignment operator
	Vector& Vector::operator=(Vector&& st) noexcept {
		int tmp = top;
		top = st.top;
		st.top = tmp;
		tmp = SZ;
		SZ = st.SZ;
		st.SZ = tmp;
		char* ptr = c;
		c = st.c;
		st.c = ptr;
		return *this;
	}

	Vector::Vector(int x) : top(0), SZ(0), c(new char[0]){
		if (x <= 0) throw std::invalid_argument("Number of X in vector need to be > 0");

		for (int i = 0; i < x; i++)
			this->set_C('X');
	}

	Vector::Vector(std::string str) :top(0), SZ(0), c(new char[0]){
		if (str.length() <= 0) throw std::out_of_range("Length of vector need to be > 0");

		for (int i = 0; i < str.length(); i++) {
			this->set_C(str[i]);
		}
	}

	void Vector::set_C(char symbol) {
		if (symbol != '0' && symbol != '1' && symbol != 'X' && symbol != 'x') throw std::invalid_argument("Invalid symbol(s)");

		if (top >= SZ) {
			SZ += QUOTA;
			char* old = c;
			c = new char[SZ];
			for (int i = 0; i < top; ++i)
				c[i] = old[i];
			delete[] old;
		}

		c[top] = symbol;
		top++;
	}

	Vector Vector::operator*(const Vector& a) { 
		Vector tmp1(*this);
		Vector tmp2(a);

		if (tmp1.top >= tmp2.top) {
			for (int i = tmp2.top; i < tmp1.top; i++) {
				tmp2.set_C('X');
			}
		}

		else {
			for (int i = tmp1.top; i < tmp2.top; i++) {
				tmp1.set_C('X');
			}
		}

		for (int i = 0; i < tmp1.top; i++) {
			if (tmp2.c[i] == '1') {
				if (tmp1.c[i] == 'X') {
					tmp2.c[i] = 'X';
				}
				else if (tmp1.c[i] == '0') {
					tmp2.c[i] = '0';
				}
			}

			else if (tmp2.c[i] == 'X') {
				if (tmp1.c[i] == '0') {
					tmp2.c[i] = '0';
				}
			}
		}

		return tmp2;
	}

	Vector Vector::operator+(const Vector &a) {
		Vector tmp1(*this);
		Vector tmp2(a);

		if (tmp1.top >= tmp2.top) {
			for (int i = tmp2.top; i < tmp1.top; i++) {
				tmp2.set_C('X');
			}
		}
		else {
			for (int i = tmp1.top; i < tmp2.top; i++) {
				tmp1.set_C('X');
			}
		}
		
		for (int i = 0; i < tmp1.top; i++) {
			if (tmp2.c[i] == '0') {
				if (tmp1.c[i] == '1') {
					tmp2.c[i] = '1';
				}
				else if (tmp1.c[i] == 'X') {
					tmp2.c[i] = 'X';
				}
			}

			else if (tmp2.c[i] == 'X') {
				if (tmp1.c[i] == '1') {
					tmp2.c[i] = '1';
				}
			}
		}

		return tmp2;
	}

	bool Vector::operator==(const Vector& a) {

		if (this->top != a.top)
			return false;

		for (int i = 0; i < this->top; i++) {
			if (this->c[i] != a.c[i])
				return false;
		}
		return true;
	}

	Vector Vector::operator!() {
		Vector tmp(*this);
		for (int i = 0; i < tmp.top; i++) {
			if (tmp.c[i] == '0')
				tmp.c[i] = '1';
			else if (tmp.c[i] == '1')
				tmp.c[i] = '0';
		}
		return tmp;
	}

	std::ostream& operator <<(std::ostream& s, const Vector& st){
		if (st.top == 0)
			s << "Vector is empty";
		else
			for (int i = 0; i < st.top; i++)
				s << st.c[i] << ' ';
		s << std::endl;
		return s;
	}

	bool Vector::Certainity() { // Analysis of certainity
		for (int i = 0; i < this->top; i++) {
			if (this->c[i] == 'X')
				return false;
		}
		return true;
	}

}
