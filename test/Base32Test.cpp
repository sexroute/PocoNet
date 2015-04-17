// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/Base32Encoder.h"
#include "Poco/Base32Decoder.h"
#include "Poco/Exception.h"
#include <sstream>


using Poco::Base32Encoder;
using Poco::Base32Decoder;
using Poco::DataFormatException;



TEST(Base32Test, testEncoder)
{
	{
		std::ostringstream str;
		Base32Encoder encoder(str);
		encoder << std::string("\00\01\02\03\04\05", 6);
		encoder.close();
		EXPECT_TRUE (str.str() == "AAAQEAYEAU======");
	}
	{
		std::ostringstream str;
		Base32Encoder encoder(str);
		encoder << std::string("\00\01\02\03", 4);
		encoder.close();
		EXPECT_TRUE (str.str() == "AAAQEAY=");
	}
	{
		std::ostringstream str;
		Base32Encoder encoder(str, false);
		encoder << "ABCDEF";
		encoder.close();
		EXPECT_TRUE (str.str() == "IFBEGRCFIY");
	}
	{
		std::ostringstream str;
		Base32Encoder encoder(str);
		encoder << "ABCDEF";
		encoder.close();
		EXPECT_TRUE (str.str() == "IFBEGRCFIY======");
	}
	{
		std::ostringstream str;
		Base32Encoder encoder(str);
		encoder << "ABCDE";
		encoder.close();
		EXPECT_TRUE (str.str() == "IFBEGRCF");
	}
}

TEST(Base32Test, testDecoder)
{
	{
		std::istringstream istr("AAAQEAYEAU======");
		Base32Decoder decoder(istr);
		EXPECT_TRUE (decoder.good() && decoder.get() == 0);
		EXPECT_TRUE (decoder.good() && decoder.get() == 1);
		EXPECT_TRUE (decoder.good() && decoder.get() == 2);
		EXPECT_TRUE (decoder.good() && decoder.get() == 3);
		EXPECT_TRUE (decoder.good() && decoder.get() == 4);
		EXPECT_TRUE (decoder.good() && decoder.get() == 5);
		EXPECT_TRUE (decoder.good() && decoder.get() == -1);
	}
	{
		std::istringstream istr("AAAQEAYE");
		Base32Decoder decoder(istr);
		EXPECT_TRUE (decoder.good() && decoder.get() == 0);
		EXPECT_TRUE (decoder.good() && decoder.get() == 1);
		EXPECT_TRUE (decoder.good() && decoder.get() == 2);
		EXPECT_TRUE (decoder.good() && decoder.get() == 3);
		EXPECT_TRUE (decoder.good() && decoder.get() == 4);
		EXPECT_TRUE (decoder.good() && decoder.get() == -1);
	}
	{
		std::istringstream istr("AAAQEAY=");
		Base32Decoder decoder(istr);
		EXPECT_TRUE (decoder.good() && decoder.get() == 0);
		EXPECT_TRUE (decoder.good() && decoder.get() == 1);
		EXPECT_TRUE (decoder.good() && decoder.get() == 2);
		EXPECT_TRUE (decoder.good() && decoder.get() == 3);
		EXPECT_TRUE (decoder.good() && decoder.get() == -1);
	}
	{
		std::istringstream istr("IFBEGRCFIY======");
		Base32Decoder decoder(istr);
		std::string s;
		decoder >> s;
		EXPECT_TRUE (s == "ABCDEF");
		EXPECT_TRUE (decoder.eof());
		EXPECT_TRUE (!decoder.fail());
	}
	{
		std::istringstream istr("QUJD#REVG");
		Base32Decoder decoder(istr);
		std::string s;
		try
		{
			decoder >> s;
			EXPECT_TRUE (decoder.bad());
		}
		catch (DataFormatException&)
		{
		}
		EXPECT_TRUE (!decoder.eof());
	}
}

TEST(Base32Test, testEncodeDecode)
{
	{
		std::stringstream str;
		Base32Encoder encoder(str);
		encoder << "The quick brown fox ";
		encoder << "jumped over the lazy dog.";
		encoder.close();
		Base32Decoder decoder(str);
		std::string s;
		int c = decoder.get();
		while (c != -1) { s += char(c); c = decoder.get(); }
		EXPECT_TRUE (s == "The quick brown fox jumped over the lazy dog.");
	}
	{
		std::string src;
		for (int i = 0; i < 255; ++i) src += char(i);
		std::stringstream str;
		Base32Encoder encoder(str);
		encoder.write(src.data(), (std::streamsize) src.size());
		encoder.close();
		Base32Decoder decoder(str);
		std::string s;
		int c = decoder.get();
		while (c != -1) { s += char(c); c = decoder.get(); }
		EXPECT_TRUE (s == src);
	}
}

