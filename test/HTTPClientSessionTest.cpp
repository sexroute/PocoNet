#include <gtest/gtest.h>
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include <istream>
#include <ostream>
#include <sstream>


using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;


TEST(HTTPClientSession, testGetSmall)
{
	HTTPClientSession s("www.baidu.com", 80);
	HTTPRequest request(HTTPRequest::HTTP_GET, "/index.html");
	s.sendRequest(request);
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (response.getContentLength() > 0);
	EXPECT_TRUE (response.getContentType() == "text/plain");
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	//EXPECT_TRUE (ostr.str() == HTTPTestServer::SMALL_BODY);
}


TEST(HTTPClientSession, testGetLarge)
{
	HTTPClientSession s("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_GET, "/index.html");
	s.sendRequest(request);
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (response.getContentLength() > 0);
	EXPECT_TRUE (response.getContentType() == "text/plain");
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	//EXPECT_TRUE (ostr.str() == HTTPTestServer::LARGE_BODY);
}


TEST(HTTPClientSession, testHead)
{
	HTTPClientSession s("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_HEAD, "/large");
	s.sendRequest(request);
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (response.getContentLength() > 0);
	EXPECT_TRUE (response.getContentType() == "text/plain");
	std::ostringstream ostr;
	EXPECT_TRUE (StreamCopier::copyStream(rs, ostr) == 0);
}


TEST(HTTPClientSession, testPostSmallIdentity)
{
	HTTPClientSession s("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_POST, "/echo");
	std::string body("this is a random request body\r\n0\r\n");
	request.setContentLength((int) body.length());
	s.sendRequest(request) << body;
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (response.getContentLength() == body.length());
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	EXPECT_TRUE (ostr.str() == body);
}


TEST(HTTPClientSession, testPostLargeIdentity)
{
	HTTPClientSession s("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_POST, "/echo");
	std::string body(8000, 'x');
	body.append("\r\n0\r\n");
	request.setContentLength((int) body.length());
	s.sendRequest(request) << body;
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (response.getContentLength() == body.length());
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	EXPECT_TRUE (ostr.str() == body);
}


TEST(HTTPClientSession, testPostSmallChunked)
{
	HTTPClientSession s("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_POST, "/echo");
	std::string body("this is a random request body");
	request.setChunkedTransferEncoding(true);
	s.sendRequest(request) << body;
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (response.getChunkedTransferEncoding());
	EXPECT_TRUE (response.getContentLength() == HTTPMessage::UNKNOWN_CONTENT_LENGTH);
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	EXPECT_TRUE (ostr.str() == body);
}


TEST(HTTPClientSession, testPostLargeChunked)
{
	HTTPClientSession s("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_POST, "/echo");
	std::string body(16000, 'x');
	request.setChunkedTransferEncoding(true);
	s.sendRequest(request) << body;
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (response.getChunkedTransferEncoding());
	EXPECT_TRUE (response.getContentLength() == HTTPMessage::UNKNOWN_CONTENT_LENGTH);
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	EXPECT_TRUE (ostr.str() == body);
}


TEST(HTTPClientSession, testPostSmallClose)
{
	HTTPClientSession s("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_POST, "/echo");
	std::string body("this is a random request body");
	s.sendRequest(request) << body;
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (!response.getChunkedTransferEncoding());
	EXPECT_TRUE (response.getContentLength() == HTTPMessage::UNKNOWN_CONTENT_LENGTH);
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	EXPECT_TRUE (ostr.str() == body);
}


TEST(HTTPClientSession, testPostLargeClose)
{
	HTTPClientSession s("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_POST, "/echo");
	std::string body(8000, 'x');
	s.sendRequest(request) << body;
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (!response.getChunkedTransferEncoding());
	EXPECT_TRUE (response.getContentLength() == HTTPMessage::UNKNOWN_CONTENT_LENGTH);
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	EXPECT_TRUE (ostr.str() == body);
}


TEST(HTTPClientSession, testKeepAlive)
{
	HTTPClientSession s("localhost", 80);
	s.setKeepAlive(true);
	HTTPRequest request(HTTPRequest::HTTP_HEAD, "/keepAlive", HTTPMessage::HTTP_1_1);
	s.sendRequest(request);
	HTTPResponse response;
	std::istream& rs1 = s.receiveResponse(response);
	//EXPECT_TRUE (response.getContentLength() == HTTPTestServer::SMALL_BODY.length());
	EXPECT_TRUE (response.getContentType() == "text/plain");
	EXPECT_TRUE (response.getKeepAlive());
	std::ostringstream ostr1;
	EXPECT_TRUE (StreamCopier::copyStream(rs1, ostr1) == 0);
	
	request.setMethod(HTTPRequest::HTTP_GET);
	request.setURI("/small");
	s.sendRequest(request);
	std::istream& rs2 = s.receiveResponse(response);
	//EXPECT_TRUE (response.getContentLength() == HTTPTestServer::SMALL_BODY.length());
	EXPECT_TRUE (response.getKeepAlive());
	std::ostringstream ostr2;
	StreamCopier::copyStream(rs2, ostr2);
	//EXPECT_TRUE (ostr2.str() == HTTPTestServer::SMALL_BODY);
	
	request.setMethod(HTTPRequest::HTTP_GET);
	request.setURI("/large");
	s.sendRequest(request);
	std::istream& rs3 = s.receiveResponse(response);
	EXPECT_TRUE (response.getContentLength() == HTTPMessage::UNKNOWN_CONTENT_LENGTH);
	EXPECT_TRUE (response.getChunkedTransferEncoding());
	EXPECT_TRUE (response.getKeepAlive());
	std::ostringstream ostr3;
	std::streamsize n = StreamCopier::copyStream(rs3, ostr3);
	//EXPECT_TRUE (ostr3.str() == HTTPTestServer::LARGE_BODY);

	request.setMethod(HTTPRequest::HTTP_HEAD);
	request.setURI("/large");
	s.sendRequest(request);
	std::istream& rs4= s.receiveResponse(response);
	//EXPECT_TRUE (response.getContentLength() == HTTPTestServer::LARGE_BODY.length());
	EXPECT_TRUE (response.getContentType() == "text/plain");
	EXPECT_TRUE (!response.getKeepAlive());
	std::ostringstream ostr4;
	EXPECT_TRUE (StreamCopier::copyStream(rs4, ostr4) == 0);
}


TEST(HTTPClientSession, testProxy)
{
	HTTPClientSession s("www.somehost.com");
	s.setProxy("localhost", 80);
	HTTPRequest request(HTTPRequest::HTTP_GET, "/large");
	s.sendRequest(request);
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	//EXPECT_TRUE (response.getContentLength() == HTTPTestServer::LARGE_BODY.length());
	EXPECT_TRUE (response.getContentType() == "text/plain");
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	//EXPECT_TRUE (ostr.str() == HTTPTestServer::LARGE_BODY);
}


TEST(HTTPClientSession, testProxyAuth)
{
	HTTPClientSession s("www.somehost.com");
	s.setProxy("localhost", 80);
	s.setProxyCredentials("user", "pass");
	HTTPRequest request(HTTPRequest::HTTP_GET, "/large");
	s.sendRequest(request);
	HTTPResponse response;
	std::istream& rs = s.receiveResponse(response);
	EXPECT_TRUE (response.getContentLength() > 0);
	EXPECT_TRUE (response.getContentType() == "text/plain");
	std::ostringstream ostr;
	StreamCopier::copyStream(rs, ostr);
	//EXPECT_TRUE (ostr.str() == HTTPTestServer::LARGE_BODY);
	//std::string r = srv.lastRequest();
	//EXPECT_TRUE (r.find("Proxy-Authorization: Basic dXNlcjpwYXNz\r\n") != std::string::npos);	
}


TEST(HTTPClientSession, testBypassProxy)
{
	HTTPClientSession::ProxyConfig proxyConfig;
	proxyConfig.host = "proxy.domain.com";
	proxyConfig.port = 80;
	proxyConfig.nonProxyHosts = "localhost|127\\.0\\.0\\.1";
	
	HTTPClientSession s1("localhost", 80);
	s1.setProxyConfig(proxyConfig);
	EXPECT_TRUE (s1.bypassProxy());
	
	HTTPClientSession s2("127.0.0.1", 80);
	s2.setProxyConfig(proxyConfig);
	EXPECT_TRUE (s2.bypassProxy());
	
	HTTPClientSession s3("www.appinf.com", 80);
	s3.setProxyConfig(proxyConfig);
	EXPECT_TRUE (!s3.bypassProxy());
}
