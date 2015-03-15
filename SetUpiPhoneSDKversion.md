1) Download Xcode from [this\_wiki](https://code.google.com/p/spark-opengles/wiki/UsefulLinks) with version of sdk you need

2) Go to
/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs

3) Create a symbolic link from Xcode's sdk version which you downloaded here

ln -vs /path/toXcode/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOSx.y.sdk iPhoneOSx.y.sdk