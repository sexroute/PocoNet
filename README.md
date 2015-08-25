PocoNet
=======

[Poco](http://pocoproject.org/)'s TCP and HTTP network module, extracted for embedded device(Android, iOS, Window Phone) usage.


## Installation

First, Obtain [premake5](http://premake.github.io/download.html) toolchain

### Build on Windows (Windows 7 x64)

1. Simply run `msvc2013.bat` to generate Visual C++ 2013 solution files.

### Build on Linux (Ubuntu 14.04 x64)

1. Type `premake5 gmake && make config=release` in your terminal window.

### Build for Android (Hosted on Windows 7 x64)

1. Set environment variable `ANDROID_NDK` as root directory of your NDK path.
2. Simply run `build-android.bat`.

### Build for iOS(Hosted on OSX)

1. Open XCode project in directory 'xcode'
