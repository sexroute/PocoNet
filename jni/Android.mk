#
# Poco Library Net Module
# http://www.appinf.com/docs/poco/99300-AndroidPlatformNotes.html
#

LOCAL_PATH := $(call my-dir)/../src

include $(CLEAR_VARS)
LOCAL_MODULE     := poco
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_CFLAGS     := -DPOCO_ANDROID -DPOCO_NO_FPENVIRONMENT -DPOCO_NO_WSTRING -DPOCO_NO_SHAREDMEMORY
LOCAL_SRC_FILES  := \
    Poco/pcre_chartables.c \
    Poco/pcre_compile.c \
    Poco/pcre_exec.c \
    Poco/pcre_fullinfo.c \
    Poco/pcre_globals.c \
    Poco/pcre_maketables.c \
    Poco/pcre_newline.c \
    Poco/pcre_ord2utf8.c \
    Poco/pcre_study.c \
    Poco/pcre_tables.c \
    Poco/pcre_try_flipped.c \
    Poco/pcre_ucd.c \
    Poco/pcre_valid_utf8.c \
    Poco/pcre_xclass.c \
    Poco/ASCIIEncoding.cpp \
    Poco/AtomicCounter.cpp \
    Poco/Base64Decoder.cpp \
    Poco/Base64Encoder.cpp \
    Poco/Bugcheck.cpp \
    Poco/ByteOrder.cpp \
    Poco/CountingStream.cpp \
    Poco/DateTime.cpp \
    Poco/DateTimeFormat.cpp \
    Poco/DateTimeFormatter.cpp \
    Poco/DateTimeParser.cpp \
    Poco/DirectoryIterator.cpp \
    Poco/Environment.cpp \
    Poco/ErrorHandler.cpp \
    Poco/Exception.cpp \
    Poco/Event.cpp \
    Poco/File.cpp \
    Poco/Latin1Encoding.cpp \
    Poco/Latin2Encoding.cpp \
    Poco/Latin9Encoding.cpp \
    Poco/LocalDateTime.cpp \
    Poco/MemoryPool.cpp \
    Poco/MemoryStream.cpp \
    Poco/Mutex.cpp \
    Poco/NumberFormatter.cpp \
    Poco/NumberParser.cpp \
    Poco/Path.cpp \
    Poco/RefCountedObject.cpp \
    Poco/RegularExpression.cpp \
    Poco/Runnable.cpp \
    Poco/RWLock.cpp \
    Poco/SignalHandler.cpp \
    Poco/StreamCopier.cpp \
    Poco/String.cpp \
    Poco/StringTokenizer.cpp \
    Poco/TextConverter.cpp \
    Poco/TextEncoding.cpp \
    Poco/TextIterator.cpp \
    Poco/Thread.cpp \
    Poco/ThreadLocal.cpp \
    Poco/Timespan.cpp \
    Poco/Timestamp.cpp \
    Poco/Timezone.cpp \
    Poco/UnicodeConverter.cpp \
    Poco/UTF8Encoding.cpp \
    Poco/URI.cpp \
    Poco/UTF16Encoding.cpp \
    Poco/Windows1250Encoding.cpp \
    Poco/Windows1251Encoding.cpp \
    Poco/Windows1252Encoding.cpp \
    Poco/Net/DatagramSocket.cpp \
    Poco/Net/DatagramSocketImpl.cpp \
    Poco/Net/DNS.cpp \
    Poco/Net/HostEntry.cpp \
    Poco/Net/HTTPBasicCredentials.cpp \
    Poco/Net/HTTPBufferAllocator.cpp \
    Poco/Net/HTTPChunkedStream.cpp \
    Poco/Net/HTTPClientSession.cpp \
    Poco/Net/HTTPCookie.cpp \
    Poco/Net/HTTPFixedLengthStream.cpp \
    Poco/Net/HTTPHeaderStream.cpp \
    Poco/Net/HTTPMessage.cpp \
    Poco/Net/HTTPRequest.cpp \
    Poco/Net/HTTPResponse.cpp \
    Poco/Net/HTTPSession.cpp \
    Poco/Net/HTTPStream.cpp \
    Poco/Net/IPAddress.cpp \
    Poco/Net/MediaType.cpp \
    Poco/Net/MessageHeader.cpp \
    Poco/Net/NameValueCollection.cpp \
    Poco/Net/NetException.cpp \
    Poco/Net/NetworkInterface.cpp \
    Poco/Net/RawSocket.cpp \
    Poco/Net/RawSocketImpl.cpp \
    Poco/Net/Socket.cpp \
    Poco/Net/SocketAddress.cpp \
    Poco/Net/SocketImpl.cpp \
    Poco/Net/SocketStream.cpp \
    Poco/Net/StreamSocket.cpp \
    Poco/Net/StreamSocketImpl.cpp

include $(BUILD_STATIC_LIBRARY)
