#include "TruthTable.h"

namespace Ext{
	void TruthTable::expand() {
		Prog3::Vector *newarr;
		try{
			newarr = new Prog3::Vector[AZ + QUOTA];
		}catch(std::bad_alloc &ba){
			std::cerr << ba.what() << std::endl;
			throw std::exception();
		}
		
		for(int i = 0;i < AZ;++i){
			newarr[i] = vectors[i];
		}
		
		delete [] vectors;
		vectors = newarr;
		AZ += QUOTA;
	}
	
	void TruthTable::reduce() {
		AZ -= QUOTA;
		
		Prog3::Vector *newarr;
		try{
			newarr = new Prog3::Vector[AZ];
		}catch(std::bad_alloc &ba){
			std::cerr << ba.what() << std::endl;
			throw std::exception();
		}
		
		for(int i = 0;i < AZ;++i){
			newarr[i] = vectors[i];
		}
		
		delete [] vectors;
		vectors = newarr;
	}
	
	TruthTable::TruthTable() : count(0), AZ(QUOTA){
		try{
			vectors = new Prog3::Vector[QUOTA];
		}catch(std::bad_alloc &ba){
			std::cerr << ba.what() << std::endl;
			throw std::exception();
		}
	}
	
	void TruthTable::inputVector(Prog3::Vector &v) {
		vectors[count++] = v;
	}
	
	std::ostream &operator<<(std::ostream &s, const TruthTable &v) {
		for(int i = 0;i < v.count;++i){
			s << v.vectors[i];
		}
		
		return s;
	}
	
	const Prog3::Vector & TruthTable::operator[](int number) const {
		if(number >= count || number < 0)
			throw std::runtime_error("Can't find vector");
		
		return vectors[number];
	}
	
	Prog3::Vector TruthTable::sum(int n1, int n2) const {
		if(n1 >= count || n2 >= count || n2 < 0 || n1 < 0)
			throw std::runtime_error("Can't find vector");
		
		return vectors[n1] + vectors[n2];
	}
	
	Prog3::Vector TruthTable::add(int n1, int n2) const {
		if(n1 >= count || n2 >= count || n2 < 0 || n1 < 0)
			throw std::runtime_error("Can't find vector");
		
		return vectors[n1] * vectors[n2];
	}
	
	bool TruthTable::comp(int n1, int n2) const {
		if(n1 >= count || n2 >= count || n2 < 0 || n1 < 0)
			throw std::runtime_error("Can't find vector");
		
		return vectors[n1] == vectors[n2];
	}
	
	void TruthTable::inv(int number) {
		if(number >= count || number < 0)
			throw std::runtime_error("Can't find vector");
		
		vectors[number] = !vectors[number];
	}
	
	void TruthTable::erase() {
		delete [] vectors;
		
		count = 0;
		AZ = 0;
	}
	
	void TruthTable::setAZ(int num) {
		AZ = num;
		
		try{
			vectors = new Prog3::Vector[num];
		}catch(std::bad_alloc &ba) {
			std::cerr << ba.what() << std::endl;
			throw std::exception();
		}
	}
	
	bool TruthTable::isEmpty() const {
		if(count == 0) return true;
		else return false;
	}
	
	TruthTable::TruthTable(const TruthTable &p) : AZ(p.AZ), count(p.count) {
		vectors = new Prog3::Vector[p.AZ];
		
		for(int i = 0;i < count;++i){
			vectors[i] = p.vectors[i];
		}
	}
}
