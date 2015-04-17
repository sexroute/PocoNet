#include <gtest/gtest.h>
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"


using Poco::Net::SocketAddress;
using Poco::Net::IPAddress;
using Poco::Net::InvalidAddressException;
using Poco::Net::HostNotFoundException;
using Poco::Net::ServiceNotFoundException;
using Poco::Net::NoAddressFoundException;
using Poco::InvalidArgumentException;


TEST(SocketAddress, testSocketAddress)
{
	SocketAddress wild;
	EXPECT_TRUE (wild.host().isWildcard());
	EXPECT_TRUE (wild.port() == 0);

	SocketAddress sa1("192.168.1.100", 100);
	EXPECT_TRUE (sa1.host().toString() == "192.168.1.100");
	EXPECT_TRUE (sa1.port() == 100);

	SocketAddress sa2("192.168.1.100", "100");
	EXPECT_TRUE (sa2.host().toString() == "192.168.1.100");
	EXPECT_TRUE (sa2.port() == 100);

#if !defined(_WIN32_WCE)
	SocketAddress sa3("192.168.1.100", "ftp");
	EXPECT_TRUE (sa3.host().toString() == "192.168.1.100");
	EXPECT_TRUE (sa3.port() == 21);
#endif

	try
	{
		SocketAddress sa3("192.168.1.100", "f00bar");
		EXPECT_FALSE("bad service name - must throw");
	}
	catch (ServiceNotFoundException&)
	{
        EXPECT_TRUE(true);
	}

	SocketAddress sa4("www.appinf.com", 80);
	EXPECT_TRUE (sa4.host().toString() == "50.57.108.29");
	EXPECT_TRUE (sa4.port() == 80);

	try
	{
		SocketAddress sa5("192.168.2.260", 80);
		EXPECT_FALSE("invalid address - must throw");
	}
	catch (HostNotFoundException&)
	{
        EXPECT_TRUE(true);
	}
	catch (NoAddressFoundException&)
	{
        EXPECT_TRUE(true);
	}

	try
	{
		SocketAddress sa6("192.168.2.120", "80000");
		EXPECT_FALSE("invalid port - must throw");
	}
	catch (ServiceNotFoundException&)
	{
        EXPECT_TRUE(true);
	}

	SocketAddress sa7("192.168.2.120:88");
	EXPECT_TRUE (sa7.host().toString() == "192.168.2.120");
	EXPECT_TRUE (sa7.port() == 88);

	SocketAddress sa8("[192.168.2.120]:88");
	EXPECT_TRUE (sa8.host().toString() == "192.168.2.120");
	EXPECT_TRUE (sa8.port() == 88);

	try
	{
		SocketAddress sa9("[192.168.2.260]");
		EXPECT_FALSE("invalid address - must throw");
	}
	catch (InvalidArgumentException&)
	{
        EXPECT_TRUE(true);
	}

	try
	{
		SocketAddress sa9("[192.168.2.260:88");
		EXPECT_FALSE("invalid address - must throw");
	}
	catch (InvalidArgumentException&)
	{
        EXPECT_TRUE(true);
	}
}


TEST(SocketAddress, testRelationals)
{
	SocketAddress sa1("192.168.1.100", 100);
    SocketAddress sa2("192.168.1.100:100");
	EXPECT_TRUE (sa1 == sa2);

    SocketAddress sa3("192.168.1.101", "99");
	EXPECT_TRUE (sa2 < sa3);

	SocketAddress sa4("192.168.1.101", "102");
	EXPECT_TRUE (sa3 < sa4);
}
