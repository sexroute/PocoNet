#include <gtest/gtest.h>
#include "Poco/URI.h"
#include "Poco/Path.h"


using Poco::URI;
using Poco::Path;


TEST(URI, testConstruction)
{
    URI uri;
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE(uri.getAuthority().empty());
    EXPECT_TRUE(uri.getUserInfo().empty());
    EXPECT_TRUE(uri.getHost().empty());
    EXPECT_TRUE(uri.getPort() == 0);
    EXPECT_TRUE(uri.getPath().empty());
    EXPECT_TRUE(uri.getQuery().empty());
    EXPECT_TRUE(uri.getFragment().empty());
    
    uri.setScheme("ftp");
    EXPECT_TRUE(uri.getScheme() == "ftp");
    EXPECT_TRUE(uri.getPort() == 21);
    
    uri.setScheme("HTTP");
    EXPECT_TRUE(uri.getScheme() == "http");
    
    uri.setAuthority("www.appinf.com");
    EXPECT_TRUE(uri.getAuthority() == "www.appinf.com");
    EXPECT_TRUE(uri.getPort() == 80);
    
    uri.setAuthority("user@services.appinf.com:8000");
    EXPECT_TRUE(uri.getUserInfo() == "user");
    EXPECT_TRUE(uri.getHost() == "services.appinf.com");
    EXPECT_TRUE(uri.getPort() == 8000);
    
    uri.setPath("/index.html");
    EXPECT_TRUE(uri.getPath() == "/index.html");
    
    uri.setPath("/file%20with%20spaces.html");
    EXPECT_TRUE (uri.getPath() == "/file with spaces.html");
    
    uri.setPathEtc("/query.cgi?query=foo");
    EXPECT_TRUE(uri.getPath() == "/query.cgi");
    EXPECT_TRUE (uri.getQuery() == "query=foo");
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.getPathEtc() == "/query.cgi?query=foo");
    EXPECT_TRUE (uri.getPathAndQuery() == "/query.cgi?query=foo");
    
    uri.setPathEtc("/query.cgi?query=bar#frag");
    EXPECT_TRUE (uri.getPath() == "/query.cgi");
    EXPECT_TRUE (uri.getQuery() == "query=bar");
    EXPECT_TRUE (uri.getFragment() == "frag");
    EXPECT_TRUE (uri.getPathEtc() == "/query.cgi?query=bar#frag");
    EXPECT_TRUE (uri.getPathAndQuery() == "/query.cgi?query=bar");
    
    uri.setQuery("query=test");
    EXPECT_TRUE (uri.getQuery() == "query=test");
    
    uri.setFragment("result");
    EXPECT_TRUE (uri.getFragment() == "result");
    
    URI uri2("file", "/home/guenter/foo.bar");
    EXPECT_TRUE (uri2.getScheme() == "file");
    EXPECT_TRUE (uri2.getPath() == "/home/guenter/foo.bar");
    
    URI uri3("http", "www.appinf.com", "/index.html");
    EXPECT_TRUE (uri3.getScheme() == "http");
    EXPECT_TRUE (uri3.getAuthority() == "www.appinf.com");
    EXPECT_TRUE (uri3.getPath() == "/index.html");
    
    URI uri4("http", "www.appinf.com:8000", "/index.html");
    EXPECT_TRUE (uri4.getScheme() == "http");
    EXPECT_TRUE (uri4.getAuthority() == "www.appinf.com:8000");
    EXPECT_TRUE (uri4.getPath() == "/index.html");

    URI uri5("http", "user@www.appinf.com:8000", "/index.html");
    EXPECT_TRUE (uri5.getScheme() == "http");
    EXPECT_TRUE (uri5.getUserInfo() == "user");
    EXPECT_TRUE (uri5.getHost() == "www.appinf.com");
    EXPECT_TRUE (uri5.getPort() == 8000);
    EXPECT_TRUE (uri5.getAuthority() == "user@www.appinf.com:8000");
    EXPECT_TRUE (uri5.getPath() == "/index.html");

    URI uri6("http", "user@www.appinf.com:80", "/index.html");
    EXPECT_TRUE (uri6.getScheme() == "http");
    EXPECT_TRUE (uri6.getUserInfo() == "user");
    EXPECT_TRUE (uri6.getHost() == "www.appinf.com");
    EXPECT_TRUE (uri6.getPort() == 80);
    EXPECT_TRUE (uri6.getAuthority() == "user@www.appinf.com");
    EXPECT_TRUE (uri6.getPath() == "/index.html");

    URI uri7("http", "user@www.appinf.com:", "/index.html");
    EXPECT_TRUE (uri7.getScheme() == "http");
    EXPECT_TRUE (uri7.getUserInfo() == "user");
    EXPECT_TRUE (uri7.getHost() == "www.appinf.com");
    EXPECT_TRUE (uri7.getPort() == 80);
    EXPECT_TRUE (uri7.getAuthority() == "user@www.appinf.com");
    EXPECT_TRUE (uri7.getPath() == "/index.html");
    
    URI uri8("http", "www.appinf.com", "/index.html", "query=test");
    EXPECT_TRUE (uri8.getScheme() == "http");
    EXPECT_TRUE (uri8.getAuthority() == "www.appinf.com");
    EXPECT_TRUE (uri8.getPath() == "/index.html");
    EXPECT_TRUE (uri8.getQuery() == "query=test");

    URI uri9("http", "www.appinf.com", "/index.html", "query=test", "fragment");
    EXPECT_TRUE (uri9.getScheme() == "http");
    EXPECT_TRUE (uri9.getAuthority() == "www.appinf.com");
    EXPECT_TRUE (uri9.getPath() == "/index.html");
    EXPECT_TRUE (uri9.getPathEtc() == "/index.html?query=test#fragment");
    EXPECT_TRUE (uri9.getQuery() == "query=test");
    EXPECT_TRUE (uri9.getFragment() == "fragment");

    uri9.clear();
    EXPECT_TRUE (uri9.getScheme().empty());
    EXPECT_TRUE (uri9.getAuthority().empty());
    EXPECT_TRUE (uri9.getUserInfo().empty());
    EXPECT_TRUE (uri9.getHost().empty());
    EXPECT_TRUE (uri9.getPort() == 0);
    EXPECT_TRUE (uri9.getPath().empty());
    EXPECT_TRUE (uri9.getQuery().empty());
    EXPECT_TRUE (uri9.getFragment().empty());

    URI uri10("ldap", "[2001:db8::7]", "/c=GB?objectClass?one");
    EXPECT_TRUE (uri10.getScheme() == "ldap");
    EXPECT_TRUE (uri10.getUserInfo().empty());
    EXPECT_TRUE (uri10.getHost() == "2001:db8::7");
    EXPECT_TRUE (uri10.getPort() == 389);
    EXPECT_TRUE (uri10.getAuthority() == "[2001:db8::7]");
    EXPECT_TRUE (uri10.getPathEtc() == "/c=GB?objectClass?one");
    
    URI uri11("http", "www.appinf.com", "/index.html?query=test#fragment");
    EXPECT_TRUE (uri11.getScheme() == "http");
    EXPECT_TRUE (uri11.getAuthority() == "www.appinf.com");
    EXPECT_TRUE (uri11.getPath() == "/index.html");
    EXPECT_TRUE (uri11.getPathEtc() == "/index.html?query=test#fragment");
    EXPECT_TRUE (uri11.getQuery() == "query=test");
    EXPECT_TRUE (uri11.getFragment() == "fragment");
}


TEST(URI, testParse)
{
    URI uri("http://www.appinf.com");
    EXPECT_TRUE (uri.getScheme() == "http");
    EXPECT_TRUE (uri.getAuthority() == "www.appinf.com");
    EXPECT_TRUE (uri.getPath().empty());
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (!uri.isRelative());

    uri = "http://www.appinf.com/";
    EXPECT_TRUE (uri.getScheme() == "http");
    EXPECT_TRUE (uri.getAuthority() == "www.appinf.com");
    EXPECT_TRUE (uri.getPath() == "/");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (!uri.isRelative());
    
    uri = "ftp://anonymous@ftp.appinf.com/pub/";
    EXPECT_TRUE (uri.getScheme() == "ftp");
    EXPECT_TRUE (uri.getUserInfo() == "anonymous");
    EXPECT_TRUE (uri.getHost() == "ftp.appinf.com");
    EXPECT_TRUE (uri.getPort() == 21);
    EXPECT_TRUE (uri.getAuthority() == "anonymous@ftp.appinf.com");
    EXPECT_TRUE (uri.getPath() == "/pub/");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (!uri.isRelative());
    EXPECT_TRUE (!uri.isRelative());

    uri = "https://www.appinf.com/index.html#top";
    EXPECT_TRUE (uri.getScheme() == "https");
    EXPECT_TRUE (uri.getHost() == "www.appinf.com");
    EXPECT_TRUE (uri.getPort() == 443);
    EXPECT_TRUE (uri.getPath() == "/index.html");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment() == "top");
    EXPECT_TRUE (!uri.isRelative());
    
    uri = "http://www.appinf.com/search.cgi?keyword=test&scope=all";
    EXPECT_TRUE (uri.getScheme() == "http");
    EXPECT_TRUE (uri.getHost() == "www.appinf.com");
    EXPECT_TRUE (uri.getPort() == 80);
    EXPECT_TRUE (uri.getPath() == "/search.cgi");
    EXPECT_TRUE (uri.getQuery() == "keyword=test&scope=all");
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (!uri.isRelative());

    uri = "http://www.appinf.com/search.cgi?keyword=test&scope=all#result";
    EXPECT_TRUE (uri.getScheme() == "http");
    EXPECT_TRUE (uri.getHost() == "www.appinf.com");
    EXPECT_TRUE (uri.getPort() == 80);
    EXPECT_TRUE (uri.getPath() == "/search.cgi");
    EXPECT_TRUE (uri.getQuery() == "keyword=test&scope=all");
    EXPECT_TRUE (uri.getFragment() == "result");
    EXPECT_TRUE (!uri.isRelative());
    
    uri = "http://www.appinf.com/search.cgi?keyword=test%20encoded&scope=all#result";
    EXPECT_TRUE (uri.getScheme() == "http");
    EXPECT_TRUE (uri.getHost() == "www.appinf.com");
    EXPECT_TRUE (uri.getPort() == 80);
    EXPECT_TRUE (uri.getPath() == "/search.cgi");
    EXPECT_TRUE (uri.getQuery() == "keyword=test encoded&scope=all");
    EXPECT_TRUE (uri.getFragment() == "result");
    EXPECT_TRUE (!uri.isRelative());
    
    uri = "ldap://[2001:db8::7]/c=GB?objectClass?one";
    EXPECT_TRUE (uri.getScheme() == "ldap");
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost() == "2001:db8::7");
    EXPECT_TRUE (uri.getPort() == 389);
    EXPECT_TRUE (uri.getAuthority() == "[2001:db8::7]");
    EXPECT_TRUE (uri.getPath() == "/c=GB");
    EXPECT_TRUE (uri.getQuery() == "objectClass?one");
    EXPECT_TRUE (uri.getFragment().empty());
    
    uri = "mailto:John.Doe@example.com";
    EXPECT_TRUE (uri.getScheme() == "mailto");
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getPath() == "John.Doe@example.com");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    
    uri = "tel:+1-816-555-1212";
    EXPECT_TRUE (uri.getScheme() == "tel");
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getPath() == "+1-816-555-1212");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    
    uri = "telnet://192.0.2.16:80";
    EXPECT_TRUE (uri.getScheme() == "telnet");
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost() == "192.0.2.16");
    EXPECT_TRUE (uri.getPort() == 80);
    EXPECT_TRUE (uri.getAuthority() == "192.0.2.16:80");
    EXPECT_TRUE (uri.getPath().empty());
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    
    uri = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";
    EXPECT_TRUE (uri.getScheme() == "urn");
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getPath() == "oasis:names:specification:docbook:dtd:xml:4.1.2");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    
    uri = "";
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath().empty());
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.empty());
    
    // relative references
    
    uri = "/foo/bar";
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "/foo/bar");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.isRelative());

    uri = "./foo/bar";
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "./foo/bar");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.isRelative());

    uri = "../foo/bar";
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "../foo/bar");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.isRelative());

    uri = "index.html";
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "index.html");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.isRelative());

    uri = "index.html#frag";
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "index.html");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment() == "frag");
    EXPECT_TRUE (uri.isRelative());
    
    uri = "?query=test";    
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath().empty());
    EXPECT_TRUE (uri.getQuery() == "query=test");
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.isRelative());

    uri = "?query=test#frag";   
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath().empty());
    EXPECT_TRUE (uri.getQuery() == "query=test");
    EXPECT_TRUE (uri.getFragment() == "frag");
    EXPECT_TRUE (uri.isRelative());
    
    uri = "#frag";  
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath().empty());
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment() == "frag");
    EXPECT_TRUE (uri.isRelative());

    uri = "#";  
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath().empty());
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.isRelative());
    
    uri = "file:///a/b/c";
    EXPECT_TRUE (uri.getScheme() == "file");
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "/a/b/c");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (!uri.isRelative());

    uri = "file://localhost/a/b/c";
    EXPECT_TRUE (uri.getScheme() == "file");
    EXPECT_TRUE (uri.getAuthority() == "localhost");
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost() == "localhost");
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "/a/b/c");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (!uri.isRelative());
    
    uri = "file:///c:/Windows/system32/";
    EXPECT_TRUE (uri.getScheme() == "file");
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "/c:/Windows/system32/");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (!uri.isRelative());

    uri = "./c:/Windows/system32/";
    EXPECT_TRUE (uri.getScheme().empty());
    EXPECT_TRUE (uri.getAuthority().empty());
    EXPECT_TRUE (uri.getUserInfo().empty());
    EXPECT_TRUE (uri.getHost().empty());
    EXPECT_TRUE (uri.getPort() == 0);
    EXPECT_TRUE (uri.getPath() == "./c:/Windows/system32/");
    EXPECT_TRUE (uri.getQuery().empty());
    EXPECT_TRUE (uri.getFragment().empty());
    EXPECT_TRUE (uri.isRelative());
    
}


TEST(URI, testToString)
{
    URI uri("http://www.appinf.com");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com");

    uri = "http://www.appinf.com/";
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/");
    
    uri = "ftp://anonymous@ftp.appinf.com/pub/";
    EXPECT_TRUE (uri.toString() == "ftp://anonymous@ftp.appinf.com/pub/");

    uri = "https://www.appinf.com/index.html#top";
    EXPECT_TRUE (uri.toString() == "https://www.appinf.com/index.html#top");
    
    uri = "http://www.appinf.com/search.cgi?keyword=test&scope=all";
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/search.cgi?keyword=test&scope=all");

    uri = "http://www.appinf.com/search.cgi?keyword=test&scope=all#result";
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/search.cgi?keyword=test&scope=all#result");
    
    uri = "http://www.appinf.com/search.cgi?keyword=test%20encoded&scope=all#result";
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/search.cgi?keyword=test%20encoded&scope=all#result");
    
    uri = "ldap://[2001:db8::7]/c=GB?objectClass?one";
    EXPECT_TRUE (uri.toString() == "ldap://[2001:db8::7]/c=GB?objectClass?one");
    
    uri = "mailto:John.Doe@example.com";
    EXPECT_TRUE (uri.toString() == "mailto:John.Doe@example.com");
    
    uri = "tel:+1-816-555-1212";
    EXPECT_TRUE (uri.toString() == "tel:+1-816-555-1212");
    
    uri = "telnet://192.0.2.16:80";
    EXPECT_TRUE (uri.toString() == "telnet://192.0.2.16:80");
    
    uri = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";
    EXPECT_TRUE (uri.toString() == "urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
    
    uri = "";
    EXPECT_TRUE (uri.toString() == "");

    // relative references
    
    uri = "/foo/bar";
    EXPECT_TRUE (uri.toString() == "/foo/bar");

    uri = "./foo/bar";
    EXPECT_TRUE (uri.toString() == "./foo/bar");

    uri = "../foo/bar";
    EXPECT_TRUE (uri.toString() == "../foo/bar");

    uri = "//foo/bar";
    EXPECT_TRUE (uri.toString() == "//foo/bar");

    uri = "index.html";
    EXPECT_TRUE (uri.toString() == "index.html");

    uri = "index.html#frag";
    EXPECT_TRUE (uri.toString() == "index.html#frag");
    
    uri = "?query=test";    
    EXPECT_TRUE (uri.toString() == "?query=test");

    uri = "?query=test#frag";   
    EXPECT_TRUE (uri.toString() == "?query=test#frag");
    
    uri = "#frag";  
    EXPECT_TRUE (uri.toString() == "#frag");

    uri = "#";  
    EXPECT_TRUE (uri.toString() == "");
    
    uri = "file:///a/b/c";
    EXPECT_TRUE (uri.toString() == "file:///a/b/c");
    
    uri = "file://localhost/a/b/c";
    EXPECT_TRUE (uri.toString() == "file://localhost/a/b/c");
    
    uri = "file:///c:/Windows/system32/";
    EXPECT_TRUE (uri.toString() == "file:///c:/Windows/system32/");

    uri = "./c:/Windows/system32/";
    EXPECT_TRUE (uri.toString() == "./c:/Windows/system32/");
    
    uri = "http://www.appinf.com";
    uri.setRawQuery("query=test");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/?query=test");
}


TEST(URI, testCompare)
{
    URI uri1("http://www.appinf.com");
    URI uri2("HTTP://www.appinf.com:80");
    EXPECT_TRUE (uri1 == uri2);
    EXPECT_TRUE (uri1 == "http://www.appinf.com:");
    EXPECT_TRUE (uri1 != "http://www.google.com");
    
    uri1 = "/foo/bar";
    EXPECT_TRUE (uri1 == "/foo/bar");
    EXPECT_TRUE (uri1 != "/foo/baz");
    
    uri1 = "?query";
    EXPECT_TRUE (uri1 == "?query");
    EXPECT_TRUE (uri1 != "?query2");
    
    uri1 = "#frag";
    EXPECT_TRUE (uri1 == "#frag");
    EXPECT_TRUE (uri1 != "#frag2");
    
    uri1 = "/index.html#frag";
    EXPECT_TRUE (uri1 == "/index.html#frag");
    EXPECT_TRUE (uri1 != "/index.html");
}


TEST(URI, testNormalize)
{
    URI uri("http://www.appinf.com");
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com");
    
    uri = "http://www.appinf.com/";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/");
    
    uri = "http://www.appinf.com/foo/bar/./index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/foo/bar/index.html");
    
    uri = "http://www.appinf.com/foo/bar/../index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/foo/index.html");

    uri = "http://www.appinf.com/foo/./bar/../index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/foo/index.html");

    uri = "http://www.appinf.com/foo/./bar/../index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/foo/index.html");

    uri = "http://www.appinf.com/foo/bar/../../index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/index.html");

    uri = "http://www.appinf.com/foo/bar/../../../index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/index.html");

    uri = "http://www.appinf.com/foo/bar/.././../index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/index.html");

    uri = "http://www.appinf.com/./foo/bar/index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/foo/bar/index.html");

    uri = "http://www.appinf.com/../foo/bar/index.html";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/foo/bar/index.html");

    uri = "http://www.appinf.com/../foo/bar/";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/foo/bar/");

    uri = "http://www.appinf.com/../foo/../";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/");
    
    uri = "file:///c:/Windows/system32/";
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "file:///c:/Windows/system32/");

    uri.clear();
    uri.setPath("c:/windows/system32/");
    uri.normalize();
    EXPECT_TRUE (uri.toString() == "./c:/windows/system32/");
}


TEST(URI, testResolve)
{
    URI uri("http://www.appinf.com");
    
    uri.resolve("/index.html");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/index.html");
    
    uri.resolve("#frag");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/index.html#frag");
    
    uri = "http://www.appinf.com/html";
    uri.resolve("../images/foo.gif");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/images/foo.gif");

    uri = "http://www.appinf.com/html/";
    uri.resolve(".");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/html/");

    uri = "http://www.appinf.com/html/";
    uri.resolve(".");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/html/");

    uri = "http://www.appinf.com/html/";
    uri.resolve("..");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/");

    uri = "http://www.appinf.com/html/";
    uri.resolve("index.html");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/html/index.html");

    uri = "http://www.appinf.com/html/";
    uri.resolve("/index.html");
    EXPECT_TRUE (uri.toString() == "http://www.appinf.com/index.html");

    uri = "/a/b/c/d/e";
    uri.resolve("./../../f/./g");
    EXPECT_TRUE (uri.toString() == "/a/b/f/g");
    
    uri = "/a/b/../c/";
    uri.resolve("../d");
    EXPECT_TRUE (uri.toString() == "/a/d");

    uri = "/a/b/../c/";
    uri.resolve("../d/");
    EXPECT_TRUE (uri.toString() == "/a/d/");

    uri = "/a/b/c/";
    uri.resolve("../../../../d/");
    EXPECT_TRUE (uri.toString() == "/d/");

    uri = "/a/b/c/";
    uri.resolve("%2e%2e/%2e%2e/%2e%2e/../d/");
    EXPECT_TRUE (uri.toString() == "/d/");

    uri = "/a/b/c/";
    uri.resolve("");
    EXPECT_TRUE (uri.toString() == "/a/b/c/");

    uri = "/a/b/c/";
    uri.resolve("/d/");
    EXPECT_TRUE (uri.toString() == "/d/");

    uri = "/a/b/c";
    uri.resolve("");
    EXPECT_TRUE (uri.toString() == "/a/b/c");

    uri = "/a/b/c";
    uri.resolve("?query=test");
    EXPECT_TRUE (uri.toString() == "/a/b/c?query=test");

    uri = "/a/b/c";
    uri.resolve("#frag");
    EXPECT_TRUE (uri.toString() == "/a/b/c#frag");

    uri = "http://www.appinf.com/html/";
    uri.resolve("http://www.google.com/");
    EXPECT_TRUE (uri.toString() == "http://www.google.com/");
    
    uri = "http://www.appinf.com/";
    URI uri2(uri, "index.html");
    EXPECT_TRUE (uri2.toString() == "http://www.appinf.com/index.html");

    uri = "index.html";
    URI uri3(uri, "search.html");
    EXPECT_TRUE (uri3.toString() == "search.html");
}


TEST(URI, testSwap)
{
    URI uri1("http://www.appinf.com/search.cgi?keyword=test%20encoded&scope=all#result");
    URI uri2("mailto:John.Doe@example.com");
    
    uri1.swap(uri2);
    EXPECT_TRUE (uri1.toString() == "mailto:John.Doe@example.com");
    EXPECT_TRUE (uri2.toString() == "http://www.appinf.com/search.cgi?keyword=test%20encoded&scope=all#result");
}

TEST(URI, testOther)
{
    // The search string is "hello%world"; google happens to ignore the '%'
    // character, so it finds lots of hits for "hello world" programs. This is
    // a convenient reproduction case, and a URL that actually works.
    Poco::URI uri("http://google.com/search?q=hello%25world#frag%20ment");

    EXPECT_TRUE(uri.getHost() == "google.com");
    EXPECT_TRUE(uri.getPath() == "/search");
    EXPECT_TRUE(uri.getQuery() == "q=hello%world");
    EXPECT_TRUE(uri.getRawQuery() == "q=hello%25world");
    EXPECT_TRUE(uri.getFragment() == "frag ment");
    EXPECT_TRUE(uri.toString() == "http://google.com/search?q=hello%25world#frag%20ment");
    EXPECT_TRUE(uri.getPathEtc() == "/search?q=hello%25world#frag%20ment");

    uri.setQuery("q=goodbye cruel world");
    EXPECT_TRUE(uri.getQuery() == "q=goodbye cruel world");
    EXPECT_TRUE(uri.getRawQuery() == "q=goodbye%20cruel%20world");
    EXPECT_TRUE(uri.toString() == "http://google.com/search?q=goodbye%20cruel%20world#frag%20ment");
    EXPECT_TRUE(uri.getPathEtc() == "/search?q=goodbye%20cruel%20world#frag%20ment");

    uri.setRawQuery("q=pony%7eride");
    EXPECT_TRUE(uri.getQuery() == "q=pony~ride");
    EXPECT_TRUE(uri.getRawQuery() == "q=pony%7eride");
    EXPECT_TRUE(uri.toString() == "http://google.com/search?q=pony%7eride#frag%20ment");
    EXPECT_TRUE(uri.getPathEtc() == "/search?q=pony%7eride#frag%20ment");
}


TEST(URI, testFromPath)
{
    Path path1("/var/www/site/index.html", Path::PATH_UNIX);
    URI uri1(path1);
    EXPECT_TRUE (uri1.toString() == "file:///var/www/site/index.html");

    Path path2("/var/www/site/with space.html", Path::PATH_UNIX);
    URI uri2(path2);
    EXPECT_TRUE (uri2.toString() == "file:///var/www/site/with%20space.html");
    
    Path path3("c:\\www\\index.html", Path::PATH_WINDOWS);
    URI uri3(path3);
    EXPECT_TRUE (uri3.toString() == "file:///c:/www/index.html");
}
