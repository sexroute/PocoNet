#include <gtest/gtest.h>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"
#include "Poco/Timespan.h"
#include <iostream>


using Poco::Net::Socket;
using Poco::Net::StreamSocket;
using Poco::Net::SocketAddress;
using Poco::Net::ConnectionRefusedException;
using Poco::Timespan;
using Poco::TimeoutException;
using Poco::InvalidArgumentException;


static const std::string http_request = "GET /index.html HTTP/1.0\r\n\r\n";
static const std::string response_ok = "HTTP/1.1 200 OK\r\n";


TEST(Socket, testEcho)
{
    StreamSocket ss;
    ss.connect(SocketAddress("www.baidu.com", 80));
    int n = ss.sendBytes(http_request.c_str(), http_request.size());
    EXPECT_TRUE (n == http_request.size());
    char buffer[512];
    n = ss.receiveBytes(buffer, sizeof(buffer));
    EXPECT_TRUE (n > 0);
    std::string response(buffer, n);
    EXPECT_TRUE (response.find(response_ok) == 0);
    ss.close();
}


TEST(Socket, testPoll)
{
    StreamSocket ss;
    ss.connect(SocketAddress("www.baidu.com", 80));

    Timespan timeout(1000000);
    EXPECT_TRUE (!ss.poll(timeout, Socket::SELECT_READ));
    
    EXPECT_TRUE (ss.poll(timeout, Socket::SELECT_WRITE));

    ss.sendBytes(http_request.c_str(), http_request.size());
    
    EXPECT_TRUE (ss.poll(timeout, Socket::SELECT_READ));
    char buffer[512];
    int n = ss.receiveBytes(buffer, sizeof(buffer));
    EXPECT_TRUE (n > 0);
    std::string response(buffer, n);
    EXPECT_TRUE (response.find(response_ok) == 0);

    ss.close();
}


TEST(Socket, testAvailable)
{
    StreamSocket ss;
    ss.connect(SocketAddress("www.baidu.com", 80));
    Timespan timeout(1000000);
    ss.sendBytes(http_request.c_str(), http_request.size());
    char buffer[512];
    EXPECT_TRUE (ss.poll(timeout, Socket::SELECT_READ));
    int av = ss.available();
    EXPECT_TRUE (av > 0);

    int n = ss.receiveBytes(buffer, sizeof(buffer));
    EXPECT_TRUE (n > 0);
    std::string response(buffer, n);
    EXPECT_TRUE (response.find(response_ok) == 0);

    ss.close();
}


TEST(Socket, testConnect)
{
    StreamSocket ss;
    Timespan timeout(250000);
    ss.connect(SocketAddress("www.baidu.com", 80), timeout);
}


TEST(Socket, testConnectRefused)
{
    StreamSocket ss;
    Timespan timeout(250000);
    EXPECT_THROW(ss.connect(SocketAddress("localhost", 80)), 
        ConnectionRefusedException);
}


TEST(Socket, testConnectRefusedNB)
{
    StreamSocket ss;
    Timespan timeout(2, 0);
    try
    {
        ss.connect(SocketAddress("localhost", 80), timeout);
        EXPECT_FALSE("connection refused - must throw");
    }
    catch (TimeoutException&)
    {
        EXPECT_TRUE(true);
    }
    catch (ConnectionRefusedException&)
    {
        EXPECT_TRUE(true);
    }
}


TEST(Socket, testNonBlocking)
{
    StreamSocket ss;
    ss.connect(SocketAddress("www.baidu.com", 80));
    ss.setBlocking(false);

    Timespan timeout(1000000);
    EXPECT_TRUE (ss.poll(timeout, Socket::SELECT_WRITE));
    int n = ss.sendBytes(http_request.c_str(), http_request.size());
    EXPECT_TRUE (n > 0);

    char buffer[512];
    EXPECT_TRUE (ss.poll(timeout, Socket::SELECT_READ));
    n = ss.receiveBytes(buffer, sizeof(buffer));
    std::string response(buffer, n);
    EXPECT_TRUE (response.find(response_ok) == 0);

    ss.close();
}


TEST(Socket, testTimeout)
{
    StreamSocket ss;
    ss.connect(SocketAddress("www.baidu.com", 80));
    
    Timespan timeout0 = ss.getReceiveTimeout();
    Timespan timeout(250000);
    ss.setReceiveTimeout(timeout);
    Timespan timeout1 = ss.getReceiveTimeout();
    std::cout << "original receive timeout:  " << timeout0.totalMicroseconds() << std::endl;
    std::cout << "requested receive timeout: " << timeout.totalMicroseconds() << std::endl;
    std::cout << "actual receive timeout:    " << timeout1.totalMicroseconds() << std::endl;
    
    // some socket implementations adjust the timeout value
     EXPECT_TRUE (ss.getReceiveTimeout() == timeout);

     try
     {
         char buffer[256];
         ss.receiveBytes(buffer, sizeof(buffer));
         EXPECT_FALSE("nothing to receive - must timeout");
     }
     catch (TimeoutException&)
     {
         EXPECT_TRUE(true);
     }

    
    timeout0 = ss.getSendTimeout();
    ss.setSendTimeout(timeout);
    timeout1 = ss.getSendTimeout();
    std::cout << "original send timeout:  " << timeout0.totalMicroseconds() << std::endl;
    std::cout << "requested send timeout: " << timeout.totalMicroseconds() << std::endl;
    std::cout << "actual send timeout:    " << timeout1.totalMicroseconds() << std::endl;
    EXPECT_TRUE (ss.getSendTimeout() == timeout);
}


TEST(Socket, testBufferSize)
{
    SocketAddress sa("localhost", 1234);
    StreamSocket ss(sa.family());
    
    int osz = ss.getSendBufferSize();
    int rsz = 32000;
    ss.setSendBufferSize(rsz);
    int asz = ss.getSendBufferSize();
    std::cout << "original send buffer size:  " << osz << std::endl;
    std::cout << "requested send buffer size: " << rsz << std::endl;
    std::cout << "actual send buffer size:    " << asz << std::endl;
    
    osz = ss.getReceiveBufferSize();
    ss.setReceiveBufferSize(rsz);
    asz = ss.getReceiveBufferSize();
    std::cout << "original recv buffer size:  " << osz << std::endl;
    std::cout << "requested recv buffer size: " << rsz << std::endl;
    std::cout << "actual recv buffer size:    " << asz << std::endl;
}


TEST(Socket, testOptions)
{
    StreamSocket ss;
    ss.connect(SocketAddress("www.baidu.com", 80));

    ss.setLinger(true, 20);
    bool f;
    int  t;
    ss.getLinger(f, t);
    EXPECT_TRUE (f && t == 20);
    ss.setLinger(false, 0);
    ss.getLinger(f, t);
    EXPECT_TRUE (!f);
    
    ss.setNoDelay(true);
    EXPECT_TRUE (ss.getNoDelay());
    ss.setNoDelay(false);
    EXPECT_TRUE (!ss.getNoDelay());
    
    ss.setKeepAlive(true);
    EXPECT_TRUE (ss.getKeepAlive());
    ss.setKeepAlive(false);
    EXPECT_TRUE (!ss.getKeepAlive());
    
    ss.setOOBInline(true);
    EXPECT_TRUE (ss.getOOBInline());
    ss.setOOBInline(false);
    EXPECT_TRUE (!ss.getOOBInline());
}


TEST(Socket, testSelect)
{
    Timespan timeout(250000);

    StreamSocket ss;
    ss.connect(SocketAddress("www.baidu.com", 80));

    Socket::SocketList readList;
    Socket::SocketList writeList;
    Socket::SocketList exceptList;

    readList.push_back(ss);
    EXPECT_TRUE (Socket::select(readList, writeList, exceptList, timeout) == 0);
    EXPECT_TRUE (readList.empty());
    EXPECT_TRUE (writeList.empty());
    EXPECT_TRUE (exceptList.empty());
    
    ss.sendBytes(http_request.c_str(), http_request.size());

    ss.poll(timeout, Socket::SELECT_READ);

    readList.push_back(ss);
    writeList.push_back(ss);
    EXPECT_TRUE (Socket::select(readList, writeList, exceptList, timeout) == 2);
    EXPECT_TRUE (!readList.empty());
    EXPECT_TRUE (!writeList.empty());
    EXPECT_TRUE (exceptList.empty());

    char buffer[256];
    int n = ss.receiveBytes(buffer, sizeof(buffer));
    EXPECT_TRUE (n > 0);
    std::string response(buffer, n);
    EXPECT_TRUE (response.find(response_ok) == 0);

    ss.close();
}


TEST(Socket, testSelect2)
{
    Timespan timeout(100000);

    StreamSocket ss1(SocketAddress("www.baidu.com", 80));
    StreamSocket ss2(SocketAddress("www.bing.com", 80));
    
    Socket::SocketList readList;
    Socket::SocketList writeList;
    Socket::SocketList exceptList;

    readList.push_back(ss1);
    readList.push_back(ss2);
    EXPECT_TRUE (Socket::select(readList, writeList, exceptList, timeout) == 0);
    EXPECT_TRUE (readList.empty());
    EXPECT_TRUE (writeList.empty());
    EXPECT_TRUE (exceptList.empty());
    
    ss1.sendBytes(http_request.c_str(), http_request.size());

    ss1.poll(timeout, Socket::SELECT_READ);

    readList.push_back(ss1);
    readList.push_back(ss2);
    EXPECT_TRUE (Socket::select(readList, writeList, exceptList, timeout) == 1);

    EXPECT_TRUE (readList.size() == 1);
    EXPECT_TRUE (readList[0] == ss1);
    EXPECT_TRUE (writeList.empty());
    EXPECT_TRUE (exceptList.empty());

    char buffer[256];
    int n = ss1.receiveBytes(buffer, sizeof(buffer));
    EXPECT_TRUE (n > 0);
    std::string response(buffer, n);
    EXPECT_TRUE (response.find(response_ok) == 0);

    readList.clear();
    writeList.clear();
    exceptList.clear();
    writeList.push_back(ss1);
    writeList.push_back(ss2);
    EXPECT_TRUE (Socket::select(readList, writeList, exceptList, timeout) == 2);
    EXPECT_TRUE (readList.empty());
    EXPECT_TRUE (writeList.size() == 2);
    EXPECT_TRUE (writeList[0] == ss1);
    EXPECT_TRUE (writeList[1] == ss2);
    EXPECT_TRUE (exceptList.empty());

    ss1.close();
    ss2.close();
}


TEST(Socket, testSelect3)
{
    Socket::SocketList readList;
    Socket::SocketList writeList;
    Socket::SocketList exceptList;
    Timespan timeout(1000);

    int rc = Socket::select(readList, writeList, exceptList, timeout);
    EXPECT_TRUE (rc == 0);
}
