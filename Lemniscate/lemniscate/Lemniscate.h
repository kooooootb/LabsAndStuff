#ifndef LAB2_LEMNISCATE_H
#define LAB2_LEMNISCATE_H

#include <cmath>

const double PI = 3.1415926535897932384626433832795;

template<class T>
int getNum(T &a) {
    while(true){
        std::cin >> a;
        if(std::cin.good() == 1)
            break;
        if(std::cin.eof() == 1)
            return -1;
        std::cout << "Error, repeat:";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
    return 1;
}

namespace Prog2{
    class Lemniscate{
    private:
        double c;//Lemniscate's parameter
    public:
        //constructors:
        explicit Lemniscate(double c0 = 1);

        //setters:
        Lemniscate& setC(double c0){ c = c0; return *this; }

        //getters:
        double getC() const { return c; };

        //tasks:
        double dist(double angle) const;//расстояние до центра в зависимости от угла
        double curvAngle(double angle) const;//радиус кривизны в зависимости от угла
        double curvDist(double dist) const;//радиус кривизны в зависимости от расстояния до центра
        double areaSegm(double angle) const;//площадь сегмента в зависимости от угла
        inline double area() const{ return 2*c*c; }//площадь лемнискаты
    };
}

#endif //LAB2_LEMNISCATE_H
