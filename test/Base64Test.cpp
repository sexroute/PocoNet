// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Exception.h"
#include <sstream>


using Poco::Base64Encoder;
using Poco::Base64Decoder;
using Poco::DataFormatException;


TEST(Base64Test, testEncoder)
{
	{
		std::ostringstream str;
		Base64Encoder encoder(str);
		encoder << std::string("\00\01\02\03\04\05", 6);
		encoder.close();
		EXPECT_TRUE (str.str() == "AAECAwQF");
	}
	{
		std::ostringstream str;
		Base64Encoder encoder(str);
		encoder << std::string("\00\01\02\03", 4);
		encoder.close();
		EXPECT_TRUE (str.str() == "AAECAw==");
	}
	{
		std::ostringstream str;
		Base64Encoder encoder(str);
		encoder << "ABCDEF";
		encoder.close();
		EXPECT_TRUE (str.str() == "QUJDREVG");
	}
}

TEST(Base64Test, testDecoder)
{
	{
		std::istringstream istr("AAECAwQF");
		Base64Decoder decoder(istr);
		EXPECT_TRUE (decoder.good() && decoder.get() == 0);
		EXPECT_TRUE (decoder.good() && decoder.get() == 1);
		EXPECT_TRUE (decoder.good() && decoder.get() == 2);
		EXPECT_TRUE (decoder.good() && decoder.get() == 3);
		EXPECT_TRUE (decoder.good() && decoder.get() == 4);
		EXPECT_TRUE (decoder.good() && decoder.get() == 5);
		EXPECT_TRUE (decoder.good() && decoder.get() == -1);
	}
	{
		std::istringstream istr("AAECAwQ=");
		Base64Decoder decoder(istr);
		EXPECT_TRUE (decoder.good() && decoder.get() == 0);
		EXPECT_TRUE (decoder.good() && decoder.get() == 1);
		EXPECT_TRUE (decoder.good() && decoder.get() == 2);
		EXPECT_TRUE (decoder.good() && decoder.get() == 3);
		EXPECT_TRUE (decoder.good() && decoder.get() == 4);
		EXPECT_TRUE (decoder.good() && decoder.get() == -1);
	}
	{
		std::istringstream istr("AAECAw==");
		Base64Decoder decoder(istr);
		EXPECT_TRUE (decoder.good() && decoder.get() == 0);
		EXPECT_TRUE (decoder.good() && decoder.get() == 1);
		EXPECT_TRUE (decoder.good() && decoder.get() == 2);
		EXPECT_TRUE (decoder.good() && decoder.get() == 3);
		EXPECT_TRUE (decoder.good() && decoder.get() == -1);
	}
	{
		std::istringstream istr("QUJDREVG");
		Base64Decoder decoder(istr);
		std::string s;
		decoder >> s;
		EXPECT_TRUE (s == "ABCDEF");
		EXPECT_TRUE (decoder.eof());
		EXPECT_TRUE (!decoder.fail());
	}
	{
		std::istringstream istr("QUJ\r\nDRE\r\nVG");
		Base64Decoder decoder(istr);
		std::string s;
		decoder >> s;
		EXPECT_TRUE (s == "ABCDEF");
		EXPECT_TRUE (decoder.eof());
		EXPECT_TRUE (!decoder.fail());
	}
	{
		std::istringstream istr("QUJD#REVG");
		Base64Decoder decoder(istr);
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

TEST(Base64Test, testEncodeDecode)
{
	{
		std::stringstream str;
		Base64Encoder encoder(str);
		encoder << "The quick brown fox ";
		encoder << "jumped over the lazy dog.";
		encoder.close();
		Base64Decoder decoder(str);
		std::string s;
		int c = decoder.get();
		while (c != -1) { s += char(c); c = decoder.get(); }
		EXPECT_TRUE (s == "The quick brown fox jumped over the lazy dog.");
	}
	{
		std::string src;
		for (int i = 0; i < 255; ++i) src += char(i);
		std::stringstream str;
		Base64Encoder encoder(str);
		encoder.write(src.data(), (std::streamsize) src.size());
		encoder.close();
		Base64Decoder decoder(str);
		std::string s;
		int c = decoder.get();
		while (c != -1) { s += char(c); c = decoder.get(); }
		EXPECT_TRUE (s == src);
	}
}
