// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/Clock.h"
#include "Poco/Thread.h"
#include <iostream>


using Poco::Clock;
using Poco::Thread;



TEST(ClockTest, testClock)
{
	Clock t1;
	Thread::sleep(200);
	Clock t2;
	Clock t3 = t2;
	EXPECT_TRUE (t1 != t2);
	EXPECT_TRUE (!(t1 == t2));
	EXPECT_TRUE (t2 > t1);
	EXPECT_TRUE (t2 >= t1);
	EXPECT_TRUE (!(t1 > t2));
	EXPECT_TRUE (!(t1 >= t2));
	EXPECT_TRUE (t2 == t3);
	EXPECT_TRUE (!(t2 != t3));
	EXPECT_TRUE (t2 >= t3);
	EXPECT_TRUE (t2 <= t3);
	Clock::ClockDiff d = (t2 - t1);
	EXPECT_TRUE (d >= 180000 && d <= 300000);
	
	Clock::ClockDiff acc = Clock::accuracy();
	EXPECT_TRUE (acc > 0 && acc < Clock::resolution());
	std::cout << "Clock accuracy: " << acc << std::endl;
	
	t1.swap(t2);
	EXPECT_TRUE (t1 > t2);
	t2.swap(t1);
	
	Clock now;
	Thread::sleep(201);
	EXPECT_TRUE (now.elapsed() >= 200000);
	EXPECT_TRUE (now.isElapsed(200000));
	EXPECT_TRUE (!now.isElapsed(2000000));
}
