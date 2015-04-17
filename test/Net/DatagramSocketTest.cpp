#include <gtest/gtest.h>
#include <cstdint>
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"
#include "Poco/Timespan.h"


using Poco::Net::Socket;
using Poco::Net::DatagramSocket;
using Poco::Net::SocketAddress;
using Poco::Net::IPAddress;
using Poco::Timespan;
using Poco::TimeoutException;
using Poco::InvalidArgumentException;
using Poco::IOException;

const uint8_t dns_query[] = 
{
    0xc8, 0x3a, 0x35, 0x49, 0xfb, 0xa0, 0x68, 0x17, 
    0x29, 0x49, 0xb8, 0x3a, 0x08, 0x00, 0x45, 0x00,
    0x00, 0x3e, 0x51, 0x8a, 0x00, 0x00, 0x40, 0x11,
    0xfe, 0x2d, 0xc0, 0xa8, 0x00, 0x67, 0x65, 0xe2,
    0x04, 0x06, 0xcb, 0xf7, 0x00, 0x35, 0x00, 0x2a,
    0x99, 0xb4, 0x02, 0x1d, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x74,
    0x69, 0x6d, 0x65, 0x07, 0x77, 0x69, 0x6e, 0x64,
    0x6f, 0x77, 0x73, 0x03, 0x63, 0x6f, 0x6d, 0x00,
    0x00, 0x01, 0x00, 0x01,
};

TEST(DatagramSocket, testEcho)
{
    DatagramSocket ss;
    ss.connect(SocketAddress("www.opendns.com", 53));
    int n = ss.sendBytes(dns_query, sizeof(dns_query));
    //EXPECT_TRUE (n == sizeof(dns_query));
    //char buffer[256];
    //n = ss.receiveBytes(buffer, sizeof(buffer));
    //EXPECT_TRUE (n == 5);
    //EXPECT_TRUE (std::string(buffer, n) == "hello");
    ss.close();
}

//
//TEST(DatagramSocket, testSendToReceiveFrom)
//{
//    DatagramSocket ss;
//    int n = ss.sendTo("hello", 5, SocketAddress("localhost", 80));
//    EXPECT_TRUE (n == 5);
//    char buffer[256];
//    SocketAddress sa;
//    n = ss.receiveFrom(buffer, sizeof(buffer), sa);
//    //EXPECT_TRUE (sa.host() == "");
//    EXPECT_TRUE (sa.port() == 12);
//    EXPECT_TRUE (n == 5);
//    EXPECT_TRUE (std::string(buffer, n) == "hello");
//    ss.close();
//}
//
//
//TEST(DatagramSocket, testBroadcast)
//{
//    DatagramSocket ss(IPAddress::IPv4);
//    SocketAddress sa("255.255.255.255", 80);
//    try
//    {
//        int n = ss.sendTo("hello", 5, sa);
//        // not all socket implementations fail if broadcast option is not set
//        // fail ("broadcast option not set - must throw");
//    }
//    catch (IOException&)
//    {
//    }
//    ss.setBroadcast(true);
//    int n = ss.sendTo("hello", 5, sa);
//    EXPECT_TRUE (n == 5);
//    char buffer[256];
//    n = ss.receiveBytes(buffer, sizeof(buffer));
//    EXPECT_TRUE (n == 5);
//    EXPECT_TRUE (std::string(buffer, n) == "hello");
//    ss.close();
//}
