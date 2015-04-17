// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/AutoPtr.h"
#include "Poco/Exception.h"


using Poco::AutoPtr;
using Poco::NullPointerException;


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



TEST(AutoPtrTest, testAutoPtr)
{
	{
		AutoPtr<TestObj> ptr = new TestObj;
		EXPECT_TRUE (ptr->rc() == 1);
		AutoPtr<TestObj> ptr2 = ptr;
		EXPECT_TRUE (ptr->rc() == 2);
		ptr2 = new TestObj;
		EXPECT_TRUE (ptr->rc() == 1);
		AutoPtr<TestObj> ptr3;
		ptr3 = ptr2;
		EXPECT_TRUE (ptr2->rc() == 2);
		ptr3 = new TestObj;
		EXPECT_TRUE (ptr2->rc() == 1);
		ptr3 = ptr2;
		EXPECT_TRUE (ptr2->rc() == 2);
		EXPECT_TRUE (TestObj::count() > 0);
	}
	EXPECT_TRUE (TestObj::count() == 0);
}

TEST(AutoPtrTest, testOps)
{
	AutoPtr<TestObj> ptr1;
	EXPECT_EQ(nullptr, ptr1.get());
	TestObj* pTO1 = new TestObj;
	TestObj* pTO2 = new TestObj;
	if (pTO2 < pTO1)
	{
		TestObj* pTmp = pTO1;
		pTO1 = pTO2;
		pTO2 = pTmp;
	}
	EXPECT_TRUE (pTO1 < pTO2);
	ptr1 = pTO1;
	AutoPtr<TestObj> ptr2 = pTO2;
	AutoPtr<TestObj> ptr3 = ptr1;
	AutoPtr<TestObj> ptr4;
	EXPECT_TRUE (ptr1.get() == pTO1);
	EXPECT_TRUE (ptr1 == pTO1);
	EXPECT_TRUE (ptr2.get() == pTO2);
	EXPECT_TRUE (ptr2 == pTO2);
	EXPECT_TRUE (ptr3.get() == pTO1);
	EXPECT_TRUE (ptr3 == pTO1);
	
	EXPECT_TRUE (ptr1 == pTO1);
	EXPECT_TRUE (ptr1 != pTO2);
	EXPECT_TRUE (ptr1 < pTO2);
	EXPECT_TRUE (ptr1 <= pTO2);
	EXPECT_TRUE (ptr2 > pTO1);
	EXPECT_TRUE (ptr2 >= pTO1);
	
	EXPECT_TRUE (ptr1 == ptr3);
	EXPECT_TRUE (ptr1 != ptr2);
	EXPECT_TRUE (ptr1 < ptr2);
	EXPECT_TRUE (ptr1 <= ptr2);
	EXPECT_TRUE (ptr2 > ptr1);
	EXPECT_TRUE (ptr2 >= ptr1);
	
	ptr1 = pTO1;
	ptr2 = pTO2;
	ptr1.swap(ptr2);
	EXPECT_TRUE (ptr2.get() == pTO1);
	EXPECT_TRUE (ptr1.get() == pTO2);
		
    EXPECT_THROW(ptr4->rc(), NullPointerException);

	EXPECT_TRUE (!(ptr4 == ptr1));
	EXPECT_TRUE (!(ptr4 == ptr2));
	EXPECT_TRUE (ptr4 != ptr1);
	EXPECT_TRUE (ptr4 != ptr2);
	
	ptr4 = ptr2;
	EXPECT_TRUE (ptr4 == ptr2);
	EXPECT_TRUE (!(ptr4 != ptr2));
	
	EXPECT_TRUE (!(!ptr1));
	ptr1 = 0;
	EXPECT_TRUE (!ptr1);
}
