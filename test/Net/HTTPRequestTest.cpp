#include <gtest/gtest.h>
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/NetException.h"
#include <sstream>


using Poco::Net::HTTPRequest;
using Poco::Net::HTTPMessage;
using Poco::Net::MessageException;
using Poco::Net::NameValueCollection;


TEST(HTTPRequest, testWrite1)
{
	HTTPRequest request;
	std::ostringstream ostr;
	request.write(ostr);
	std::string s = ostr.str();
	EXPECT_TRUE (s == "GET / HTTP/1.0\r\n\r\n");
}


TEST(HTTPRequest, testWrite2)
{
	HTTPRequest request(HTTPRequest::HTTP_HEAD, "/index.html", HTTPMessage::HTTP_1_1);
	request.setHost("localhost", 80);
	request.setKeepAlive(true);
	request.set("User-Agent", "Poco");
	std::ostringstream ostr;
	request.write(ostr);
	std::string s = ostr.str();
	EXPECT_TRUE (s == "HEAD /index.html HTTP/1.1\r\nConnection: Keep-Alive\r\nHost: localhost\r\nUser-Agent: Poco\r\n\r\n");
}


TEST(HTTPRequest, testWrite3)
{
	HTTPRequest request(HTTPRequest::HTTP_POST, "/test.cgi", HTTPMessage::HTTP_1_1);
	request.setHost("localhost", 8000);
	request.setKeepAlive(false);
	request.set("User-Agent", "Poco");
	request.setContentLength(100);
	request.setContentType("text/plain");
	std::ostringstream ostr;
	request.write(ostr);
	std::string s = ostr.str();
	EXPECT_TRUE (s == "POST /test.cgi HTTP/1.1\r\nConnection: Close\r\nContent-Length: 100\r\nContent-Type: text/plain\r\nHost: localhost:8000\r\nUser-Agent: Poco\r\n\r\n");
}


TEST(HTTPRequest, testWrite4)
{
	HTTPRequest request(HTTPRequest::HTTP_HEAD, "/index.html", HTTPMessage::HTTP_1_1);
	request.setHost("fe80::1", 88);
	request.setKeepAlive(true);
	request.set("User-Agent", "Poco");
	std::ostringstream ostr;
	request.write(ostr);
	std::string s = ostr.str();
	EXPECT_TRUE (s == "HEAD /index.html HTTP/1.1\r\nConnection: Keep-Alive\r\nHost: [fe80::1]:88\r\nUser-Agent: Poco\r\n\r\n");
}


TEST(HTTPRequest, testRead1)
{
	std::string s("GET / HTTP/1.0\r\n\r\n");
	std::istringstream istr(s);
	HTTPRequest request;
	request.read(istr);
	EXPECT_TRUE (request.getMethod() == HTTPRequest::HTTP_GET);
	EXPECT_TRUE (request.getURI() == "/");
	EXPECT_TRUE (request.getVersion() == HTTPMessage::HTTP_1_0);
	EXPECT_TRUE (request.empty());
	EXPECT_TRUE (istr.get() == -1);
}


TEST(HTTPRequest, testRead2)
{
	std::string s("HEAD /index.html HTTP/1.1\r\nConnection: Keep-Alive\r\nHost: localhost\r\nUser-Agent: Poco\r\n\r\n");
	std::istringstream istr(s);
	HTTPRequest request;
	request.read(istr);
	EXPECT_TRUE (request.getMethod() == HTTPRequest::HTTP_HEAD);
	EXPECT_TRUE (request.getURI() == "/index.html");
	EXPECT_TRUE (request.getVersion() == HTTPMessage::HTTP_1_1);
	EXPECT_TRUE (request.size() == 3);
	EXPECT_TRUE (request["Connection"] == "Keep-Alive");
	EXPECT_TRUE (request["Host"] == "localhost");
	EXPECT_TRUE (request["User-Agent"] == "Poco");
	EXPECT_TRUE (istr.get() == -1);
}


TEST(HTTPRequest, testRead3)
{
	std::string s("POST /test.cgi HTTP/1.1\r\nConnection: Close\r\nContent-Length: 100\r\nContent-Type: text/plain\r\nHost: localhost:8000\r\nUser-Agent: Poco\r\n\r\n");
	std::istringstream istr(s);
	HTTPRequest request;
	request.read(istr);
	EXPECT_TRUE (request.getMethod() == HTTPRequest::HTTP_POST);
	EXPECT_TRUE (request.getURI() == "/test.cgi");
	EXPECT_TRUE (request.getVersion() == HTTPMessage::HTTP_1_1);
	EXPECT_TRUE (request.size() == 5);
	EXPECT_TRUE (request["Connection"] == "Close");
	EXPECT_TRUE (request["Host"] == "localhost:8000");
	EXPECT_TRUE (request["User-Agent"] == "Poco");
	EXPECT_TRUE (request.getContentType() == "text/plain");
	EXPECT_TRUE (request.getContentLength() == 100);
	EXPECT_TRUE (istr.get() == -1);
}


TEST(HTTPRequest, testRead4)
{
	std::string s("POST /test.cgi HTTP/1.1\r\nConnection: Close\r\nContent-Length:   100  \r\nContent-Type: text/plain\r\nHost: localhost:8000\r\nUser-Agent: Poco\r\n\r\n");
	std::istringstream istr(s);
	HTTPRequest request;
	request.read(istr);
	EXPECT_TRUE (request.getMethod() == HTTPRequest::HTTP_POST);
	EXPECT_TRUE (request.getURI() == "/test.cgi");
	EXPECT_TRUE (request.getVersion() == HTTPMessage::HTTP_1_1);
	EXPECT_TRUE (request.size() == 5);
	EXPECT_TRUE (request["Connection"] == "Close");
	EXPECT_TRUE (request["Host"] == "localhost:8000");
	EXPECT_TRUE (request["User-Agent"] == "Poco");
	EXPECT_TRUE (request.getContentType() == "text/plain");
	EXPECT_TRUE (request.getContentLength() == 100);
	EXPECT_TRUE (istr.get() == -1);
}


TEST(HTTPRequest, testInvalid1)
{
	std::string s(256, 'x');
	std::istringstream istr(s);
	HTTPRequest request;
    EXPECT_THROW(request.read(istr), MessageException);
}


TEST(HTTPRequest, testInvalid2)
{
	std::string s("GET ");
	s.append(8000, 'x');
	s.append("HTTP/1.0");
	std::istringstream istr(s);
	HTTPRequest request;
    EXPECT_THROW(request.read(istr), MessageException);
}


TEST(HTTPRequest, testInvalid3)
{
	std::string s("GET / HTTP/1.10");
	std::istringstream istr(s);
	HTTPRequest request;
    EXPECT_THROW(request.read(istr), MessageException);
}


TEST(HTTPRequest, testCookies)
{
	HTTPRequest request1;
	NameValueCollection cookies1;
	cookies1.add("cookie1", "value1");
	request1.setCookies(cookies1);
	EXPECT_TRUE (request1["Cookie"] == "cookie1=value1");
	
	HTTPRequest request2;
	NameValueCollection cookies2;
	cookies2.add("cookie2", "value2");
	cookies2.add("cookie3", "value3");
	request2.setCookies(cookies2);
	EXPECT_TRUE (request2["Cookie"] == "cookie2=value2; cookie3=value3");
	
	request1.setCookies(cookies2);
	NameValueCollection cookies3;
	request1.getCookies(cookies3);
	EXPECT_TRUE (cookies3.size() == 3);
	EXPECT_TRUE (cookies3["cookie1"] == "value1");
	EXPECT_TRUE (cookies3["cookie2"] == "value2");
	EXPECT_TRUE (cookies3["cookie3"] == "value3");	
	
	HTTPRequest request3;
	request3.add("Cookie", "cookie1=value1");
	request3.add("cookie", "cookie2=value2");
	NameValueCollection cookies4;
	request3.getCookies(cookies4);
	EXPECT_TRUE (cookies4.size() == 2);
	EXPECT_TRUE (cookies4["cookie1"] == "value1");
	EXPECT_TRUE (cookies4["cookie2"] == "value2");	
}
