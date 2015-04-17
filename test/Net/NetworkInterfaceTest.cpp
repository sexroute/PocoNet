#include <gtest/gtest.h>
#include "Poco/Net/NetworkInterface.h"
#include <iostream>


using Poco::Net::NetworkInterface;



TEST(NetworkInterface, testList)
{
	NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
	EXPECT_TRUE (!list.empty());
	for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		std::cout << "Name:        " << it->name() << std::endl;
		std::cout << "DisplayName: " << it->displayName() << std::endl;
		std::cout << "Address:     " << it->address().toString() << std::endl;
		std::cout << "Subnet:      " << it->subnetMask().toString() << std::endl;
		std::cout << "Broadcast:   " << it->broadcastAddress().toString() << std::endl;
		std::cout << "Index:       " << it->index() << std::endl;		
	}
}


TEST(NetworkInterface, testForName)
{
	NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
	for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		NetworkInterface ifc = NetworkInterface::forName(it->name());
		EXPECT_TRUE (ifc.name() == it->name());
	}
}


TEST(NetworkInterface, testForAddress)
{
	NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
	for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		NetworkInterface ifc = NetworkInterface::forAddress(it->address());
		EXPECT_TRUE (ifc.address() == it->address());
	}
}


TEST(NetworkInterface, testForIndex)
{
#if defined(POCO_HAVE_IPv6)
	NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
	for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		NetworkInterface ifc = NetworkInterface::forIndex(it->index());
		EXPECT_TRUE (ifc.index() == it->index());
	}
#endif
}
