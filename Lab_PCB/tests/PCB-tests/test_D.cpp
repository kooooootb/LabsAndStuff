#include "gtest/gtest.h"
#include "lib_D/PCB.h"

Prog3_D::PCB initPCB(){
	Prog3_D::PCB p;
	
	Prog3_D::Contact 	a = {false,0,0},
			b = {true,1,1},
			c = {false,2,2},
			d = {true,3,3},
			e = {false,4,4};
	((((p += a) += b) += c) += d) += e;
	
	p.makeConnection(0,1);
	
	return p;
}

TEST(PCB, check) {
	Prog3_D::PCB p = initPCB();
	ASSERT_EQ(true, p.check(1));
	ASSERT_EQ(true, p.check(3));
	ASSERT_ANY_THROW(p.check(-1));
	ASSERT_ANY_THROW(p.check(100));
}

TEST(PCB, connect) {
	Prog3_D::PCB p = initPCB();
	
	p.makeConnection(3,4);
	Prog3_D::Contact a = {true, 3, 3};	a.index = 4;
	
	ASSERT_EQ(p[3], a );
	ASSERT_ANY_THROW(p.makeConnection(0,1));
}

TEST(PCB, select_type) {
	Prog3_D::PCB p = initPCB();
	Prog3_D::PCB test;
	Prog3_D::Contact c1 = {true, 1, 1};c1.index = 0;
	Prog3_D::Contact c2 = {true, 3, 3};
	(test += c1) += c2;
	
	ASSERT_EQ(test, p.selType(true));
}

TEST(PCB, distance) {
	Prog3_D::PCB p = initPCB();
	double near = 0.0001;
	ASSERT_NEAR(sqrt(2), p.dist(0,1), near);
}

TEST(PCB, indexation) {
	Prog3_D::PCB p = initPCB();
	Prog3_D::Contact c = {false, 4, 4};
	ASSERT_EQ(p[4], c);
	Prog3_D::Contact a = {true,10,10};
	p[4] = a;
	ASSERT_EQ(a,p[4]);
}

TEST(PCB, inverse) {
	Prog3_D::PCB p = initPCB();
	Prog3_D::PCB p1;
	Prog3_D::Contact 	a = {true,0,0},
			b = {false,1,1},
			c = {true,2,2},
			d = {false,3,3},
			e = {true,4,4};a.index = 1;b.index = 0;
	((((p1 += a) += b) += c) += d) += e;
	ASSERT_EQ(-p,p1);
}

TEST(PCB, deleteLast) {
	Prog3_D::PCB p = initPCB(), pcopy(p), p2 = initPCB();
	
	Prog3_D::PCB p1;
	Prog3_D::Contact 	a = {false,0,0},
			b = {true,1,1},
			c = {false,2,2},
			d = {true,3,3};a.index = 1;b.index = 0;
	(((p1 += a) += b) += c) += d;
	
	ASSERT_EQ(p--,pcopy);
	ASSERT_EQ(p,p1);
	ASSERT_EQ(--p2,p1);
}

TEST(PCB, summarize) {
	Prog3_D::PCB p, p1, p2;
	
	Prog3_D::Contact 	a = {false,0,0},
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
	Prog3_D::PCB p1, p2;
	
	Prog3_D::Contact 	a = {false,0,0},
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
	auto *ptr = new Prog3_D::Contact[count];
	
	for(int i = 0;i < count;++i){
		ptr[i].type = (bool) i % 2;
		ptr[i].x = i;
		ptr[i].y = i;
	}
	ptr[0].index = 1;
	ptr[1].index = 0;
	
	Prog3_D::PCB pt = initPCB();
	const Prog3_D::PCB p1(pt);
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
	Prog3_D::PCB p2(p1);
	p1 == p2;
	ASSERT_EQ(ptr[0], p1[0]);
	ASSERT_ANY_THROW(p1[100]);
	ASSERT_ANY_THROW(p1[-1]);
	
	std::cout << p1;
}

TEST(PCB, constructors){
//	std::cout << "Testing move and copy constructors and assignments" << std::endl;
	Prog3_D::PCB nullPCB;
	Prog3_D::PCB constr_p = initPCB();
	Prog3_D::PCB constr_p1(constr_p);//copy
	ASSERT_EQ(constr_p, constr_p1);
	
	Prog3_D::PCB constr_p2(std::move(constr_p));//move
	ASSERT_EQ(constr_p1, constr_p2);
	ASSERT_EQ(nullPCB, constr_p);
	
//	EXPECT_DEATH(ASSERT_EQ(constr_p, constr_p1), "DEATH");
	
	Prog3_D::PCB assign_p;
	Prog3_D::PCB assign_p1;
	assign_p1 = assign_p;
	ASSERT_EQ(assign_p, assign_p1);
	
	Prog3_D::PCB assign_p2;
	assign_p2 = std::move(assign_p);
	ASSERT_EQ(assign_p1, assign_p2);
	ASSERT_EQ(nullPCB, assign_p);
	
//	EXPECT_DEATH(ASSERT_EQ(assign_p, assign_p1), "[  DEATH   ]");
//	std::cout << "Finished testing move and copy constructors and assignments" << std::endl;
}

int _tmain()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
