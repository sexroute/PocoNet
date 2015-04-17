// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/ByteOrder.h"


using Poco::ByteOrder;
using Poco::Int16;
using Poco::UInt16;
using Poco::Int32;
using Poco::UInt32;
#if defined(POCO_HAVE_INT64)
using Poco::Int64;
using Poco::UInt64;
#endif


TEST(ByteOrderTest, testByteOrderFlip)
{
	{
		Int16 norm = (Int16) 0xAABB;
		Int16 flip = ByteOrder::flipBytes(norm);
		EXPECT_TRUE (UInt16(flip) == 0xBBAA);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (flip == norm);
	}
	{
		UInt16 norm = (UInt16) 0xAABB;
		UInt16 flip = ByteOrder::flipBytes(norm);
		EXPECT_TRUE (flip == 0xBBAA);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (flip == norm);
	}
	{
		Int32 norm = 0xAABBCCDD;
		Int32 flip = ByteOrder::flipBytes(norm);
		EXPECT_TRUE (UInt32(flip) == 0xDDCCBBAA);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (flip == norm);
	}
	{
		UInt32 norm = 0xAABBCCDD;
		UInt32 flip = ByteOrder::flipBytes(norm);
		EXPECT_TRUE (flip == 0xDDCCBBAA);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (flip == norm);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = (Int64(0x8899AABB) << 32) + 0xCCDDEEFF;
		Int64 flip = ByteOrder::flipBytes(norm);
		EXPECT_TRUE (flip == (Int64(0xFFEEDDCC) << 32) + 0xBBAA9988);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (flip == norm);
	}
	{
		UInt64 norm = (UInt64(0x8899AABB) << 32) + 0xCCDDEEFF;
		UInt64 flip = ByteOrder::flipBytes(norm);
		EXPECT_TRUE (flip == (UInt64(0xFFEEDDCC) << 32) + 0xBBAA9988);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (flip == norm);
	}
	#endif
}

TEST(ByteOrderTest, testByteOrderBigEndian)
{
#if defined(POCO_ARCH_BIG_ENDIAN)
	//
	// big-endian systems
	//
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	#endif
	
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	#endif
#else
	//
	// little-endian systems
	//
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::toBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#endif
	
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::fromBigEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#endif
#endif
}

TEST(ByteOrderTest, testByteOrderLittleEndian)
{
#if defined(POCO_ARCH_LITTLE_ENDIAN)
	//
	// big-endian systems
	//
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	#endif
	
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm == flip);
	}
	#endif
#else
	//
	// little-endian systems
	//
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::toLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#endif
	
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::fromLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::fromLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::fromLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::fromLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::fromLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::fromLittleEndian(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#endif
#endif
}

TEST(ByteOrderTest, testByteOrderNetwork)
{
#if defined(POCO_ARCH_BIG_ENDIAN)
	//
	// big-endian systems
	//
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	#endif
	
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm == flip);
	}
	#endif
#else
	//
	// little-endian systems
	//
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::toNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#endif
	
	{
		Int16 norm = 4;
		Int16 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt16 norm = 4;
		UInt16 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		Int32 norm = 4;
		Int32 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt32 norm = 4;
		UInt32 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#if defined(POCO_HAVE_INT64)
	{
		Int64 norm = 4;
		Int64 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	{
		UInt64 norm = 4;
		UInt64 flip = ByteOrder::fromNetwork(norm);
		EXPECT_TRUE (norm != flip);
		flip = ByteOrder::flipBytes(flip);
		EXPECT_TRUE (norm == flip);
	}
	#endif
#endif
}
