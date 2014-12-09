rem ;
rem ; ANDROID_NDK must be defined first
rem ;

set PATH=%PATH%;%ANDROID_NDK%;
ndk-build.cmd NDK_PROJECT_PATH=./
pause
