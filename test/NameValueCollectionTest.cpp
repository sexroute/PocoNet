#include <gtest/gtest.h>
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Exception.h"


using Poco::Net::NameValueCollection;
using Poco::NotFoundException;


TEST(NameValueCollection, testNameValueCollection)
{
	NameValueCollection nvc;
	
	EXPECT_TRUE (nvc.empty());
	EXPECT_TRUE (nvc.size() == 0);
	
	nvc.set("name", "value");
	EXPECT_TRUE (!nvc.empty());
	EXPECT_TRUE (nvc["name"] == "value");
	EXPECT_TRUE (nvc["Name"] == "value");
	
	nvc.set("name2", "value2");
	EXPECT_TRUE (nvc.get("name2") == "value2");
	EXPECT_TRUE (nvc.get("NAME2") == "value2");
	
	EXPECT_TRUE (nvc.size() == 2);
	
	try
	{
		std::string value = nvc.get("name3");
		EXPECT_FALSE("not found - must throw");
	}
	catch (NotFoundException&)
	{
        EXPECT_TRUE(true);
	}

	try
	{
		std::string value = nvc["name3"];
		EXPECT_FALSE("not found - must throw");
	}
	catch (NotFoundException&)
	{
        EXPECT_TRUE(true);
	}
	
	EXPECT_TRUE (nvc.get("name", "default") == "value");
	EXPECT_TRUE (nvc.get("name3", "default") == "default");

	EXPECT_TRUE (nvc.has("name"));
	EXPECT_TRUE (nvc.has("name2"));
	EXPECT_TRUE (!nvc.has("name3"));	
	
	nvc.add("name3", "value3");
	EXPECT_TRUE (nvc.get("name3") == "value3");
	
	nvc.add("name3", "value31");
	
	NameValueCollection::ConstIterator it = nvc.find("Name3");
	EXPECT_TRUE (it != nvc.end());
	std::string v1 = it->second;
	EXPECT_TRUE (it->first == "name3");
	++it;
	EXPECT_TRUE (it != nvc.end());
	std::string v2 = it->second;
	EXPECT_TRUE (it->first == "name3");
	
	EXPECT_TRUE ((v1 == "value3" && v2 == "value31") || (v1 == "value31" && v2 == "value3"));
	
	nvc.erase("name3");
	EXPECT_TRUE (!nvc.has("name3"));
	EXPECT_TRUE (nvc.find("name3") == nvc.end());
	
	it = nvc.begin();
	EXPECT_TRUE (it != nvc.end());
	++it;
	EXPECT_TRUE (it != nvc.end());
	++it;
	EXPECT_TRUE (it == nvc.end());
	
	nvc.clear();
	EXPECT_TRUE (nvc.empty());
	
	EXPECT_TRUE (nvc.size() == 0);
}
