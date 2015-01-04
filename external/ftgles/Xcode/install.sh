#!/bin/sh

xcodebuild -configuration Release -sdk iphoneos -alltargets clean
xcodebuild -configuration Release -sdk iphoneos -alltargets build
cp build/Release-iphoneos/libFTGLES.a ./libFTGLES-arm.a

xcodebuild -configuration Release -sdk iphonesimulator -alltargets clean
xcodebuild -configuration Release -sdk iphonesimulator -alltargets build
cp build/Release-iphonesimulator/libFTGLES.a ./libFTGLES-sim.a

lipo -o libFTGLES.a -create libFTGLES-arm.a libFTGLES-sim.a
