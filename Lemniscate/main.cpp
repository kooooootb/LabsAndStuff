#include <iostream>

#include "Lemniscate.h"

int main() {
    std::cout << "Lemniscate's equation: (x^2 + y^2)^2 = 2*c^2(x^2 - y^2)" << std::endl;
    double c;
    std::cout << "Enter c:";
    if (getNum(c) < 0)
        return 0;

    Prog2::Lemniscate l(c);

    bool fl1 = true;

    while (fl1) {
        std::cout << "Enter angle to calculate dot's distance to center:";
        double alpha, r;
        if (getNum(alpha) < 0) return 0;
        try {
            r = l.dist(alpha);
            std::cout << "distance = " << r << std::endl;
        } catch (std::invalid_argument &inv) {
            std::cout << inv.what() << std::endl;
        }

        std::cout << "Enter angle to calculate radius of curvature:";
        if (getNum(alpha) < 0) return 0;
        try {
            r = l.curvAngle(alpha);
            std::cout << "radius of curvature = " << r << std::endl;
        } catch (std::invalid_argument &inv) {
            std::cout << inv.what() << std::endl;
        }

        std::cout << "Enter distance to dot to calculate radius of curvature:";
        if (getNum(alpha) < 0) return 0;
        try {
            r = l.curvDist(alpha);
            std::cout << "radius of curvature = " << r << std::endl;
        } catch (std::invalid_argument &inv) {
            std::cout << inv.what() << std::endl;
        }

        std::cout << "Enter angle to calculate segment's area:";
        if (getNum(alpha) < 0) return 0;
        try {
            r = l.areaSegm(alpha);
            std::cout << "segment's area = " << r << std::endl;
        } catch (std::invalid_argument &inv) {
            std::cout << inv.what() << std::endl;
        }

        std::cout << "Lemniscate's area = " << l.area() << std::endl;

        std::cout << "Enter new c to continue or EOF to exit:";
        if (getNum(c) > 0)
            l.setC(c);
        else
            fl1 = false;
    }

    return 0;
}
