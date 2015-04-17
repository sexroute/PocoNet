// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/Activity.h"
#include "Poco/Thread.h"


using Poco::Activity;
using Poco::Thread;


namespace
{
	class ActiveObject
	{
	public:
		ActiveObject(): 
			_activity(this, &ActiveObject::run),
			_count(0)
		{
		}
		
		~ActiveObject()
		{
		}
		
		Activity<ActiveObject>& activity()
		{
			return _activity;
		}
		
		Poco::UInt64 count() const
		{
			return _count;
		}

	protected:
		void run()
		{
			while (!_activity.isStopped()) 
				++_count;
		}

	private:
		Activity<ActiveObject> _activity;
		Poco::UInt64           _count;
	};
}
 

TEST(ActivityTest, testActivity)
{
	ActiveObject activeObj;
    EXPECT_TRUE(activeObj.activity().isStopped());
	activeObj.activity().start();
    EXPECT_TRUE(!activeObj.activity().isStopped());
	Thread::sleep(1000);
	EXPECT_TRUE (activeObj.activity().isRunning());
	activeObj.activity().stop();
	activeObj.activity().wait();
    EXPECT_GT(activeObj.count(), 0);
}
