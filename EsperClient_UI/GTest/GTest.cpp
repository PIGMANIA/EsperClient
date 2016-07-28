// GTest.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <conio.h>
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include "Communication.h"


int _tmain(int argc, _TCHAR* argv[], TCHAR* envp[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	int a;
	std::cin >> a;
	
    return 0;
}

TEST(testCommunication, test)
{
	SOCKET s = socketCreate();
	sockSetting(s);
	string str;
	string ID = "authlest7", PW = "0000";
	Items item;
	item.setId(ID);
	item.setPw(PW);
	socket_send(s, "signIn", item);
	resultpacketbuffer1 = "";
	resultpacketbuffer2 = "";
	resultpacketbuffer3 = "";
	


	socket_recv(s, &str);

	EXPECT_EQ("approval", resultpacketbuffer3);
	
}

