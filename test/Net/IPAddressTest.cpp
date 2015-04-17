#include <gtest/gtest.h>
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetException.h"


using Poco::Net::IPAddress;
using Poco::Net::InvalidAddressException;


TEST(IPAddress, testStringConv)
{
	IPAddress ia1("127.0.0.1");
	EXPECT_TRUE (ia1.family() == IPAddress::IPv4);
	EXPECT_TRUE (ia1.toString() == "127.0.0.1");
	
	IPAddress ia2("192.168.1.120");
	EXPECT_TRUE (ia2.family() == IPAddress::IPv4);
	EXPECT_TRUE (ia2.toString() == "192.168.1.120");
	
	IPAddress ia3("255.255.255.255");
	EXPECT_TRUE (ia3.family() == IPAddress::IPv4);
	EXPECT_TRUE (ia3.toString() == "255.255.255.255");

	IPAddress ia4("0.0.0.0");
	EXPECT_TRUE (ia4.family() == IPAddress::IPv4);
	EXPECT_TRUE (ia4.toString() == "0.0.0.0");
}


TEST(IPAddress, testStringConv6)
{
#ifdef POCO_HAVE_IPv6
	IPAddress ia1("1080:0:0:0:8:600:200A:425C");
	EXPECT_TRUE (ia1.family() == IPAddress::IPv6);
	EXPECT_TRUE (ia1.toString() == "1080::8:600:200A:425C");
	
	IPAddress ia2("1080::8:600:200A:425C");
	EXPECT_TRUE (ia2.family() == IPAddress::IPv6);
	EXPECT_TRUE (ia2.toString() == "1080::8:600:200A:425C");
	
	IPAddress ia3("::192.168.1.120");
	EXPECT_TRUE (ia3.family() == IPAddress::IPv6);
	EXPECT_TRUE (ia3.toString() == "::192.168.1.120");

	IPAddress ia4("::FFFF:192.168.1.120");
	EXPECT_TRUE (ia4.family() == IPAddress::IPv6);
	EXPECT_TRUE (ia4.toString() == "::FFFF:192.168.1.120");
#endif
}


TEST(IPAddress, testParse)
{
	IPAddress ip;
	EXPECT_TRUE (IPAddress::tryParse("192.168.1.120", ip));
	
	EXPECT_TRUE (!IPAddress::tryParse("192.168.1.280", ip));

	ip = IPAddress::parse("192.168.1.120");
	try
	{
		ip = IPAddress::parse("192.168.1.280");
		EXPECT_FALSE("bad address - must throw");
	}	
	catch (InvalidAddressException&)
	{
        EXPECT_TRUE(true);
	}
}


TEST(IPAddress, testClassification)
{
	IPAddress ip1("0.0.0.0"); // wildcard
	EXPECT_TRUE (ip1.isWildcard());
	EXPECT_TRUE (!ip1.isBroadcast());
	EXPECT_TRUE (!ip1.isLoopback());
	EXPECT_TRUE (!ip1.isMulticast());
	EXPECT_TRUE (!ip1.isUnicast());
	EXPECT_TRUE (!ip1.isLinkLocal());
	EXPECT_TRUE (!ip1.isSiteLocal());
	EXPECT_TRUE (!ip1.isWellKnownMC());
	EXPECT_TRUE (!ip1.isNodeLocalMC());
	EXPECT_TRUE (!ip1.isLinkLocalMC());
	EXPECT_TRUE (!ip1.isSiteLocalMC());
	EXPECT_TRUE (!ip1.isOrgLocalMC());
	EXPECT_TRUE (!ip1.isGlobalMC());
		
	IPAddress ip2("255.255.255.255"); // broadcast
	EXPECT_TRUE (!ip2.isWildcard());
	EXPECT_TRUE (ip2.isBroadcast());
	EXPECT_TRUE (!ip2.isLoopback());
	EXPECT_TRUE (!ip2.isMulticast());
	EXPECT_TRUE (!ip2.isUnicast());
	EXPECT_TRUE (!ip2.isLinkLocal());
	EXPECT_TRUE (!ip2.isSiteLocal());
	EXPECT_TRUE (!ip2.isWellKnownMC());
	EXPECT_TRUE (!ip2.isNodeLocalMC());
	EXPECT_TRUE (!ip2.isLinkLocalMC());
	EXPECT_TRUE (!ip2.isSiteLocalMC());
	EXPECT_TRUE (!ip2.isOrgLocalMC());
	EXPECT_TRUE (!ip2.isGlobalMC());
	
	IPAddress ip3("127.0.0.1"); // loopback
	EXPECT_TRUE (!ip3.isWildcard());
	EXPECT_TRUE (!ip3.isBroadcast());
	EXPECT_TRUE (ip3.isLoopback());
	EXPECT_TRUE (!ip3.isMulticast());
	EXPECT_TRUE (ip3.isUnicast());
	EXPECT_TRUE (!ip3.isLinkLocal());
	EXPECT_TRUE (!ip3.isSiteLocal());
	EXPECT_TRUE (!ip3.isWellKnownMC());
	EXPECT_TRUE (!ip3.isNodeLocalMC());
	EXPECT_TRUE (!ip3.isLinkLocalMC());
	EXPECT_TRUE (!ip3.isSiteLocalMC());
	EXPECT_TRUE (!ip3.isOrgLocalMC());
	EXPECT_TRUE (!ip3.isGlobalMC());

	IPAddress ip4("80.122.195.86"); // unicast
	EXPECT_TRUE (!ip4.isWildcard());
	EXPECT_TRUE (!ip4.isBroadcast());
	EXPECT_TRUE (!ip4.isLoopback());
	EXPECT_TRUE (!ip4.isMulticast());
	EXPECT_TRUE (ip4.isUnicast());
	EXPECT_TRUE (!ip4.isLinkLocal());
	EXPECT_TRUE (!ip4.isSiteLocal());
	EXPECT_TRUE (!ip4.isWellKnownMC());
	EXPECT_TRUE (!ip4.isNodeLocalMC());
	EXPECT_TRUE (!ip4.isLinkLocalMC());
	EXPECT_TRUE (!ip4.isSiteLocalMC());
	EXPECT_TRUE (!ip4.isOrgLocalMC());
	EXPECT_TRUE (!ip4.isGlobalMC());

	IPAddress ip5("169.254.1.20"); // link local unicast
	EXPECT_TRUE (!ip5.isWildcard());
	EXPECT_TRUE (!ip5.isBroadcast());
	EXPECT_TRUE (!ip5.isLoopback());
	EXPECT_TRUE (!ip5.isMulticast());
	EXPECT_TRUE (ip5.isUnicast());
	EXPECT_TRUE (ip5.isLinkLocal());
	EXPECT_TRUE (!ip5.isSiteLocal());
	EXPECT_TRUE (!ip5.isWellKnownMC());
	EXPECT_TRUE (!ip5.isNodeLocalMC());
	EXPECT_TRUE (!ip5.isLinkLocalMC());
	EXPECT_TRUE (!ip5.isSiteLocalMC());
	EXPECT_TRUE (!ip5.isOrgLocalMC());
	EXPECT_TRUE (!ip5.isGlobalMC());

	IPAddress ip6("192.168.1.120"); // site local unicast
	EXPECT_TRUE (!ip6.isWildcard());
	EXPECT_TRUE (!ip6.isBroadcast());
	EXPECT_TRUE (!ip6.isLoopback());
	EXPECT_TRUE (!ip6.isMulticast());
	EXPECT_TRUE (ip6.isUnicast());
	EXPECT_TRUE (!ip6.isLinkLocal());
	EXPECT_TRUE (ip6.isSiteLocal());
	EXPECT_TRUE (!ip6.isWellKnownMC());
	EXPECT_TRUE (!ip6.isNodeLocalMC());
	EXPECT_TRUE (!ip6.isLinkLocalMC());
	EXPECT_TRUE (!ip6.isSiteLocalMC());
	EXPECT_TRUE (!ip6.isOrgLocalMC());
	EXPECT_TRUE (!ip6.isGlobalMC());

	IPAddress ip7("10.0.0.138"); // site local unicast
	EXPECT_TRUE (!ip7.isWildcard());
	EXPECT_TRUE (!ip7.isBroadcast());
	EXPECT_TRUE (!ip7.isLoopback());
	EXPECT_TRUE (!ip7.isMulticast());
	EXPECT_TRUE (ip7.isUnicast());
	EXPECT_TRUE (!ip7.isLinkLocal());
	EXPECT_TRUE (ip7.isSiteLocal());
	EXPECT_TRUE (!ip7.isWellKnownMC());
	EXPECT_TRUE (!ip7.isNodeLocalMC());
	EXPECT_TRUE (!ip7.isLinkLocalMC());
	EXPECT_TRUE (!ip7.isSiteLocalMC());
	EXPECT_TRUE (!ip7.isOrgLocalMC());
	EXPECT_TRUE (!ip7.isGlobalMC());

	IPAddress ip8("172.18.1.200"); // site local unicast
	EXPECT_TRUE (!ip8.isWildcard());
	EXPECT_TRUE (!ip8.isBroadcast());
	EXPECT_TRUE (!ip8.isLoopback());
	EXPECT_TRUE (!ip8.isMulticast());
	EXPECT_TRUE (ip8.isUnicast());
	EXPECT_TRUE (!ip8.isLinkLocal());
	EXPECT_TRUE (ip8.isSiteLocal());
	EXPECT_TRUE (!ip8.isWellKnownMC());
	EXPECT_TRUE (!ip8.isNodeLocalMC());
	EXPECT_TRUE (!ip8.isLinkLocalMC());
	EXPECT_TRUE (!ip8.isSiteLocalMC());
	EXPECT_TRUE (!ip8.isOrgLocalMC());
	EXPECT_TRUE (!ip8.isGlobalMC());
}


TEST(IPAddress, testMCClassification)
{
	IPAddress ip1("224.0.0.100"); // well-known multicast
	EXPECT_TRUE (!ip1.isWildcard());
	EXPECT_TRUE (!ip1.isBroadcast());
	EXPECT_TRUE (!ip1.isLoopback());
	EXPECT_TRUE (ip1.isMulticast());
	EXPECT_TRUE (!ip1.isUnicast());
	EXPECT_TRUE (!ip1.isLinkLocal());
	EXPECT_TRUE (!ip1.isSiteLocal());
	EXPECT_TRUE (ip1.isWellKnownMC());
	EXPECT_TRUE (!ip1.isNodeLocalMC());
	EXPECT_TRUE (ip1.isLinkLocalMC()); // well known are in the range of link local
	EXPECT_TRUE (!ip1.isSiteLocalMC());
	EXPECT_TRUE (!ip1.isOrgLocalMC());
	EXPECT_TRUE (!ip1.isGlobalMC());

	IPAddress ip2("224.1.0.100"); // link local unicast
	EXPECT_TRUE (!ip2.isWildcard());
	EXPECT_TRUE (!ip2.isBroadcast());
	EXPECT_TRUE (!ip2.isLoopback());
	EXPECT_TRUE (ip2.isMulticast());
	EXPECT_TRUE (!ip2.isUnicast());
	EXPECT_TRUE (!ip2.isLinkLocal());
	EXPECT_TRUE (!ip2.isSiteLocal());
	EXPECT_TRUE (!ip2.isWellKnownMC());
	EXPECT_TRUE (!ip2.isNodeLocalMC());
	EXPECT_TRUE (ip2.isLinkLocalMC());
	EXPECT_TRUE (!ip2.isSiteLocalMC());
	EXPECT_TRUE (!ip2.isOrgLocalMC());
	EXPECT_TRUE (ip2.isGlobalMC()); // link local fall in the range of global

	IPAddress ip3("239.255.0.100"); // site local unicast
	EXPECT_TRUE (!ip3.isWildcard());
	EXPECT_TRUE (!ip3.isBroadcast());
	EXPECT_TRUE (!ip3.isLoopback());
	EXPECT_TRUE (ip3.isMulticast());
	EXPECT_TRUE (!ip3.isUnicast());
	EXPECT_TRUE (!ip3.isLinkLocal());
	EXPECT_TRUE (!ip3.isSiteLocal());
	EXPECT_TRUE (!ip3.isWellKnownMC());
	EXPECT_TRUE (!ip3.isNodeLocalMC());
	EXPECT_TRUE (!ip3.isLinkLocalMC());
	EXPECT_TRUE (ip3.isSiteLocalMC());
	EXPECT_TRUE (!ip3.isOrgLocalMC());
	EXPECT_TRUE (!ip3.isGlobalMC());

	IPAddress ip4("239.192.0.100"); // org local unicast
	EXPECT_TRUE (!ip4.isWildcard());
	EXPECT_TRUE (!ip4.isBroadcast());
	EXPECT_TRUE (!ip4.isLoopback());
	EXPECT_TRUE (ip4.isMulticast());
	EXPECT_TRUE (!ip4.isUnicast());
	EXPECT_TRUE (!ip4.isLinkLocal());
	EXPECT_TRUE (!ip4.isSiteLocal());
	EXPECT_TRUE (!ip4.isWellKnownMC());
	EXPECT_TRUE (!ip4.isNodeLocalMC());
	EXPECT_TRUE (!ip4.isLinkLocalMC());
	EXPECT_TRUE (!ip4.isSiteLocalMC());
	EXPECT_TRUE (ip4.isOrgLocalMC());
	EXPECT_TRUE (!ip4.isGlobalMC());

	IPAddress ip5("224.2.127.254"); // global unicast
	EXPECT_TRUE (!ip5.isWildcard());
	EXPECT_TRUE (!ip5.isBroadcast());
	EXPECT_TRUE (!ip5.isLoopback());
	EXPECT_TRUE (ip5.isMulticast());
	EXPECT_TRUE (!ip5.isUnicast());
	EXPECT_TRUE (!ip5.isLinkLocal());
	EXPECT_TRUE (!ip5.isSiteLocal());
	EXPECT_TRUE (!ip5.isWellKnownMC());
	EXPECT_TRUE (!ip5.isNodeLocalMC());
	EXPECT_TRUE (ip5.isLinkLocalMC()); // link local fall in the range of global
	EXPECT_TRUE (!ip5.isSiteLocalMC());
	EXPECT_TRUE (!ip5.isOrgLocalMC());
	EXPECT_TRUE (ip5.isGlobalMC());
}


TEST(IPAddress, testClassification6)
{
#ifdef POCO_HAVE_IPv6
	IPAddress ip1("::"); // wildcard
	EXPECT_TRUE (ip1.isWildcard());
	EXPECT_TRUE (!ip1.isBroadcast());
	EXPECT_TRUE (!ip1.isLoopback());
	EXPECT_TRUE (!ip1.isMulticast());
	EXPECT_TRUE (!ip1.isUnicast());
	EXPECT_TRUE (!ip1.isLinkLocal());
	EXPECT_TRUE (!ip1.isSiteLocal());
	EXPECT_TRUE (!ip1.isWellKnownMC());
	EXPECT_TRUE (!ip1.isNodeLocalMC());
	EXPECT_TRUE (!ip1.isLinkLocalMC());
	EXPECT_TRUE (!ip1.isSiteLocalMC());
	EXPECT_TRUE (!ip1.isOrgLocalMC());
	EXPECT_TRUE (!ip1.isGlobalMC());
		
	IPAddress ip3("::1"); // loopback
	EXPECT_TRUE (!ip3.isWildcard());
	EXPECT_TRUE (!ip3.isBroadcast());
	EXPECT_TRUE (ip3.isLoopback());
	EXPECT_TRUE (!ip3.isMulticast());
	EXPECT_TRUE (ip3.isUnicast());
	EXPECT_TRUE (!ip3.isLinkLocal());
	EXPECT_TRUE (!ip3.isSiteLocal());
	EXPECT_TRUE (!ip3.isWellKnownMC());
	EXPECT_TRUE (!ip3.isNodeLocalMC());
	EXPECT_TRUE (!ip3.isLinkLocalMC());
	EXPECT_TRUE (!ip3.isSiteLocalMC());
	EXPECT_TRUE (!ip3.isOrgLocalMC());
	EXPECT_TRUE (!ip3.isGlobalMC());

	IPAddress ip4("2001:0db8:85a3:0000:0000:8a2e:0370:7334"); // unicast
	EXPECT_TRUE (!ip4.isWildcard());
	EXPECT_TRUE (!ip4.isBroadcast());
	EXPECT_TRUE (!ip4.isLoopback());
	EXPECT_TRUE (!ip4.isMulticast());
	EXPECT_TRUE (ip4.isUnicast());
	EXPECT_TRUE (!ip4.isLinkLocal());
	EXPECT_TRUE (!ip4.isSiteLocal());
	EXPECT_TRUE (!ip4.isWellKnownMC());
	EXPECT_TRUE (!ip4.isNodeLocalMC());
	EXPECT_TRUE (!ip4.isLinkLocalMC());
	EXPECT_TRUE (!ip4.isSiteLocalMC());
	EXPECT_TRUE (!ip4.isOrgLocalMC());
	EXPECT_TRUE (!ip4.isGlobalMC());

	IPAddress ip5("fe80::21f:5bff:fec6:6707"); // link local unicast
	EXPECT_TRUE (!ip5.isWildcard());
	EXPECT_TRUE (!ip5.isBroadcast());
	EXPECT_TRUE (!ip5.isLoopback());
	EXPECT_TRUE (!ip5.isMulticast());
	EXPECT_TRUE (ip5.isUnicast());
	EXPECT_TRUE (ip5.isLinkLocal());
	EXPECT_TRUE (!ip5.isSiteLocal());
	EXPECT_TRUE (!ip5.isWellKnownMC());
	EXPECT_TRUE (!ip5.isNodeLocalMC());
	EXPECT_TRUE (!ip5.isLinkLocalMC());
	EXPECT_TRUE (!ip5.isSiteLocalMC());
	EXPECT_TRUE (!ip5.isOrgLocalMC());
	EXPECT_TRUE (!ip5.isGlobalMC());

	IPAddress ip10("fe80::12"); // link local unicast
	EXPECT_TRUE (!ip10.isWildcard());
	EXPECT_TRUE (!ip10.isBroadcast());
	EXPECT_TRUE (!ip10.isLoopback());
	EXPECT_TRUE (!ip10.isMulticast());
	EXPECT_TRUE (ip10.isUnicast());
	EXPECT_TRUE (ip10.isLinkLocal());
	EXPECT_TRUE (!ip10.isSiteLocal());
	EXPECT_TRUE (!ip10.isWellKnownMC());
	EXPECT_TRUE (!ip10.isNodeLocalMC());
	EXPECT_TRUE (!ip10.isLinkLocalMC());
	EXPECT_TRUE (!ip10.isSiteLocalMC());
	EXPECT_TRUE (!ip10.isOrgLocalMC());
	EXPECT_TRUE (!ip10.isGlobalMC());

	IPAddress ip6("fec0::21f:5bff:fec6:6707"); // site local unicast
	EXPECT_TRUE (!ip6.isWildcard());
	EXPECT_TRUE (!ip6.isBroadcast());
	EXPECT_TRUE (!ip6.isLoopback());
	EXPECT_TRUE (!ip6.isMulticast());
	EXPECT_TRUE (ip6.isUnicast());
	EXPECT_TRUE (!ip6.isLinkLocal());
	EXPECT_TRUE (ip6.isSiteLocal());
	EXPECT_TRUE (!ip6.isWellKnownMC());
	EXPECT_TRUE (!ip6.isNodeLocalMC());
	EXPECT_TRUE (!ip6.isLinkLocalMC());
	EXPECT_TRUE (!ip6.isSiteLocalMC());
	EXPECT_TRUE (!ip6.isOrgLocalMC());
	EXPECT_TRUE (!ip6.isGlobalMC());
#endif
}


TEST(IPAddress, testMCClassification6)
{
#ifdef POCO_HAVE_IPv6
	IPAddress ip1("ff02:0:0:0:0:0:0:c"); // well-known link-local multicast
	EXPECT_TRUE (!ip1.isWildcard());
	EXPECT_TRUE (!ip1.isBroadcast());
	EXPECT_TRUE (!ip1.isLoopback());
	EXPECT_TRUE (ip1.isMulticast());
	EXPECT_TRUE (!ip1.isUnicast());
	EXPECT_TRUE (!ip1.isLinkLocal());
	EXPECT_TRUE (!ip1.isSiteLocal());
	EXPECT_TRUE (ip1.isWellKnownMC());
	EXPECT_TRUE (!ip1.isNodeLocalMC());
	EXPECT_TRUE (ip1.isLinkLocalMC()); 
	EXPECT_TRUE (!ip1.isSiteLocalMC());
	EXPECT_TRUE (!ip1.isOrgLocalMC());
	EXPECT_TRUE (!ip1.isGlobalMC());

	IPAddress ip2("FF01:0:0:0:0:0:0:FB"); // node-local unicast
	EXPECT_TRUE (!ip2.isWildcard());
	EXPECT_TRUE (!ip2.isBroadcast());
	EXPECT_TRUE (!ip2.isLoopback());
	EXPECT_TRUE (ip2.isMulticast());
	EXPECT_TRUE (!ip2.isUnicast());
	EXPECT_TRUE (!ip2.isLinkLocal());
	EXPECT_TRUE (!ip2.isSiteLocal());
	EXPECT_TRUE (ip2.isWellKnownMC());
	EXPECT_TRUE (ip2.isNodeLocalMC());
	EXPECT_TRUE (!ip2.isLinkLocalMC());
	EXPECT_TRUE (!ip2.isSiteLocalMC());
	EXPECT_TRUE (!ip2.isOrgLocalMC());
	EXPECT_TRUE (!ip2.isGlobalMC()); 

	IPAddress ip3("FF05:0:0:0:0:0:0:FB"); // site local unicast
	EXPECT_TRUE (!ip3.isWildcard());
	EXPECT_TRUE (!ip3.isBroadcast());
	EXPECT_TRUE (!ip3.isLoopback());
	EXPECT_TRUE (ip3.isMulticast());
	EXPECT_TRUE (!ip3.isUnicast());
	EXPECT_TRUE (!ip3.isLinkLocal());
	EXPECT_TRUE (!ip3.isSiteLocal());
	EXPECT_TRUE (ip3.isWellKnownMC());
	EXPECT_TRUE (!ip3.isNodeLocalMC());
	EXPECT_TRUE (!ip3.isLinkLocalMC());
	EXPECT_TRUE (ip3.isSiteLocalMC());
	EXPECT_TRUE (!ip3.isOrgLocalMC());
	EXPECT_TRUE (!ip3.isGlobalMC());

	IPAddress ip4("FF18:0:0:0:0:0:0:FB"); // org local unicast
	EXPECT_TRUE (!ip4.isWildcard());
	EXPECT_TRUE (!ip4.isBroadcast());
	EXPECT_TRUE (!ip4.isLoopback());
	EXPECT_TRUE (ip4.isMulticast());
	EXPECT_TRUE (!ip4.isUnicast());
	EXPECT_TRUE (!ip4.isLinkLocal());
	EXPECT_TRUE (!ip4.isSiteLocal());
	EXPECT_TRUE (!ip4.isWellKnownMC());
	EXPECT_TRUE (!ip4.isNodeLocalMC());
	EXPECT_TRUE (!ip4.isLinkLocalMC());
	EXPECT_TRUE (!ip4.isSiteLocalMC());
	EXPECT_TRUE (ip4.isOrgLocalMC());
	EXPECT_TRUE (!ip4.isGlobalMC());

	IPAddress ip5("FF1F:0:0:0:0:0:0:FB"); // global unicast
	EXPECT_TRUE (!ip5.isWildcard());
	EXPECT_TRUE (!ip5.isBroadcast());
	EXPECT_TRUE (!ip5.isLoopback());
	EXPECT_TRUE (ip5.isMulticast());
	EXPECT_TRUE (!ip5.isUnicast());
	EXPECT_TRUE (!ip5.isLinkLocal());
	EXPECT_TRUE (!ip5.isSiteLocal());
	EXPECT_TRUE (!ip5.isWellKnownMC());
	EXPECT_TRUE (!ip5.isNodeLocalMC());
	EXPECT_TRUE (!ip5.isLinkLocalMC()); 
	EXPECT_TRUE (!ip5.isSiteLocalMC());
	EXPECT_TRUE (!ip5.isOrgLocalMC());
	EXPECT_TRUE (ip5.isGlobalMC());
#endif
}


TEST(IPAddress, testRelationals)
{
	IPAddress ip1("192.168.1.120");
	IPAddress ip2(ip1);
	IPAddress ip3;
	IPAddress ip4("10.0.0.138");
	
	EXPECT_TRUE (ip1 != ip4);
	EXPECT_TRUE (ip1 == ip2);
	EXPECT_TRUE (!(ip1 != ip2));
	EXPECT_TRUE (!(ip1 == ip4));
	EXPECT_TRUE (ip1 > ip4);
	EXPECT_TRUE (ip1 >= ip4);
	EXPECT_TRUE (ip4 < ip1);
	EXPECT_TRUE (ip4 <= ip1);
	EXPECT_TRUE (!(ip1 < ip4));
	EXPECT_TRUE (!(ip1 <= ip4));
	EXPECT_TRUE (!(ip4 > ip1));
	EXPECT_TRUE (!(ip4 >= ip1));
	
	ip3 = ip1;
	EXPECT_TRUE (ip1 == ip3);
	ip3 = ip4;
	EXPECT_TRUE (ip1 != ip3);
	EXPECT_TRUE (ip3 == ip4);
}


TEST(IPAddress, testWildcard)
{
	IPAddress wildcard = IPAddress::wildcard();
	EXPECT_TRUE (wildcard.isWildcard());
	EXPECT_TRUE (wildcard.toString() == "0.0.0.0");
}


TEST(IPAddress, testBroadcast)
{
	IPAddress broadcast = IPAddress::broadcast();
	EXPECT_TRUE (broadcast.isBroadcast());
	EXPECT_TRUE (broadcast.toString() == "255.255.255.255");
}
