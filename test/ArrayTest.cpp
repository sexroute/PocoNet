// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/Array.h"
#include <vector>
#include <algorithm>
#include <functional>

struct Element
{
	int _data;
};

TEST(ArrayTest, testConstruction)
{

	// fundamental type
	typedef Poco::Array<float,6> FloatArray;
	FloatArray a = { { 42.f } };

	for (unsigned i=1; i<a.size(); ++i) {
		a[i] = a[i-1]+1.f;
	}

	// copy constructor and assignment operator
	FloatArray b(a);
	FloatArray c;
	c = a;
	EXPECT_TRUE (a==b && a==c);

	typedef Poco::Array<double,6> DArray;
	typedef Poco::Array<int,6> IArray;
	IArray ia = {{1, 2, 3, 4, 5, 6 }};
	DArray da;
	da = ia;
	da.assign(42);

	// user-defined type
	typedef Poco::Array<Element,10> ElementArray;
	ElementArray g;

	for (unsigned i=0; i<g.size(); ++i) {
		g[i]._data = i;
	}

	for (unsigned i=0; i<g.size(); ++i) {
		EXPECT_TRUE(g[i]._data == i);
	}


}
TEST(ArrayTest, testOperations)
{
	const int SIZE = 6;
	typedef Poco::Array<int,SIZE> Array;
	Array a = { { 1 } };

	// use some common STL container operations
	EXPECT_TRUE(a.size() == SIZE);
	EXPECT_TRUE(a.max_size() == SIZE);
	EXPECT_TRUE(a.empty() == false);
	EXPECT_TRUE(a.front() == a[0]);
	EXPECT_TRUE(a.back() == a[a.size()-1]);
	//EXPECT_TRUE(a.data() == &a[0]);

	// assign
	a.assign(100);
	for(int i = 0; i<a.size(); i++){
		EXPECT_TRUE(a[i] == 100);
	}

	// swap
	Array b; 
	b.assign(10);
	for(int i=0; i<SIZE; i++){
		EXPECT_TRUE(a[i] == 100);
		EXPECT_TRUE(b[i] == 10);
	}
	a.swap(b);
	for(int i=0; i<SIZE; i++){
		EXPECT_TRUE(a[i] == 10);
		EXPECT_TRUE(b[i] == 100);
	}

}

TEST(ArrayTest, testContainer)
{
	const int SIZE = 2;
	typedef Poco::Array<int,SIZE> Array;
	Array a = {{1, 2}};
	EXPECT_TRUE(a[0] == 1);
	EXPECT_TRUE(a[1] == 2);

	typedef std::vector<Array> ArrayVec;
	ArrayVec container;
	container.push_back(a);
	container.push_back(a);

	EXPECT_TRUE(container[0][0] == 1);
	EXPECT_TRUE(container[0][1] == 2);
	EXPECT_TRUE(container[1][0] == 1);
	EXPECT_TRUE(container[1][1] == 2);
}

TEST(ArrayTest, testIterator)
{
    // create array of four seasons
	Poco::Array<std::string,4> seasons = {
        { "spring", "summer", "autumn", "winter" }
    };

    // copy and change order
	Poco::Array<std::string,4> org = seasons;
    for (size_t i=seasons.size()-1; i>0; --i) {
		swap(seasons.at(i),seasons.at((i+1)%seasons.size()));
    }

    // try swap()
    swap(seasons,org);

    // try reverse iterators
    for (Poco::Array<std::string,4>::reverse_iterator pos
           =seasons.rbegin(); pos<seasons.rend(); ++pos) {
    }
}

TEST(ArrayTest, testAlgorithm)
{
    // create and initialize array
	const int SIZE = 10;
	typedef Poco::Array<int,SIZE> IArray;
	IArray a = { { 1, 2, 3, 4, 5 } };
	IArray b(a);

    // modify elements directly
    for (unsigned i=0; i<b.size(); ++i) {
        ++b[i];
    }

    // try iterators
	for (IArray::iterator pos =b.begin(); pos<b.end(); ++pos) {
		--(*pos);
    }

    for (unsigned i=0; i<a.size(); ++i) {
		EXPECT_TRUE(a[i] == b[i]);
    }

    // change order using an STL algorithm
	std::reverse(a.begin(),a.end());

    for (unsigned i=0; i<a.size(); ++i) {
		EXPECT_TRUE(a[SIZE-i-1] == b[i]);
    }

	std::reverse(a.begin(),a.end());

    // negate elements using STL framework
	std::transform(	a.begin(),a.end(),    // source
					a.begin(),            // destination
					std::negate<int>());  // operation

    for (unsigned i=0; i<a.size(); ++i) {
		EXPECT_TRUE(a[i] == -b[i]);
    }

}

TEST(ArrayTest, testMultiLevelArray)
{
	const int SIZE = 2;
	typedef Poco::Array<int,SIZE> IArray;
	typedef Poco::Array<IArray,SIZE> MultiArray;

	MultiArray a;
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = 3;
	a[1][1] = 4;

	MultiArray b = a;
	EXPECT_TRUE(b[0][0] == 1);
	EXPECT_TRUE(b[0][1] == 2);
	EXPECT_TRUE(b[1][0] == 3);
	EXPECT_TRUE(b[1][1] == 4);
}
