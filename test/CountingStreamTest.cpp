// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/CountingStream.h"
#include <sstream>


using Poco::CountingInputStream;
using Poco::CountingOutputStream;


TEST(CountingStreamTest, testInput)
{
	char c;
	std::istringstream istr1("foo");
	CountingInputStream ci1(istr1);
	while (ci1.good()) ci1.get(c);
	EXPECT_TRUE (ci1.lines() == 1);
	EXPECT_TRUE (ci1.chars() == 3);
	EXPECT_TRUE (ci1.pos() == 3);

	std::istringstream istr2("foo\nbar");
	CountingInputStream ci2(istr2);
	while (ci2.good()) ci2.get(c);
	EXPECT_TRUE (ci2.lines() == 2);
	EXPECT_TRUE (ci2.chars() == 7);
	EXPECT_TRUE (ci2.pos() == 3);

	std::istringstream istr3("foo\nbar\n");
	CountingInputStream ci3(istr3);
	while (ci3.good()) ci3.get(c);
	EXPECT_TRUE (ci3.lines() == 2);
	EXPECT_TRUE (ci3.chars() == 8);
	EXPECT_TRUE (ci3.pos() == 0);

	std::istringstream istr4("foo");
	CountingInputStream ci4(istr4);
	while (ci4.good()) ci4.get(c);
	ci4.addChars(10);
	ci4.addLines(2);
	ci4.addPos(3);
	EXPECT_TRUE (ci4.lines() == 1 + 2);
	EXPECT_TRUE (ci4.chars() == 3 + 10);
	EXPECT_TRUE (ci4.pos() == 3 + 3);
}

TEST(CountingStreamTest, testOutput)
{
	std::ostringstream ostr1;
	CountingOutputStream co1(ostr1);
	co1 << "foo";
	EXPECT_TRUE (ostr1.str() == "foo");
	EXPECT_TRUE (co1.lines() == 1);
	EXPECT_TRUE (co1.chars() == 3);
	EXPECT_TRUE (co1.pos() == 3);

	std::ostringstream ostr2;
	CountingOutputStream co2(ostr2);
	co2 << "foo\nbar";
	EXPECT_TRUE (ostr2.str() == "foo\nbar");
	EXPECT_TRUE (co2.lines() == 2);
	EXPECT_TRUE (co2.chars() == 7);
	EXPECT_TRUE (co2.pos() == 3);

	CountingOutputStream co3;
	co3 << "foo\nbar\n";
	EXPECT_TRUE (co3.lines() == 2);
	EXPECT_TRUE (co3.chars() == 8);
	EXPECT_TRUE (co3.pos() == 0);

	std::ostringstream ostr4;
	CountingOutputStream co4(ostr4);
	co4 << "foo";
	co4.addChars(10);
	co4.addLines(2);
	co4.addPos(3);
	EXPECT_TRUE (co4.lines() == 1 + 2);
	EXPECT_TRUE (co4.chars() == 3 + 10);
	EXPECT_TRUE (co4.pos() == 3 + 3);
}
