#include "gtest/gtest.h"
#include "Lemniscate.h"

//constructors' tests:
TEST(LemniscateConstructor, DefaultConstructor){
    Prog2::Lemniscate l1;
    ASSERT_EQ(1, l1.getC());
}

TEST(LemniscateConstructor, InitConstructors){
    Prog2::Lemniscate l2(5);
    ASSERT_EQ(5, l2.getC());
}

//other tests:
TEST(LemniscateMethods, Setters){
    Prog2::Lemniscate l;
    l.setC(2);
    ASSERT_EQ(2, l.getC());
    l.setC(-2);
    ASSERT_EQ(-2, l.getC());
}

TEST(LemniscateMethods, Parameters){
    Prog2::Lemniscate l;
    const double near = 0.00001;
    //total area:
    ASSERT_NEAR(l.getC() * l.getC() * 2, l.area(), near);
    //distance:
    ASSERT_NEAR(0, l.dist(PI / 4), near);
    ASSERT_NEAR(sqrt(2 * cos(PI / 4)), l.dist(PI / 8), near);
    ASSERT_ANY_THROW(l.dist(PI / 2));
    //Radius of curvature with angle parameter:
    ASSERT_NEAR(sqrt(2) / (3 * sqrt(cos(PI / 4))), l.curvAngle(PI / 8), near);
    ASSERT_NEAR(sqrt(2) / (3 * sqrt(cos(0))), l.curvAngle(0), near);
    ASSERT_ANY_THROW(l.curvAngle(PI / 2));
    //Radius of curvature with distance parameter:
    ASSERT_NEAR((double) 2 / 3, l.curvDist(1), near);
    ASSERT_NEAR(2 / (3 * sqrt(2)), l.curvDist(sqrt(2)), near);
    ASSERT_ANY_THROW(l.curvDist(-1));
    ASSERT_ANY_THROW(l.curvDist((double) 3));
    //area of segment:
    ASSERT_NEAR(0, l.areaSegm(0), near);
    ASSERT_NEAR(sin(PI / 4) / 2, l.areaSegm(PI / 8), near);
    ASSERT_NEAR((double) 1 / 2, l.areaSegm(PI / 4), near);
    ASSERT_NEAR((double) 1 / 2, l.areaSegm(3 * PI / 4), near);
    ASSERT_NEAR((double) 1 - sin(PI / 4) / 2, l.areaSegm(7 * PI / 8), near);
    ASSERT_NEAR((double) 1, l.areaSegm(PI), near);
    ASSERT_NEAR(sin(PI / 4) / 2 + (double) 1, l.areaSegm(9 * PI / 8), near);
    ASSERT_NEAR((double) 3 / 2, l.areaSegm(5 * PI / 4), near);
    ASSERT_NEAR((double) 3 / 2, l.areaSegm(7 * PI / 4), near);
    ASSERT_NEAR(sin(PI / 4) / 2 + (double) 3 / 2, l.areaSegm(15 * PI / 8), near);
    ASSERT_ANY_THROW(l.areaSegm(5 * PI / 2));
    ASSERT_ANY_THROW(l.areaSegm(-1));
}

int _tmain()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}