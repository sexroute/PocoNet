PocoNet
=======

Poco's TCP and HTTP network module, extracted for embedded device(Android, iOS, Window Phone) usage.


## Installation

First, Obtain premake toolchain(http://industriousone.com/premake/download)

### Build on Windows (Windows 7 x64)

1. Simply run `build-msvc2012.bat` to generate Visual C++ 2012 solution files.

### Build on Linux (Ubuntu 12.04 x64)

1. Type `premake4 gmake` in your terminal window.
2. Type `make config=release64` in your terminal window.

### Build for Android (Hosted in Windows 7 x64)

1. Set environment variable `ANDROID_NDK` to root directory of your NDK path.
2. Simply run `build-android.bat`.

### Build for iOS

1. Type `premake4 xcode4` in your terminal window.

### Build for Windows Phone

(to be continued.)
