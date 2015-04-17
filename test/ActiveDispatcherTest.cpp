// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/ActiveDispatcher.h"
#include "Poco/ActiveMethod.h"
#include "Poco/Thread.h"
#include "Poco/Event.h"
#include "Poco/Exception.h"


using Poco::ActiveDispatcher;
using Poco::ActiveMethod;
using Poco::ActiveResult;
using Poco::ActiveStarter;
using Poco::Thread;
using Poco::Event;
using Poco::Exception;


namespace
{
	class ActiveObject: public ActiveDispatcher
	{
	public:
		ActiveObject():
			testMethod(this, &ActiveObject::testMethodImpl),
			testVoid(this, &ActiveObject::testVoidImpl),
			testVoidInOut(this, &ActiveObject::testVoidInOutImpl),
			testVoidIn(this, &ActiveObject::testVoidInImpl)
		{
		}
		
		~ActiveObject()
		{
		}
		
		ActiveMethod<int, int, ActiveObject, ActiveStarter<ActiveDispatcher> > testMethod;

		ActiveMethod<void, int, ActiveObject, ActiveStarter<ActiveDispatcher> > testVoid;

		ActiveMethod<void, void, ActiveObject, ActiveStarter<ActiveDispatcher> > testVoidInOut;

		ActiveMethod<int, void, ActiveObject, ActiveStarter<ActiveDispatcher> > testVoidIn;
		
		void cont()
		{
			_continue.set();
		}
		
	protected:
		int testMethodImpl(const int& n)
		{
			if (n == 100) throw Exception("n == 100");
			_continue.wait();
			return n;
		}

		void testVoidImpl(const int& n)
		{
			if (n == 100) throw Exception("n == 100");
			_continue.wait();
		}

		void testVoidInOutImpl()
		{
			_continue.wait();
		}

		int testVoidInImpl()
		{
			_continue.wait();
			return 123;
		}
		
	private:
		Event _continue;
	};
}


TEST(DatagramSocket, testWait)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testMethod(123);
	EXPECT_TRUE (!result.available());
	activeObj.cont();
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_EQ (result.data(), 123);
	EXPECT_FALSE (result.failed());
}

TEST(DatagramSocket, testWaitInterval)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testMethod(123);
	EXPECT_TRUE (!result.available());
    EXPECT_THROW(result.wait(100), Exception);
	activeObj.cont();
	result.wait(10000);
	EXPECT_TRUE (result.available());
	EXPECT_EQ (result.data(), 123);
	EXPECT_TRUE (!result.failed());
}

TEST(DatagramSocket, testTryWait)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testMethod(123);
	EXPECT_TRUE (!result.available());
	EXPECT_TRUE (!result.tryWait(200));
	activeObj.cont();
	EXPECT_TRUE (result.tryWait(10000));
	EXPECT_TRUE (result.available());
    EXPECT_EQ(result.data(), 123);
	EXPECT_TRUE (!result.failed());
}

TEST(DatagramSocket, testFailure)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testMethod(100);
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (result.failed());
	std::string msg = result.error();
	EXPECT_TRUE (msg == "n == 100");
}

TEST(DatagramSocket, testVoid)
{
	ActiveObject activeObj;
	ActiveResult<void> result = activeObj.testVoid(123);
	EXPECT_TRUE (!result.available());
	activeObj.cont();
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (!result.failed());
}

TEST(DatagramSocket, testVoidInOut)
{
	ActiveObject activeObj;
	ActiveResult<void> result = activeObj.testVoidInOut();
	EXPECT_TRUE (!result.available());
	activeObj.cont();
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (!result.failed());
}

TEST(DatagramSocket, testVoidIn)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testVoidIn();
	EXPECT_TRUE (!result.available());
	activeObj.cont();
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (!result.failed());
    EXPECT_EQ(result.data(), 123);
}
