// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/UUIDGenerator.h"
#include "Poco/UUID.h"
#include <set>


using Poco::UUIDGenerator;
using Poco::UUID;


TEST(UUIDGeneratorTest, testTimeBased)
{
	UUIDGenerator& gen = UUIDGenerator::defaultGenerator();
	
	std::set<UUID> uuids;
	for (int i = 0; i < 1000; ++i)
	{
		UUID uuid = gen.create();
		EXPECT_TRUE (uuid.version() == UUID::UUID_TIME_BASED);
		EXPECT_TRUE (uuids.find(uuid) == uuids.end());
		uuids.insert(uuid);
	}
}

TEST(UUIDGeneratorTest, testRandom)
{
	UUIDGenerator& gen = UUIDGenerator::defaultGenerator();

	std::set<UUID> uuids;
	for (int i = 0; i < 1000; ++i)
	{
		UUID uuid = gen.createRandom();
		EXPECT_TRUE (uuid.version() == UUID::UUID_RANDOM);
		EXPECT_TRUE (uuids.find(uuid) == uuids.end());
		uuids.insert(uuid);
	}
}

TEST(UUIDGeneratorTest, testNameBased)
{
	UUIDGenerator& gen = UUIDGenerator::defaultGenerator();

	UUID uuid1 = gen.createFromName(UUID::uri(), "http://www.appinf.com/uuid");
	EXPECT_TRUE (uuid1.version() == UUID::UUID_NAME_BASED);
	EXPECT_TRUE (uuid1.variant() == 2);

	UUID uuid2 = gen.createFromName(UUID::uri(), "http://www.appinf.com/uuid2");
	EXPECT_TRUE (uuid2 != uuid1);

	UUID uuid3 = gen.createFromName(UUID::dns(), "www.appinf.com");
	EXPECT_TRUE (uuid3 != uuid1);

	UUID uuid4 = gen.createFromName(UUID::oid(), "1.3.6.1.4.1");
	EXPECT_TRUE (uuid4 != uuid1);

	UUID uuid5 = gen.createFromName(UUID::x500(), "cn=Guenter Obiltschnig, ou=People, o=Applied Informatics, c=at");
	EXPECT_TRUE (uuid5 != uuid1);

	UUID uuid6 = gen.createFromName(UUID::uri(), "http://www.appinf.com/uuid");
	EXPECT_TRUE (uuid6 == uuid1);
}
