#include <gtest/gtest.h>
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/NetException.h"
#include <sstream>


using Poco::Net::MessageHeader;
using Poco::Net::NameValueCollection;
using Poco::Net::MessageException;


TEST(MessageHeader, testWrite)
{
	MessageHeader mh;
	mh.set("name1", "value1");
	mh.set("name2", "value2");
	mh.set("name3", "value3");
	
	std::ostringstream ostr;
	mh.write(ostr);
	std::string s = ostr.str();
	EXPECT_TRUE (s == "name1: value1\r\nname2: value2\r\nname3: value3\r\n");
}


TEST(MessageHeader, testRead1)
{
	std::string s("name1: value1\r\nname2: value2\r\nname3: value3\r\n");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 3);
	EXPECT_TRUE (mh["name1"] == "value1");
	EXPECT_TRUE (mh["name2"] == "value2");
	EXPECT_TRUE (mh["name3"] == "value3");
}


TEST(MessageHeader, testRead2)
{
	std::string s("name1: value1\nname2: value2\nname3: value3\n");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 3);
	EXPECT_TRUE (mh["name1"] == "value1");
	EXPECT_TRUE (mh["name2"] == "value2");
	EXPECT_TRUE (mh["name3"] == "value3");
}


TEST(MessageHeader, testRead3)
{
	std::string s("name1: value1\r\n");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 1);
	EXPECT_TRUE (mh["name1"] == "value1");
}


TEST(MessageHeader, testRead4)
{
	std::string s("name1: value1\r\nname2: value2\r\n\r\nsomedata");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 2);
	EXPECT_TRUE (mh["name1"] == "value1");
	EXPECT_TRUE (mh["name2"] == "value2");
	int ch = istr.get();
	EXPECT_TRUE (ch == '\r');
	ch = istr.get();
	EXPECT_TRUE (ch == '\n');
	ch = istr.get();
	EXPECT_TRUE (ch == 's');
}


TEST(MessageHeader, testRead5)
{
	std::string s("name1:\r\nname2: value2\r\nname3: value3  \r\n");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 3);
	EXPECT_TRUE (mh["name1"] == "");
	EXPECT_TRUE (mh["name2"] == "value2");
	EXPECT_TRUE (mh["name3"] == "value3");
}


TEST(MessageHeader, testReadFolding1)
{
	std::string s("name1: value1\r\nname2: value21\r\n value22\r\nname3: value3\r\n");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 3);
	EXPECT_TRUE (mh["name1"] == "value1");
	EXPECT_TRUE (mh["name2"] == "value21 value22");
	EXPECT_TRUE (mh["name3"] == "value3");
}


TEST(MessageHeader, testReadFolding2)
{
	std::string s("name1: value1\nname2: value21\n\tvalue22\nname3: value3\n");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 3);
	EXPECT_TRUE (mh["name1"] == "value1");
	EXPECT_TRUE (mh["name2"] == "value21\tvalue22");
	EXPECT_TRUE (mh["name3"] == "value3");
}


TEST(MessageHeader, testReadFolding3)
{
	std::string s("name1: value1\r\nname2: value21\r\n value22\r\n");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 2);
	EXPECT_TRUE (mh["name1"] == "value1");
	EXPECT_TRUE (mh["name2"] == "value21 value22");
}


TEST(MessageHeader, testReadFolding4)
{
	std::string s("name1: value1\r\nname2: value21\r\n value22\r\n value23");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 2);
	EXPECT_TRUE (mh["name1"] == "value1");
	EXPECT_TRUE (mh["name2"] == "value21 value22 value23");
}


TEST(MessageHeader, testReadFolding5)
{
	std::string s("name1: value1\r\nname2: value21\r\n value22\r\n value23\r\nname3: value3");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.read(istr);
	EXPECT_TRUE (mh.size() == 3);
	EXPECT_TRUE (mh["name1"] == "value1");
	EXPECT_TRUE (mh["name2"] == "value21 value22 value23");
	EXPECT_TRUE (mh["name3"] == "value3");
}


TEST(MessageHeader, testReadInvalid1)
{
	std::string s("name1: value1\r\nname2: value21\r\n value22\r\n value23\r\n");
	s.append(300, 'x');
	std::istringstream istr(s);
	MessageHeader mh;
	try
	{
		mh.read(istr);
		EXPECT_FALSE("malformed message - must throw");
	}
	catch (MessageException&)
	{
        EXPECT_TRUE(true);
	}
}


TEST(MessageHeader, testReadInvalid2)
{
	std::string s("name1: value1\r\nname2: ");
	s.append(20000, 'x');
	std::istringstream istr(s);
	MessageHeader mh;
	try
	{
		mh.read(istr);
		EXPECT_FALSE("malformed message - must throw");
	}
	catch (MessageException&)
	{
        EXPECT_TRUE(true);
	}
}


TEST(MessageHeader, testSplitElements)
{
	std::string s;
	std::vector<std::string> v;
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.empty());
	
	s = "foo";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 1);
	EXPECT_TRUE (v[0] == "foo");
	
	s = "  foo ";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 1);
	EXPECT_TRUE (v[0] == "foo");

	s = "foo,bar";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 2);
	EXPECT_TRUE (v[0] == "foo");
	EXPECT_TRUE (v[1] == "bar");
	
	s = "foo,,bar";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 2);
	EXPECT_TRUE (v[0] == "foo");
	EXPECT_TRUE (v[1] == "bar");

	MessageHeader::splitElements(s, v, false);
	EXPECT_TRUE (v.size() == 3);
	EXPECT_TRUE (v[0] == "foo");
	EXPECT_TRUE (v[1] == "");
	EXPECT_TRUE (v[2] == "bar");

	s = "foo;param=\"a,b\",bar;param=\"c,d\"";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 2);
	EXPECT_TRUE (v[0] == "foo;param=\"a,b\"");
	EXPECT_TRUE (v[1] == "bar;param=\"c,d\"");

	s = "foo; param=\"a,b\",  bar; param=\"c,d\"";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 2);
	EXPECT_TRUE (v[0] == "foo; param=\"a,b\"");
	EXPECT_TRUE (v[1] == "bar; param=\"c,d\"");
	
	s = "foo, bar, f00, baz";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 4);
	EXPECT_TRUE (v[0] == "foo");
	EXPECT_TRUE (v[1] == "bar");
	EXPECT_TRUE (v[2] == "f00");
	EXPECT_TRUE (v[3] == "baz");
	
	s = "a,b,c";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 3);
	EXPECT_TRUE (v[0] == "a");
	EXPECT_TRUE (v[1] == "b");
	EXPECT_TRUE (v[2] == "c");
	
	s = "a=\"value=\\\\\\\"foo, bar\\\\\\\"\",b=foo";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 2);
	EXPECT_TRUE (v[0] == "a=\"value=\\\"foo, bar\\\"\"");
	EXPECT_TRUE (v[1] == "b=foo");
	
	s = "a=\\\",b=\\\"";
	MessageHeader::splitElements(s, v);
	EXPECT_TRUE (v.size() == 2);
	EXPECT_TRUE (v[0] == "a=\"");
	EXPECT_TRUE (v[1] == "b=\"");
	
}


TEST(MessageHeader, testSplitParameters)
{
	std::string s;
	std::string v;
	NameValueCollection p;
	
	MessageHeader::splitParameters(s, v, p);
	EXPECT_TRUE (v.empty());
	EXPECT_TRUE (p.empty());
	
	s = "multipart/related";
	MessageHeader::splitParameters(s, v, p);
	EXPECT_TRUE (v == "multipart/related");
	EXPECT_TRUE (p.empty());
	
	s = "multipart/related; boundary=MIME_boundary_01234567";
	MessageHeader::splitParameters(s, v, p);
	EXPECT_TRUE (v == "multipart/related");
	EXPECT_TRUE (p.size() == 1);
	EXPECT_TRUE (p["boundary"] == "MIME_boundary_01234567");
	
	s = "multipart/related; boundary=\"MIME_boundary_76543210\"";
	MessageHeader::splitParameters(s, v, p);
	EXPECT_TRUE (v == "multipart/related");
	EXPECT_TRUE (p.size() == 1);
	EXPECT_TRUE (p["boundary"] == "MIME_boundary_76543210");
	
	s = "text/plain; charset=us-ascii";
	MessageHeader::splitParameters(s, v, p);
	EXPECT_TRUE (v == "text/plain");
	EXPECT_TRUE (p.size() == 1);
	EXPECT_TRUE (p["charset"] == "us-ascii");
	
	s = "value; p1=foo; p2=bar";
	MessageHeader::splitParameters(s, v, p);
	EXPECT_TRUE (v == "value");
	EXPECT_TRUE (p.size() == 2);
	EXPECT_TRUE (p["p1"] == "foo");
	EXPECT_TRUE (p["p2"] == "bar");
	
	s = "value; p1=\"foo; bar\"";
	MessageHeader::splitParameters(s, v, p);
	EXPECT_TRUE (v == "value");
	EXPECT_TRUE (p.size() == 1);
	EXPECT_TRUE (p["p1"] == "foo; bar");	

	s = "value ; p1=foo ; p2=bar ";
	MessageHeader::splitParameters(s, v, p);
	EXPECT_TRUE (v == "value");
	EXPECT_TRUE (p.size() == 2);
	EXPECT_TRUE (p["p1"] == "foo");
	EXPECT_TRUE (p["p2"] == "bar");
}


TEST(MessageHeader, testFieldLimit)
{
	std::string s("name1: value1\r\nname2: value2\r\nname3: value3\r\n");
	std::istringstream istr(s);
	MessageHeader mh;
	mh.setFieldLimit(2);
	try
	{
		mh.read(istr);
		EXPECT_FALSE("Field limit exceeded - must throw");
	}
	catch (MessageException&)
	{
        EXPECT_TRUE(true);
	}
}
