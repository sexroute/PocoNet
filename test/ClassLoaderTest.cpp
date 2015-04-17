// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.

#include <gtest/gtest.h>
#include "Poco/ClassLoader.h"
#include "Poco/Manifest.h"
#include "Poco/Exception.h"
#include "TestPlugin.h"

GCC_DIAG_OFF(unused-variable)

using Poco::ClassLoader;
using Poco::Manifest;
using Poco::SharedLibrary;
using Poco::AbstractMetaObject;
using Poco::NotFoundException;
using Poco::InvalidAccessException;


TEST(ClassLoaderTest, testClassLoader1)
{
	std::string path = "TestLibrary";
	path.append(SharedLibrary::suffix());

	ClassLoader<TestPlugin> cl;

	EXPECT_TRUE (cl.begin() == cl.end());
	EXPECT_EQ(nullptr, cl.findClass("PluginA"));
    EXPECT_EQ(nullptr, cl.findManifest(path));
	
	EXPECT_TRUE (!cl.isLibraryLoaded(path));
	
    EXPECT_THROW(cl.classFor("PluginA"), NotFoundException);

    EXPECT_THROW(cl.manifestFor(path), NotFoundException);
}

TEST(ClassLoaderTest, testClassLoader2)
{
	std::string path = "TestLibrary";
	path.append(SharedLibrary::suffix());

	ClassLoader<TestPlugin> cl;
	cl.loadLibrary(path);

	EXPECT_TRUE (cl.begin() != cl.end());
    EXPECT_NE(nullptr, cl.findClass("PluginA"));
    EXPECT_NE(nullptr, cl.findClass("PluginB"));
    EXPECT_NE(nullptr, cl.findClass("PluginC"));
    EXPECT_NE(nullptr, cl.findManifest(path));
	
	EXPECT_TRUE (cl.isLibraryLoaded(path));
	EXPECT_TRUE (cl.manifestFor(path).size() == 3);
	
	ClassLoader<TestPlugin>::Iterator it = cl.begin();
	EXPECT_TRUE (it != cl.end());
	EXPECT_TRUE (it->first == path);
	EXPECT_TRUE (it->second->size() == 3);
	++it;
	EXPECT_TRUE (it == cl.end());
	
	TestPlugin* pPluginA = cl.classFor("PluginA").create();
	EXPECT_TRUE (pPluginA->name() == "PluginA");
	EXPECT_TRUE (!cl.classFor("PluginA").isAutoDelete(pPluginA));
	delete pPluginA;

	TestPlugin* pPluginB = cl.classFor("PluginB").create();
	EXPECT_TRUE (pPluginB->name() == "PluginB");
	delete pPluginB;
	
	pPluginB = cl.create("PluginB");
	EXPECT_TRUE (pPluginB->name() == "PluginB");
	delete pPluginB;
	
	EXPECT_TRUE (cl.canCreate("PluginA"));
	EXPECT_TRUE (cl.canCreate("PluginB"));
	EXPECT_TRUE (!cl.canCreate("PluginC"));

	TestPlugin& pluginC = cl.instance("PluginC");
	EXPECT_TRUE (pluginC.name() == "PluginC");
	
    EXPECT_THROW(cl.instance("PluginB"), InvalidAccessException);

    EXPECT_THROW(cl.create("PluginC"), InvalidAccessException);

	try
	{
		const AbstractMetaObject<TestPlugin>& meta = cl.classFor("PluginC");
		meta.autoDelete(&(meta.instance()));
		EXPECT_FALSE("cannot take ownership of a singleton - must throw");
	}
	catch (InvalidAccessException&)
	{
	}
	
	const AbstractMetaObject<TestPlugin>& meta1 = cl.classFor("PluginC");
	EXPECT_TRUE (meta1.isAutoDelete(&(meta1.instance())));

	// the following must not produce memory leaks
	const AbstractMetaObject<TestPlugin>& meta2 = cl.classFor("PluginA");
	meta2.autoDelete(meta2.create());
	meta2.autoDelete(meta2.create());

	TestPlugin* pPlugin = meta2.create();
	meta2.autoDelete(pPlugin);
	EXPECT_TRUE (meta2.isAutoDelete(pPlugin));
	meta2.destroy(pPlugin);
	EXPECT_TRUE (!meta2.isAutoDelete(pPlugin));

	cl.unloadLibrary(path);
}

TEST(ClassLoaderTest, testClassLoader3)
{
	std::string path = "TestLibrary";
	path.append(SharedLibrary::suffix());

	ClassLoader<TestPlugin> cl;
	cl.loadLibrary(path);
	cl.loadLibrary(path);
	cl.unloadLibrary(path);
	
	EXPECT_TRUE (cl.manifestFor(path).size() == 3);
	
	ClassLoader<TestPlugin>::Iterator it = cl.begin();
	EXPECT_TRUE (it != cl.end());
	EXPECT_TRUE (it->first == path);
	EXPECT_TRUE (it->second->size() == 3);
	++it;
	EXPECT_TRUE (it == cl.end());
	
	cl.unloadLibrary(path);
    EXPECT_EQ(nullptr, cl.findManifest(path));
}
