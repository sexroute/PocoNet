// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/UUID.h"


using Poco::UUID;


TEST(UUIDTest, testParse)
{
	UUID uuid("6ba7b810-9dad-11d1-80b4-00c04fd430c8");
	EXPECT_TRUE (uuid.toString() == "6ba7b810-9dad-11d1-80b4-00c04fd430c8");
	
	uuid.parse("6BA7B810-9DAD-11D1-80B4-00C04FD430C8");
	EXPECT_TRUE (uuid.toString() == "6ba7b810-9dad-11d1-80b4-00c04fd430c8");	

	uuid.parse("6BA7B8109DAD11D180B400C04FD430C8");
	EXPECT_TRUE (uuid.toString() == "6ba7b810-9dad-11d1-80b4-00c04fd430c8");	
}

TEST(UUIDTest, testBuffer)
{
	UUID uuid("6ba7b810-9dad-11d1-80b4-00c04fd430c8");
	char buffer[16];
	uuid.copyTo(buffer);
	UUID uuid2;
	uuid2.copyFrom(buffer);
	EXPECT_TRUE (uuid2.toString() == "6ba7b810-9dad-11d1-80b4-00c04fd430c8");	
}

TEST(UUIDTest, testCompare)
{
	UUID null;
	EXPECT_TRUE (null.isNull());
	EXPECT_TRUE (UUID::null().isNull());
	
	UUID uuid1 = null;
	UUID uuid2;
	EXPECT_TRUE (uuid1.isNull());
	EXPECT_TRUE (uuid1 == null);
	EXPECT_TRUE (!(uuid1 != null));
	EXPECT_TRUE (uuid1 >= null);
	EXPECT_TRUE (uuid1 <= null);
	EXPECT_TRUE (!(uuid1 > null));
	EXPECT_TRUE (!(uuid1 < null));
	EXPECT_TRUE (uuid1.toString() == "00000000-0000-0000-0000-000000000000");
	
	uuid1 = UUID::dns();
	EXPECT_TRUE (!uuid1.isNull());
	EXPECT_TRUE (uuid1 != null);
	EXPECT_TRUE (!(uuid1 == null));
	EXPECT_TRUE (uuid1 >= null);
	EXPECT_TRUE (!(uuid1 <= null));
	EXPECT_TRUE (uuid1 > null);
	EXPECT_TRUE (!(uuid1 < null));
	EXPECT_TRUE (uuid1.toString() == "6ba7b810-9dad-11d1-80b4-00c04fd430c8");

	EXPECT_TRUE (null != uuid1);
	EXPECT_TRUE (!(null == uuid1));
	EXPECT_TRUE (!(null >= uuid1));
	EXPECT_TRUE (null <= uuid1);
	EXPECT_TRUE (!(null > uuid1));
	EXPECT_TRUE (null < uuid1);
	
	uuid2 = uuid1;
	EXPECT_TRUE (uuid2 == uuid1);
	EXPECT_TRUE (!(uuid2 != uuid1));
	EXPECT_TRUE (uuid2 >= uuid1);
	EXPECT_TRUE (uuid2 <= uuid1);
	EXPECT_TRUE (!(uuid2 > uuid1));
	EXPECT_TRUE (!(uuid2 < uuid1));
}

TEST(UUIDTest, testVersion)
{
	UUID uuid("db4fa7e9-9e62-4597-99e0-b1ec0b59800e");
	UUID::Version v = uuid.version();
	EXPECT_TRUE (v == UUID::UUID_RANDOM);
	
	uuid.parse("6ba7b810-9dad-11d1-80b4-00c04fd430c8");
	v = uuid.version();
	EXPECT_TRUE (v == UUID::UUID_TIME_BASED);

	uuid.parse("d2ee4220-3625-11d9-9669-0800200c9a66");
	v = uuid.version();
	EXPECT_TRUE (v == UUID::UUID_TIME_BASED);

	uuid.parse("360d3652-4411-4786-bbe6-b9675b548559");
	v = uuid.version();
	EXPECT_TRUE (v == UUID::UUID_RANDOM);
}

TEST(UUIDTest, testVariant)
{
	UUID uuid("db4fa7e9-9e62-4597-99e0-b1ec0b59800e");
	int v = uuid.variant();
	EXPECT_TRUE (v == 2);
	
	uuid.parse("6ba7b810-9dad-11d1-80b4-00c04fd430c8");
	v = uuid.variant();
	EXPECT_TRUE (v == 2);

	uuid.parse("d2ee4220-3625-11d9-9669-0800200c9a66");
	v = uuid.variant();
	EXPECT_TRUE (v == 2);

	uuid.parse("360d3652-4411-4786-bbe6-b9675b548559");
	v = uuid.variant();
	EXPECT_TRUE (v == 2);
}

TEST(UUIDTest, testSwap)
{
	UUID uuid1("db4fa7e9-9e62-4597-99e0-b1ec0b59800e");
	UUID uuid2("d2ee4220-3625-11d9-9669-0800200c9a66");
	uuid1.swap(uuid2);
	EXPECT_TRUE (uuid1.toString() == "d2ee4220-3625-11d9-9669-0800200c9a66");
	EXPECT_TRUE (uuid2.toString() == "db4fa7e9-9e62-4597-99e0-b1ec0b59800e");
}

TEST(UUIDTest, testTryParse)
{
	UUID uuid;
	EXPECT_TRUE (uuid.tryParse("6BA7B810-9DAD-11D1-80B4-00C04FD430C8"));
	EXPECT_TRUE (uuid.toString() == "6ba7b810-9dad-11d1-80b4-00c04fd430c8");

	UUID notUuid;
	EXPECT_TRUE (!notUuid.tryParse("not a uuid"));
	EXPECT_TRUE (notUuid.isNull());
}