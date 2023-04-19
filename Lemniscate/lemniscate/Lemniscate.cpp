#include <cstring>
#include <iostream>

#include "Lemniscate.h"

namespace Prog2{
    //конструктор
    Lemniscate::Lemniscate(double c0){
        c = c0;
    }

    //задания
    double Lemniscate::dist(double angle) const{//расстояние до центра в зависимости от угла
        double cosin = cos(2 * angle);

        if(cosin < 0)
            throw std::invalid_argument("invalid angle");

        return (c * sqrt(2 * cosin));
    }

    double Lemniscate::curvAngle(double angle) const {//радиус кривизны в зависимости от угла
        double cosin = cos(2 * angle);

        if(cosin <= 0)
            throw std::invalid_argument("invalid angle");

        return (c * sqrt(2) / (3 * sqrt(cosin)));
    }

    double Lemniscate::curvDist(double dist) const{//радиус кривизны в зависимости от расстояния до центра
        if(dist <= 0 || dist > (c * sqrt(2)))
            throw std::invalid_argument("invalid distance");

        return (2 * pow(c, 2) / (3 * dist));
    }

    double Lemniscate::areaSegm(double angle) const{//площадь сегмента в зависимости от угла
        if(angle > 2*PI || angle < 0)
            throw std::invalid_argument("invalid angle");

        if(angle >= 0 && angle < PI/4){
            return (pow(c, 2) * sin(2 * angle) / 2);
        }else if(angle >= PI/4 && angle <= 3*PI/4){
            return (pow(c, 2) / 2);
        }else if(angle > 3*PI/4 && angle <= PI){
            return ((pow(c, 2)) - (pow(c, 2) * sin(2 * (PI - angle)) / 2));
        }else if(angle > PI && angle < 5*PI/4){
            return ((pow(c, 2)) + (pow(c, 2) * sin(2 * (angle - PI)) / 2));
        }else if(angle >= 5*PI/4 && angle <= 7*PI/4){
            return (pow(c, 2) * 3 / 2);
        }else return ((pow(c, 2) * 3 / 2) + (pow(c, 2) * sin(2 * (2 * PI - angle)) / 2));
    }
}