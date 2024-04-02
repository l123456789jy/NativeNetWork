# NativeNetWork
C++ 网络请求

https://github.com/ithewei/libhv

cmake方式：

### Android

```
#https://developer.android.com/ndk/downloads
#export ANDROID_NDK_ROOT=~/Downloads/android-ndk-r21b
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake" -DANDROID_ABI="arm64-v8a" -DANDROID_PLATFORM=android-29
// 开启https
cmake .. -DWITH_OPENSSL=ON
cmake --build . --target hv --config Release
```

