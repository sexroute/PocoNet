// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/UTF8String.h"


using Poco::UTF8;



TEST(UTF8StringTest, testCompare)
{
	std::string a1("aaaaa");
	std::string b1("bbbbb");
	
	EXPECT_TRUE (UTF8::icompare(a1, b1) < 0);

	std::string a2("aaaaa");
	std::string b2("BBBBB");
	
	EXPECT_TRUE (UTF8::icompare(a2, b2) < 0);

	std::string a3("AAAAA");
	std::string b3("bbbbb");
	
	EXPECT_TRUE (UTF8::icompare(a3, b3) < 0);

	std::string a4("aaaaa");
	std::string b4("AAAAA");
	
	EXPECT_TRUE (UTF8::icompare(a4, b4) == 0);
	
	std::string a5("AAAAA");
	std::string b5("bbbbb");
	
	EXPECT_TRUE (UTF8::icompare(a5, b5) < 0);

	std::string a6("\303\274\303\266\303\244"); // "u"o"a
	std::string b6("\303\234\303\226\303\204"); // "U"O"A
	
	EXPECT_TRUE (UTF8::icompare(a6, b6) == 0);
}

TEST(UTF8StringTest, testTransform)
{
	std::string s1("abcde");
	UTF8::toUpperInPlace(s1);
	EXPECT_TRUE (s1 == "ABCDE");

	std::string s2("aBcDe123");
	UTF8::toUpperInPlace(s2);
	EXPECT_TRUE (s2 == "ABCDE123");

	std::string s3("\303\274\303\266\303\244"); // "u"o"a
	UTF8::toUpperInPlace(s3);	
	EXPECT_TRUE (s3 == "\303\234\303\226\303\204"); // "U"O"A
	UTF8::toLowerInPlace(s3);
	EXPECT_TRUE (s3 == "\303\274\303\266\303\244"); // "u"o"a

	// a mix of invalid sequences
	std::string str = "\xC2\xE5\xF0\xF8\xE8\xED\xFB+-++";
	EXPECT_TRUE ("???" == UTF8::toLower(str));
}
