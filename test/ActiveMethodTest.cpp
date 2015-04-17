// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/ActiveMethod.h"
#include "Poco/Thread.h"
#include "Poco/Event.h"
#include "Poco/Exception.h"


using Poco::ActiveMethod;
using Poco::ActiveResult;
using Poco::Thread;
using Poco::Event;
using Poco::Exception;


namespace
{
	class ActiveObject
	{
	public:
		typedef ActiveMethod<int, int, ActiveObject>   IntIntType;
		typedef ActiveMethod<void, int, ActiveObject>  VoidIntType;
		typedef ActiveMethod<void, void, ActiveObject> VoidVoidType;
		typedef ActiveMethod<int, void, ActiveObject>  IntVoidType;

		ActiveObject():
			testMethod(this, &ActiveObject::testMethodImpl),
			testVoid(this,&ActiveObject::testVoidOutImpl),
			testVoidInOut(this,&ActiveObject::testVoidInOutImpl),
			testVoidIn(this,&ActiveObject::testVoidInImpl)
		{
		}
		
		~ActiveObject()
		{
		}
		
		IntIntType testMethod;

		VoidIntType testVoid;

		VoidVoidType testVoidInOut;

		IntVoidType testVoidIn;
		
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

		void testVoidOutImpl(const int& n)
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

TEST(ActiveMethodTest, testWait)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testMethod(123);
	EXPECT_TRUE (!result.available());
	activeObj.cont();
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (result.data() == 123);
	EXPECT_TRUE (!result.failed());
}

TEST(ActiveMethodTest, testCopy)
{
	ActiveObject activeObj;

	ActiveObject::IntIntType ii = activeObj.testMethod;
	ActiveResult<int> rii = ii(123);
	EXPECT_TRUE (!rii.available());
	activeObj.cont();
	rii.wait();
	EXPECT_TRUE (rii.available());
	EXPECT_TRUE (rii.data() == 123);
	EXPECT_TRUE (!rii.failed());

	ActiveObject::VoidIntType  vi = activeObj.testVoid;
	ActiveResult<void> rvi = vi(123);
	EXPECT_TRUE (!rvi.available());
	activeObj.cont();
	rvi.wait();
	EXPECT_TRUE (rvi.available());
	EXPECT_TRUE (!rvi.failed());

	ActiveObject::VoidVoidType vv = activeObj.testVoidInOut;
	ActiveResult<void> rvv = vv();
	EXPECT_TRUE (!rvv.available());
	activeObj.cont();
	rvv.wait();
	EXPECT_TRUE (rvv.available());
	EXPECT_TRUE (!rvv.failed());

	ActiveObject::IntVoidType  iv = activeObj.testVoidIn;
	ActiveResult<int> riv = iv();
	EXPECT_TRUE (!riv.available());
	activeObj.cont();
	riv.wait();
	EXPECT_TRUE (riv.available());
	EXPECT_TRUE (riv.data() == 123);
	EXPECT_TRUE (!riv.failed());
}

TEST(ActiveMethodTest, testWaitInterval)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testMethod(123);
	EXPECT_TRUE (!result.available());
    EXPECT_THROW(result.wait(100), Exception);
	activeObj.cont();
	result.wait(10000);
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (result.data() == 123);
	EXPECT_TRUE (!result.failed());
}

TEST(ActiveMethodTest, testTryWait)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testMethod(123);
	EXPECT_TRUE (!result.available());
	EXPECT_TRUE (!result.tryWait(200));
	activeObj.cont();
	EXPECT_TRUE (result.tryWait(10000));
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (result.data() == 123);
	EXPECT_TRUE (!result.failed());
}

TEST(ActiveMethodTest, testFailure)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testMethod(100);
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (result.failed());
	std::string msg = result.error();
	EXPECT_TRUE (msg == "n == 100");
}

TEST(ActiveMethodTest, testVoidOut)
{
	ActiveObject activeObj;
	ActiveResult<void> result = activeObj.testVoid(101);
	activeObj.cont();
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (!result.failed());
}

TEST(ActiveMethodTest, testVoidInOut)
{
	ActiveObject activeObj;
	ActiveResult<void> result = activeObj.testVoidInOut();
	activeObj.cont();
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (!result.failed());
}

TEST(ActiveMethodTest, testVoidIn)
{
	ActiveObject activeObj;
	ActiveResult<int> result = activeObj.testVoidIn();
	activeObj.cont();
	result.wait();
	EXPECT_TRUE (result.available());
	EXPECT_TRUE (!result.failed());
	EXPECT_TRUE (result.data() == 123);
}
