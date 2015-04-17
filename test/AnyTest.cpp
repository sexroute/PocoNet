// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/Exception.h"
#include "Poco/Any.h"
#include "Poco/Bugcheck.h"
#include <vector>

GCC_DIAG_OFF(unused-but-set-variable)
#if defined(_MSC_VER) && _MSC_VER < 1400
	#pragma warning(disable:4800)//forcing value to bool 'true' or 'false'
#endif

using namespace Poco;


class SomeClass
{
public:
	int i;
	std::string str;
	SomeClass(int h, std::string s): i (h), str(s)
	{
	};
	bool operator==(const SomeClass& other) const
	{
		return i == other.i && str == other.str;
	}
};


TEST(AnyTest, testDefaultCtor)
{
	const Any value;
	
	EXPECT_TRUE (value.empty());
	EXPECT_TRUE (0 == AnyCast<int>(&value));
	EXPECT_TRUE (value.type() == typeid(void));
}

TEST(AnyTest, testConvertingCtor)
{
	std::string text = "test message";
	Any value = text;
	
	EXPECT_TRUE (!value.empty());
	EXPECT_TRUE (value.type() == typeid(std::string));
	EXPECT_TRUE (0 == AnyCast<int>(&value));
	EXPECT_TRUE (0 != AnyCast<std::string>(&value));
	EXPECT_TRUE (AnyCast<std::string>(value) == text);
	EXPECT_TRUE (AnyCast<std::string>(&value) != &text);
}

TEST(AnyTest, testCopyCtor)
{
	std::string text = "test message";
	Any original = text, copy = original;
	
	EXPECT_TRUE (!copy.empty());
	EXPECT_TRUE (original.type() == copy.type());
	EXPECT_TRUE (AnyCast<std::string>(original) == AnyCast<std::string>(copy));
	EXPECT_TRUE (text == AnyCast<std::string>(copy));
	EXPECT_TRUE (AnyCast<std::string>(&original) != AnyCast<std::string>(&copy));
}

TEST(AnyTest, testCopyAssign)
{
	std::string text = "test message";
	Any original = text, copy;
	Any* assignResult = &(copy = original);
	
	EXPECT_TRUE (!copy.empty());
	EXPECT_TRUE (original.type() == copy.type());
	EXPECT_TRUE (AnyCast<std::string>(original) == AnyCast<std::string>(copy));
	EXPECT_TRUE (text == AnyCast<std::string>(copy));
	EXPECT_TRUE (AnyCast<std::string>(&original) != AnyCast<std::string>(&copy));
	EXPECT_TRUE (assignResult == &copy);

	// test self assignment
	Any& ref = original;
	original = ref;
	EXPECT_TRUE (AnyCast<std::string>(original) == AnyCast<std::string>(copy));
	original = original;
	EXPECT_TRUE (AnyCast<std::string>(original) == AnyCast<std::string>(copy));
}

TEST(AnyTest, testConvertingAssign)
{
	std::string text = "test message";
	Any value;
	Any* assignResult = &(value = text);
	
	EXPECT_TRUE (!value.empty());
	EXPECT_TRUE (value.type() == typeid(std::string));
	EXPECT_TRUE (0 == AnyCast<int>(&value));
	EXPECT_TRUE (0 != AnyCast<std::string>(&value));
	EXPECT_TRUE (AnyCast<std::string>(value) == text);
	EXPECT_TRUE (AnyCast<std::string>(&value) != &text);
	EXPECT_TRUE (assignResult == &value);
}

TEST(AnyTest, testCastToReference)
{
	Any a(137);
	const Any b(a);
	
	int&                ra    = AnyCast<int &>(a);
	int const&          ra_c  = AnyCast<int const &>(a);
	int volatile&       ra_v  = AnyCast<int volatile &>(a);
	int const volatile& ra_cv = AnyCast<int const volatile&>(a);
	
	// cv references to same obj
	EXPECT_TRUE (&ra == &ra_c && &ra == &ra_v && &ra == &ra_cv);
	
	int const &          rb_c  = AnyCast<int const &>(b);
	int const volatile & rb_cv = AnyCast<int const volatile &>(b);

	EXPECT_TRUE (&rb_c == &rb_cv); // cv references to copied const obj
	EXPECT_TRUE (&ra != &rb_c); // copies hold different objects
	
	++ra;
	int incremented = AnyCast<int>(a);
	EXPECT_TRUE (incremented == 138); // increment by reference changes value

    EXPECT_THROW(AnyCast<char &>(a), BadCastException);

    EXPECT_THROW(AnyCast<const char &>(a), BadCastException);
}

TEST(AnyTest, testBadCast)
{
	std::string text = "test message";
	Any value = text;
    EXPECT_THROW(AnyCast<const char *>(value), BadCastException);
}

TEST(AnyTest, testSwap)
{
	std::string text = "test message";
	Any original = text, swapped;
	std::string* originalPtr = AnyCast<std::string>(&original);
	Any* swapResult = &original.swap(swapped);
	
	EXPECT_TRUE (original.empty());
	EXPECT_TRUE (!swapped.empty());
	EXPECT_TRUE (swapped.type() == typeid(std::string));
	EXPECT_TRUE (text == AnyCast<std::string>(swapped));
	EXPECT_TRUE (0 != originalPtr);
#ifdef POCO_NO_SOO // pointers only match when heap-allocated
	EXPECT_TRUE (originalPtr == AnyCast<std::string>(&swapped));
#endif
	EXPECT_TRUE (swapResult == &original);
}

TEST(AnyTest, testEmptyCopy)
{
	const Any null;
	Any copied = null, assigned;
	assigned = null;
	
	EXPECT_TRUE (null.empty());
	EXPECT_TRUE (copied.empty());
	EXPECT_TRUE (assigned.empty());
}

TEST(AnyTest, testInt)
{
	Any e;
	EXPECT_TRUE (e.empty());

	Any a = 13;
	EXPECT_TRUE (a.type() == typeid(int));
	int* i = AnyCast<int>(&a);
	EXPECT_TRUE (*i == 13);
	Any b = a;
	EXPECT_TRUE (b.type() == typeid(int));
	int *cpyI = AnyCast<int>(&b);
	EXPECT_TRUE (*cpyI == *i);
	*cpyI = 20;
	EXPECT_TRUE (*cpyI != *i);
	std::string* s = AnyCast<std::string>(&a);
	EXPECT_TRUE (s == NULL);

	int tmp = AnyCast<int>(a);
	const Any c = a;
	tmp = AnyCast<int>(a);
}

TEST(AnyTest, testComplexType)
{
	SomeClass str(13,std::string("hello"));
	Any a = str;
	Any b = a;
	EXPECT_TRUE (a.type() == typeid(SomeClass));
	EXPECT_TRUE (b.type() == typeid(SomeClass));
	SomeClass str2 = AnyCast<SomeClass>(a);
	EXPECT_TRUE (str == str2);
	const SomeClass& strCRef = RefAnyCast<SomeClass>(a);
	EXPECT_TRUE (str == strCRef);
	SomeClass& strRef = RefAnyCast<SomeClass>(a);
	EXPECT_TRUE (str == strRef);
}

TEST(AnyTest, testVector)
{
	std::vector<int> tmp;
	tmp.push_back(1);
	tmp.push_back(2);
	tmp.push_back(3);
	Any a = tmp;
	EXPECT_TRUE (a.type() == typeid(std::vector<int>));
	std::vector<int> tmp2 = AnyCast<std::vector<int> >(a);
	EXPECT_TRUE (tmp2.size() == 3);
	const std::vector<int>& vecCRef = RefAnyCast<std::vector<int> >(a);
	std::vector<int>& vecRef = RefAnyCast<std::vector<int> >(a);
	
	EXPECT_TRUE (vecRef[0] == 1);
	EXPECT_TRUE (vecRef[1] == 2);
	EXPECT_TRUE (vecRef[2] == 3);
	vecRef[0] = 0;
	EXPECT_TRUE (vecRef[0] == vecCRef[0]);
}
