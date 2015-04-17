// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/AutoReleasePool.h"


using Poco::AutoReleasePool;


namespace
{
	class TestObj
	{
	public:
		TestObj(): _rc(1)
		{
			++_count;
		}
				
		void duplicate()
		{
			++_rc;
		}
		
		void release()
		{
			if (--_rc == 0)
				delete this;
		}
		
		int rc() const
		{
			return _rc;
		}
		
		static int count()
		{
			return _count;
		}
		
	protected:
		~TestObj()
		{
			--_count;
		}
		
	private:
		int _rc;
		static int _count;
	};
	
	int TestObj::_count = 0;
}


TEST(AutoReleasePoolTest, testAutoReleasePool)
{
	AutoReleasePool<TestObj> arp;
	arp.add(new TestObj);
	arp.add(new TestObj);
    EXPECT_TRUE(TestObj::count() == 2);
	arp.release();
    EXPECT_TRUE(TestObj::count() == 0);
}

