#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include "Poco/Net/HTTPCookie.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Net/NameValueCollection.h"



using Poco::Timestamp;
using Poco::Timespan;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::DateTimeParser;
using Poco::DateTime;
using Poco::Net::NameValueCollection;
using Poco::Net::HTTPCookie;


TEST(HTTPCookie, testCookie)
{
	HTTPCookie cookie("name", "value");
	EXPECT_TRUE (cookie.getName() == "name");
	EXPECT_TRUE (cookie.getValue() == "value");
	EXPECT_TRUE (cookie.toString() == "name=value");
	cookie.setPath("/");
	EXPECT_TRUE (cookie.toString() == "name=value; path=/");
	cookie.setComment("comment");
	EXPECT_TRUE (cookie.toString() == "name=value; path=/");
	cookie.setDomain("appinf.com");
	EXPECT_TRUE (cookie.toString() == "name=value; domain=appinf.com; path=/");
	cookie.setSecure(true);
	EXPECT_TRUE (cookie.toString() == "name=value; domain=appinf.com; path=/; secure");
	cookie.setHttpOnly(true);
	EXPECT_TRUE (cookie.toString() == "name=value; domain=appinf.com; path=/; secure; HttpOnly");
	cookie.setPriority("Low");
	EXPECT_TRUE (cookie.toString() == "name=value; domain=appinf.com; path=/; Priority=Low; secure; HttpOnly");
	cookie.setPriority("Medium");
	EXPECT_TRUE (cookie.toString() == "name=value; domain=appinf.com; path=/; Priority=Medium; secure; HttpOnly");
	cookie.setPriority("High");
	EXPECT_TRUE (cookie.toString() == "name=value; domain=appinf.com; path=/; Priority=High; secure; HttpOnly");
	cookie.setPriority("");
	cookie.setHttpOnly(false);

	cookie.setVersion(1);
	EXPECT_TRUE (cookie.toString() == "name=\"value\"; Comment=\"comment\"; Domain=\"appinf.com\"; Path=\"/\"; secure; Version=\"1\"");
	
	cookie.setSecure(false);
	cookie.setMaxAge(100);
	EXPECT_TRUE (cookie.toString() == "name=\"value\"; Comment=\"comment\"; Domain=\"appinf.com\"; Path=\"/\"; Max-Age=\"100\"; Version=\"1\"");
	
	cookie.setHttpOnly(true);
	EXPECT_TRUE (cookie.toString() == "name=\"value\"; Comment=\"comment\"; Domain=\"appinf.com\"; Path=\"/\"; Max-Age=\"100\"; HttpOnly; Version=\"1\"");

	cookie.setPriority("Low");
	EXPECT_TRUE (cookie.toString() == "name=\"value\"; Comment=\"comment\"; Domain=\"appinf.com\"; Path=\"/\"; Priority=\"Low\"; Max-Age=\"100\"; HttpOnly; Version=\"1\"");
	cookie.setPriority("Medium");
	EXPECT_TRUE (cookie.toString() == "name=\"value\"; Comment=\"comment\"; Domain=\"appinf.com\"; Path=\"/\"; Priority=\"Medium\"; Max-Age=\"100\"; HttpOnly; Version=\"1\"");
	cookie.setPriority("High");
	EXPECT_TRUE (cookie.toString() == "name=\"value\"; Comment=\"comment\"; Domain=\"appinf.com\"; Path=\"/\"; Priority=\"High\"; Max-Age=\"100\"; HttpOnly; Version=\"1\"");	
}


TEST(HTTPCookie, testEscape)
{
	std::string escaped = HTTPCookie::escape("this is a test!");
	EXPECT_TRUE (escaped == "this%20is%20a%20test!");

	escaped = HTTPCookie::escape("\n\t@,;\"'");
	EXPECT_TRUE (escaped == "%0A%09@%2C%3B%22%27");
}


TEST(HTTPCookie, testUnescape)
{
	std::string unescaped = HTTPCookie::unescape("this%20is%20a%20test!");
	EXPECT_TRUE (unescaped == "this is a test!");

	unescaped = HTTPCookie::unescape("%0a%09@%2c%3b%22%27");
	EXPECT_TRUE (unescaped == "\n\t@,;\"'");
}


static void testCookieExpiry(DateTime expiryTime)
{
    NameValueCollection nvc;
    nvc.add("name", "value");
    std::string expiryString = DateTimeFormatter::format(expiryTime.timestamp(),DateTimeFormat::HTTP_FORMAT);
    nvc.add("expires", expiryString);

    Timestamp before; //start of cookie lifetime
    HTTPCookie cookie(nvc); //cookie created
    std::string cookieStringV0 = cookie.toString();
    cookie.setVersion(1);
    std::string cookieStringV1 = cookie.toString();
    Timestamp now;
    //expected number of seconds until expiryTime - should be close to cookie._maxAge
    int expectedMaxAge = (int) ((expiryTime.timestamp() - now) / Timestamp::resolution()); //expected number of seconds until expiryTime
    Timestamp after; //end of cookie lifetime

    //length of lifetime of the cookie
    Timespan delta = after - before;

    //pull out cookie expire time string
    size_t startPos = cookieStringV0.find("expires=") + 8;
    std::string cookieExpireTimeStr = cookieStringV0.substr(startPos, cookieStringV0.find(";", startPos));
    //convert to a DateTime
    int tzd;
    DateTime cookieExpireTime = DateTimeParser::parse(cookieExpireTimeStr, tzd);
    //pull out cookie max age
    int cookieMaxAge;
    startPos = cookieStringV1.find("Max-Age=\"") + 9;
    std::string cookieMaxAgeStr = cookieStringV1.substr(startPos, cookieStringV1.find("\"", startPos));
    //convert to integer
    std::istringstream(cookieMaxAgeStr) >> cookieMaxAge;

    //EXPECT_TRUE that the cookie's expiry time reflects the time passed to
    //its constructor, within a delta of the lifetime of the cookie
    EXPECT_TRUE (cookieExpireTime - expiryTime <= delta);
    //EXPECT_TRUE that the cookie's max age is the number of seconds between
    //the creation of the cookie and the expiry time passed to its
    //constuctor, within a delta of the lifetime of the cookie
    EXPECT_TRUE (cookieMaxAge - expectedMaxAge <= delta.seconds());
}


TEST(HTTPCookie, testExpiryFuture)
{
	DateTime future;
	//1 year from now
	future.assign(future.year() + 1,
		future.month(),
		future.day(),
		future.hour(),
		future.minute(),
		future.second(),
		future.millisecond(),
		future.microsecond());
	testCookieExpiry(future);
}


TEST(HTTPCookie, testExpiryPast)
{
	DateTime past;
	// 1 year ago
	past.assign(past.year() - 1,
		past.month(),
		past.day(),
		past.hour(),
		past.minute(),
		past.second(),
		past.millisecond(),
		past.microsecond());
	testCookieExpiry(past);
}
