#include <gtest/gtest.h>
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPCookie.h"
#include "Poco/Net/NetException.h"
#include <sstream>


using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::HTTPCookie;
using Poco::Net::MessageException;

TEST(HTTPResponse, testWrite1)
{
	HTTPResponse response;
	std::ostringstream ostr;
	response.write(ostr);
	std::string s = ostr.str();
	EXPECT_TRUE (s == "HTTP/1.0 200 OK\r\n\r\n");
}


TEST(HTTPResponse, testWrite2)
{
	HTTPResponse response(HTTPMessage::HTTP_1_1, HTTPResponse::HTTP_MOVED_PERMANENTLY);
	response.set("Location", "http://www.appinf.com/index.html");
	response.set("Server", "Poco/1.0");
	std::ostringstream ostr;
	response.write(ostr);
	std::string s = ostr.str();
	EXPECT_TRUE (s == "HTTP/1.1 301 Moved Permanently\r\nLocation: http://www.appinf.com/index.html\r\nServer: Poco/1.0\r\n\r\n");
}


TEST(HTTPResponse, testRead1)
{
	std::string s("HTTP/1.1 500 Internal Server Error\r\n\r\n");
	std::istringstream istr(s);
	HTTPResponse response;
	response.read(istr);
	EXPECT_TRUE (response.getStatus() == HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
	EXPECT_TRUE (response.getReason() == "Internal Server Error");
	EXPECT_TRUE (response.getVersion() == HTTPMessage::HTTP_1_1);
	EXPECT_TRUE (response.empty());
	EXPECT_TRUE (istr.get() == -1);
}


TEST(HTTPResponse, testRead2)
{
	std::string s("HTTP/1.0 301 Moved Permanently\r\nLocation: http://www.appinf.com/index.html\r\nServer: Poco/1.0\r\n\r\n");
	std::istringstream istr(s);
	HTTPResponse response;
	response.read(istr);
	EXPECT_TRUE (response.getStatus() == HTTPResponse::HTTP_MOVED_PERMANENTLY);
	EXPECT_TRUE (response.getReason() == "Moved Permanently");
	EXPECT_TRUE (response.getVersion() == HTTPMessage::HTTP_1_0);
	EXPECT_TRUE (response.size() == 2);
	EXPECT_TRUE (response["Location"] == "http://www.appinf.com/index.html");
	EXPECT_TRUE (response["Server"] == "Poco/1.0");
	EXPECT_TRUE (istr.get() == -1);
}


TEST(HTTPResponse, testRead3)
{
	std::string s("HTTP/1.1 200 \r\nContent-Length: 0\r\n\r\n");
	std::istringstream istr(s);
	HTTPResponse response;
	response.read(istr);
	EXPECT_TRUE (response.getVersion() == HTTPMessage::HTTP_1_1);
	EXPECT_TRUE (response.getStatus() == HTTPResponse::HTTP_OK);
	EXPECT_TRUE (response.getReason() == "");
	EXPECT_TRUE (response.size() == 1);
	EXPECT_TRUE (response.getContentLength() == 0);
	EXPECT_TRUE (istr.get() == -1);
}

TEST(HTTPResponse, testInvalid1)
{
	std::string s(256, 'x');
	std::istringstream istr(s);
	HTTPResponse response;
    EXPECT_THROW(response.read(istr), MessageException);
}


TEST(HTTPResponse, testInvalid2)
{
	std::string s("HTTP/1.1 200 ");
	s.append(1000, 'x');
	s.append("\r\n\r\n");
	std::istringstream istr(s);
	HTTPResponse response;
    EXPECT_THROW(response.read(istr), MessageException);
}


TEST(HTTPResponse, testInvalid3)
{
	std::string s("HTTP/1.0 ");
	s.append(8000, 'x');
	s.append("\r\n\r\n");
	std::istringstream istr(s);
	HTTPResponse response;
    EXPECT_THROW(response.read(istr), MessageException);
}


TEST(HTTPResponse, testCookies)
{
	HTTPResponse response;
	HTTPCookie cookie1("cookie1", "value1");
	response.addCookie(cookie1);
	std::vector<HTTPCookie> cookies;
	response.getCookies(cookies);
	EXPECT_TRUE (cookies.size() == 1);
	EXPECT_TRUE (cookie1.getVersion() == cookies[0].getVersion());
	EXPECT_TRUE (cookie1.getName() == cookies[0].getName());
	EXPECT_TRUE (cookie1.getValue() == cookies[0].getValue());
	EXPECT_TRUE (cookie1.getComment() == cookies[0].getComment());
	EXPECT_TRUE (cookie1.getDomain() == cookies[0].getDomain());
	EXPECT_TRUE (cookie1.getPath() == cookies[0].getPath());
	EXPECT_TRUE (cookie1.getSecure() == cookies[0].getSecure());
	EXPECT_TRUE (cookie1.getMaxAge() == cookies[0].getMaxAge());
	
	HTTPCookie cookie2("cookie2", "value2");
	cookie2.setVersion(1);
	cookie2.setMaxAge(42);
	cookie2.setSecure(true);
	response.addCookie(cookie2);
	response.getCookies(cookies);
	EXPECT_TRUE (cookies.size() == 2);
	HTTPCookie cookie2a;
	if (cookies[0].getName() == cookie2.getName())
		cookie2a = cookies[0];
	else
		cookie2a = cookies[1];
	EXPECT_TRUE (cookie2.getVersion() == cookie2a.getVersion());
	EXPECT_TRUE (cookie2.getName() == cookie2a.getName());
	EXPECT_TRUE (cookie2.getValue() == cookie2a.getValue());
	EXPECT_TRUE (cookie2.getComment() == cookie2a.getComment());
	EXPECT_TRUE (cookie2.getDomain() == cookie2a.getDomain());
	EXPECT_TRUE (cookie2.getPath() == cookie2a.getPath());
	EXPECT_TRUE (cookie2.getSecure() == cookie2a.getSecure());
	EXPECT_TRUE (cookie2.getMaxAge() == cookie2a.getMaxAge());
	
	HTTPResponse response2;
	response2.add("Set-Cookie", "name1=value1");
	response2.add("Set-cookie", "name2=value2");
	cookies.clear();
	response2.getCookies(cookies);
	EXPECT_TRUE (cookies.size() == 2);
	EXPECT_TRUE (cookies[0].getName() == "name1" && cookies[1].getName() == "name2" 
	    || cookies[0].getName() == "name2" && cookies[1].getName() == "name1"); 
}
