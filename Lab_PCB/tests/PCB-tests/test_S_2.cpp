#include "gtest/gtest.h"
#include "lib_S_2/PCB.h"

Prog3_S_2::PCB initPCB(){
	Prog3_S_2::PCB p;
	
	Prog3_S_2::Contact 	a = {false,0,0},
						b = {true,1,1},
						c = {false,2,2},
						d = {true,3,3},
						e = {false,4,4};
	((((p += a) += b) += c) += d) += e;
	
	p.makeConnection(0,1);
	
	return p;
}

TEST(PCB, check) {
	Prog3_S_2::PCB p = initPCB();
	ASSERT_EQ(true, p.check(1));
	ASSERT_EQ(true, p.check(3));
	ASSERT_ANY_THROW(p.check(-1));
	ASSERT_ANY_THROW(p.check(100));
}

TEST(PCB, connect) {
	Prog3_S_2::PCB p = initPCB();
	
	p.makeConnection(3,4);
	Prog3_S_2::Contact a = {true, 3, 3};	a.index = 4;
	
	ASSERT_EQ(p[3], a );
	ASSERT_ANY_THROW(p.makeConnection(0,1));
}

TEST(PCB, select_type) {
	Prog3_S_2::PCB p = initPCB();
	Prog3_S_2::PCB test;
	Prog3_S_2::Contact c1 = {true, 1, 1};c1.index = 0;
	Prog3_S_2::Contact c2 = {true, 3, 3};
	(test += c1) += c2;
	
	p == test;
	
	ASSERT_EQ(test, p.selType(true));
}

TEST(PCB, distance) {
	Prog3_S_2::PCB p = initPCB();
	double near = 0.0001;
	ASSERT_NEAR(sqrt(2), p.dist(0,1), near);
}

TEST(PCB, indexation) {
	Prog3_S_2::PCB p = initPCB();
	Prog3_S_2::Contact c = {false, 4, 4};
	ASSERT_EQ(p[4], c);
	Prog3_S_2::Contact a = {true, 10, 10};
	p[4] = a;
	ASSERT_EQ(p[4], a);
}

TEST(PCB, inverse) {
	Prog3_S_2::PCB p = initPCB();
	Prog3_S_2::PCB p1;
	Prog3_S_2::Contact 	a = {true,0,0},
						b = {false,1,1},
						c = {true,2,2},
						d = {false,3,3},
						e = {true,4,4};a.index = 1;b.index = 0;
	((((p1 += a) += b) += c) += d) += e;
	ASSERT_EQ(-p,p1);
}

TEST(PCB, deleteLast) {
	Prog3_S_2::PCB p = initPCB(), pcopy(p), p2 = initPCB();
	
	Prog3_S_2::PCB p1;
	Prog3_S_2::Contact 	a = {false,0,0},
			b = {true,1,1},
			c = {false,2,2},
			d = {true,3,3};a.index = 1;b.index = 0;
	(((p1 += a) += b) += c) += d;
	
	ASSERT_EQ(p--,pcopy);
	ASSERT_EQ(p,p1);
	ASSERT_EQ(--p2,p1);
}

TEST(PCB, summarize) {
	Prog3_S_2::PCB p, p1, p2;
	
	Prog3_S_2::Contact 	a = {false,0,0},
			b = {true,1,1},
			c = {false,2,2},
			d = {true,3,3},
			e = {false,4,4};
	((((p += a) += b) += c) += d) += e;
	(p1 += a) += b;
	((p2 += c) += d) += e;
	
	ASSERT_EQ(p, p1 + p2);
}

TEST(PCB, compare) {
	Prog3_S_2::PCB p1, p2;
	
	Prog3_S_2::Contact 	a = {false,0,0},
			b = {true,1,1},
			c = {false,2,2},
			d = {true,3,3},
			e = {false,4,4};
	(p1 += a) += b;
	((p2 += c) += d) += e;
	
	ASSERT_EQ(1, p2 <=> p1);
	ASSERT_EQ(-1, p1 <=> p2);
	ASSERT_EQ(0, p2 <=> p2);
}

TEST(PCB, constValues) {
	int count = 3;
	Prog3_S_2::Contact ptr[count];
	
	for(int i = 0;i < count;++i){
		ptr[i].type = (bool) i % 2;
		ptr[i].x = i;
		ptr[i].y = i;
	}
	ptr[0].index = 1;
	ptr[1].index = 0;
	
	const Prog3_S_2::PCB p1(count, ptr);
	p1.check(0);
	ASSERT_ANY_THROW(p1.check(-1));
	ASSERT_ANY_THROW(p1.check(100));
	
	p1.dist(1,0);
	p1.dist(0,1);
	ASSERT_ANY_THROW(p1.dist(1,1));
	ASSERT_ANY_THROW(p1.dist(2,2));
	
	p1.selType(true);
	p1.selType(false);
	
	p1 <=> p1;
	p1 + p1;
	p1 == p1;
	p1[0];
	ASSERT_ANY_THROW(p1[100]);
	ASSERT_ANY_THROW(p1[-1]);
	
	std::cout << p1;
}

int _tmain()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
