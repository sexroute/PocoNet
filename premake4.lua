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
            'POCO_NO_UNWINDOWS',
        }
        links 
        {
            'ws2_32', 
            'iphlpapi',
        }

    configuration 'gmake'
        defines '__STDC_LIMIT_MACROS'
        links 'pthread'

    project 'libpoco'
        location 'build'
        kind 'StaticLib'
        uuid '65BCF1EB-A936-4688-B1F4-7073B4ACE736'
        defines
        {
            'PCRE_STATIC',
            'POCO_STATIC',
            'POCO_NO_STAT64',
            'POCO_NO_AUTOMATIC_LIBS',
        }
        files
        {
            'src/Poco/*.c',
            'src/Poco/*.cc',
            'src/Poco/*.h',
            'src/Poco/AbstractObserver.cpp',
            'src/Poco/ActiveDispatcher.cpp',
            'src/Poco/ArchiveStrategy.cpp',
            'src/Poco/Ascii.cpp',
            'src/Poco/ASCIIEncoding.cpp',
            'src/Poco/AsyncChannel.cpp',
            'src/Poco/AtomicCounter.cpp',
            'src/Poco/Base32Decoder.cpp',
            'src/Poco/Base32Encoder.cpp',
            'src/Poco/Base64Decoder.cpp',
            'src/Poco/Base64Encoder.cpp',
            'src/Poco/BinaryReader.cpp',
            'src/Poco/BinaryWriter.cpp',
            'src/Poco/Bugcheck.cpp',
            'src/Poco/ByteOrder.cpp',
            'src/Poco/Channel.cpp',
            'src/Poco/Checksum.cpp',
            'src/Poco/Clock.cpp',
            'src/Poco/Condition.cpp',
            'src/Poco/Configurable.cpp',
            'src/Poco/ConsoleChannel.cpp',
            'src/Poco/CountingStream.cpp',
            'src/Poco/DateTime.cpp',
            'src/Poco/DateTimeFormat.cpp',
            'src/Poco/DateTimeFormatter.cpp',
            'src/Poco/DateTimeParser.cpp',
            'src/Poco/Debugger.cpp',
            'src/Poco/DeflatingStream.cpp',
            'src/Poco/DigestEngine.cpp',
            'src/Poco/DigestStream.cpp',
            'src/Poco/DirectoryIterator.cpp',
            'src/Poco/DirectoryIteratorStrategy.cpp',
            'src/Poco/DirectoryWatcher.cpp',
            'src/Poco/Environment.cpp',
            'src/Poco/Error.cpp',
            'src/Poco/ErrorHandler.cpp',
            'src/Poco/Event.cpp',
            'src/Poco/EventArgs.cpp',
            --'src/Poco/EventLogChannel.cpp',
            'src/Poco/Exception.cpp',
            'src/Poco/FIFOBufferStream.cpp',
            'src/Poco/File.cpp',
            'src/Poco/FileChannel.cpp',
            'src/Poco/FileStream.cpp',
            'src/Poco/FileStreamFactory.cpp',
            'src/Poco/Format.cpp',
            'src/Poco/Formatter.cpp',
            'src/Poco/FormattingChannel.cpp',
            'src/Poco/FPEnvironment.cpp',
            'src/Poco/Glob.cpp',
            'src/Poco/Hash.cpp',
            'src/Poco/HashStatistic.cpp',
            'src/Poco/HexBinaryDecoder.cpp',
            'src/Poco/HexBinaryEncoder.cpp',
            'src/Poco/InflatingStream.cpp',
            'src/Poco/Latin1Encoding.cpp',
            'src/Poco/Latin2Encoding.cpp',
            'src/Poco/Latin9Encoding.cpp',
            'src/Poco/LineEndingConverter.cpp',
            'src/Poco/LocalDateTime.cpp',
            'src/Poco/LogFile.cpp',
            'src/Poco/Logger.cpp',
            'src/Poco/LoggingFactory.cpp',
            'src/Poco/LoggingRegistry.cpp',
            'src/Poco/LogStream.cpp',
            'src/Poco/Manifest.cpp',
            'src/Poco/MD4Engine.cpp',
            'src/Poco/MD5Engine.cpp',
            'src/Poco/MemoryPool.cpp',
            'src/Poco/MemoryStream.cpp',
            'src/Poco/Message.cpp',
            'src/Poco/Mutex.cpp',
            'src/Poco/NamedEvent.cpp',
            'src/Poco/NamedMutex.cpp',
            'src/Poco/NestedDiagnosticContext.cpp',
            'src/Poco/Notification.cpp',
            'src/Poco/NotificationCenter.cpp',
            'src/Poco/NotificationQueue.cpp',
            'src/Poco/NullChannel.cpp',
            'src/Poco/NullStream.cpp',
            'src/Poco/NumberFormatter.cpp',
            'src/Poco/NumberParser.cpp',
            'src/Poco/NumericString.cpp',
            --'src/Poco/OpcomChannel.cpp',
            'src/Poco/Path.cpp',
            'src/Poco/PatternFormatter.cpp',
            'src/Poco/Pipe.cpp',
            'src/Poco/PipeImpl.cpp',
            'src/Poco/PipeStream.cpp',
            'src/Poco/PriorityNotificationQueue.cpp',
            'src/Poco/Process.cpp',
            'src/Poco/PurgeStrategy.cpp',
            'src/Poco/Random.cpp',
            'src/Poco/RandomStream.cpp',
            'src/Poco/RefCountedObject.cpp',
            'src/Poco/RegularExpression.cpp',
            'src/Poco/RotateStrategy.cpp',
            'src/Poco/Runnable.cpp',
            'src/Poco/RWLock.cpp',
            'src/Poco/Semaphore.cpp',
            'src/Poco/SHA1Engine.cpp',
            'src/Poco/SharedLibrary.cpp',
            'src/Poco/SharedMemory.cpp',
            'src/Poco/SignalHandler.cpp',
            'src/Poco/SimpleFileChannel.cpp',
            'src/Poco/SortedDirectoryIterator.cpp',
            'src/Poco/SplitterChannel.cpp',
            'src/Poco/Stopwatch.cpp',
            'src/Poco/StreamChannel.cpp',
            'src/Poco/StreamConverter.cpp',
            'src/Poco/StreamCopier.cpp',
            'src/Poco/StreamTokenizer.cpp',
            'src/Poco/String.cpp',
            'src/Poco/StringTokenizer.cpp',
            'src/Poco/SynchronizedObject.cpp',
            'src/Poco/SynchronizedObject.cpp',
            --'src/Poco/SyslogChannel.cpp',
            'src/Poco/Task.cpp',
            'src/Poco/TaskManager.cpp',
            'src/Poco/TaskNotification.cpp',
            'src/Poco/TeeStream.cpp',
            'src/Poco/TemporaryFile.cpp',
            'src/Poco/TextBufferIterator.cpp',
            'src/Poco/TextConverter.cpp',
            'src/Poco/TextEncoding.cpp',
            'src/Poco/TextIterator.cpp',
            'src/Poco/Thread.cpp',
            'src/Poco/ThreadLocal.cpp',
            'src/Poco/ThreadPool.cpp',
            'src/Poco/ThreadTarget.cpp',
            'src/Poco/TimedNotificationQueue.cpp',
            'src/Poco/Timer.cpp',
            'src/Poco/Timespan.cpp',
            'src/Poco/Timestamp.cpp',
            'src/Poco/Timezone.cpp',
            'src/Poco/Token.cpp',
            'src/Poco/Unicode.cpp',
            'src/Poco/UnicodeConverter.cpp',
            'src/Poco/URI.cpp',
            'src/Poco/URIStreamFactory.cpp',
            'src/Poco/URIStreamOpener.cpp',
            'src/Poco/UTF8Encoding.cpp',
            'src/Poco/UTF8String.cpp',
            'src/Poco/UTF16Encoding.cpp',
            'src/Poco/UTF32Encoding.cpp',
            'src/Poco/UUID.cpp',
            'src/Poco/UUIDGenerator.cpp',
            'src/Poco/Var.cpp',
            'src/Poco/VarHolder.cpp',
            'src/Poco/VarIterator.cpp',
            'src/Poco/Void.cpp',
            'src/Poco/Windows1250Encoding.cpp',
            'src/Poco/Windows1251Encoding.cpp',
            'src/Poco/Windows1252Encoding.cpp',
            'src/Poco/WindowsConsoleChannel.cpp',
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
        if os.get() == 'linux' then
        buildoptions '-std=c++11'
        end
        defines
        {
            'GTEST_HAS_TR1_TUPLE=0',
            'PCRE_STATIC',
            'POCO_STATIC',
            'POCO_NO_AUTOMATIC_LIBS',
        }
        files
        {
            'test/**.cpp',
            'dep/gtest/src/gtest-all.cc',
        }
        includedirs
        {
            'src',
            'dep/gtest',
            'dep/gtest/include',
        }
        links 'libpoco'

