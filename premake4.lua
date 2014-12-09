--
-- Premake4 build script (http://industriousone.com/premake/download)
--

solution 'PocoNet'
    configurations {'Debug', 'Release'}
    language 'C++'
    --flags {'ExtraWarnings'}
    targetdir 'bin'
    platforms {'x32', 'x64'}

    configuration 'Debug'
        defines { 'DEBUG' }
        flags { 'Symbols' }

    configuration 'Release'
        defines { 'NDEBUG' }
        flags { 'Symbols', 'Optimize' }

    configuration 'vs*'
        defines
        {
            '_WIN32_WINNT=0x0600',
            '_SCL_SECURE_NO_WARNINGS',
            'NOMINMAX',
        }
        links {'ws2_32', 'iphlpapi'}

    configuration 'gmake'
        buildoptions '-std=c++11'
        defines '__STDC_LIMIT_MACROS'

    project 'PocoNet'
        location 'build'
        kind 'StaticLib'
        uuid '65BCF1EB-A936-4688-B1F4-7073B4ACE736'
        defines
        {
            'PCRE_STATIC',
            'POCO_STATIC',
            'POCO_NO_AUTOMATIC_LIBS',
        }
        files
        {
            'src/Poco/*.h',
            'src/Poco/*.c',
            'src/Poco/*.cpp',
            'src/Poco/Net/*.h',
            'src/Poco/Net/*.cpp',
        }
        includedirs
        {
            'src'
        }
        libdirs 'bin'


    project 'UnitTest'
        language 'C++'
        kind 'ConsoleApp'
        location 'build'
        uuid '9C08AC41-18D8-4FB9-80F2-01F603917025'
        defines 
        {
            'GTEST_HAS_TR1_TUPLE=0',
            'PCRE_STATIC',
            'POCO_STATIC',
            'POCO_NO_AUTOMATIC_LIBS',
        }
        files
        {
            'test/*.h',
            'test/*.cpp',
            'dep/gtest/src/gtest-all.cc',
        }
        includedirs
        {
            'src',
            'dep/gtest',
            'dep/gtest/include',
        }
        links 'PocoNet'

