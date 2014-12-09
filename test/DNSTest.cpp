#include <gtest/gtest.h>
#include "Poco/Net/DNS.h"
#include "Poco/Net/HostEntry.h"
#include "Poco/Net/NetException.h"


using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;
using Poco::Net::InvalidAddressException;
using Poco::Net::HostNotFoundException;
using Poco::Net::ServiceNotFoundException;
using Poco::Net::NoAddressFoundException;

TEST(DNS, testHostByName)
{
    HostEntry he1 = DNS::hostByName("google-public-dns-a.google.com");
    // different systems report different canonical names, unfortunately.
    EXPECT_TRUE (he1.name() == "google-public-dns-a.google.com");
#if !defined(POCO_HAVE_ADDRINFO)
    // getaddrinfo() does not report any aliases
    EXPECT_TRUE (!he1.aliases().empty());
    EXPECT_TRUE (he1.aliases()[0] == "google-public-dns-a.google.com");
#endif
    EXPECT_TRUE (he1.addresses().size() >= 1);
    EXPECT_TRUE (he1.addresses()[0].toString() == "8.8.8.8");
    
    try
    {
        HostEntry he1 = DNS::hostByName("nosuchhost.microsoft.com");
        EXPECT_FALSE("host not found - must throw");
    }
    catch (HostNotFoundException&)
    {
        EXPECT_TRUE(true);
    }
    catch (NoAddressFoundException&)
    {
        EXPECT_TRUE(true);
    }
}


TEST(DNS, testHostByAddress)
{
    IPAddress ip1("8.8.8.8");
    HostEntry he1;
    EXPECT_NO_THROW(he1 = DNS::hostByAddress(ip1));
    EXPECT_TRUE (he1.name() == "google-public-dns-a.google.com");
    EXPECT_TRUE (he1.aliases().empty());
    EXPECT_TRUE (he1.addresses().size() >= 1);
    EXPECT_TRUE (he1.addresses()[0].toString() == "8.8.8.8");
    
    IPAddress ip2("12.34.56.78");
    try
    {
        HostEntry he2 = DNS::hostByAddress(ip2);
        EXPECT_FALSE("host not found - must throw");
    }
    catch (HostNotFoundException&)
    {
        EXPECT_TRUE(true);
    }
    catch (NoAddressFoundException&)
    {
        EXPECT_TRUE(true);
    }
}
