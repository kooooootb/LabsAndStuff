#include "gtest/gtest.h"
#include "lib_S_1/PCB.h"

TEST(PCB, PCB_Methods) {
	Prog3_S_1::PCB p;
	
	p.createContact(false, 0, 0);
	p.createContact(true, 1, 0);
	
	for(int i = 0;i < 11;++i)
		try{
			bool b;
			i % 2 ? b = true : b = false;
			p.createContact(b,1.0,1.0);
		}catch(std::runtime_error &err){
		
		}
	//creating:
	ASSERT_ANY_THROW(p.createContact(true, 1.0, 1.0));
	ASSERT_ANY_THROW(p.input(std::cin));
	Prog3_S_1::Contact a;
	ASSERT_ANY_THROW(p.addContact(a));
	//make connections:
	ASSERT_ANY_THROW(p.makeConnection(1,1));
	ASSERT_ANY_THROW(p.makeConnection(1,3));
	p.makeConnection(1,0);
	//check correctness:
	ASSERT_EQ(p.check(1), true);
	ASSERT_EQ(p.check(4), true);
	ASSERT_ANY_THROW(p.check(-1));
	//distance:
	ASSERT_EQ(p.dist(0,1),1);
	
}

int _tmain()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
