CinderDrawing
=============

Simple drawing application built with Cinder. It now includes both an Xcode project and a Visual Studio solution. 

On the Mac side, I'm using Xcode 5 and Cinder 0.8.5 Mac. On Windows, I am using Visual Studio 2013 and Cinder 0.8.5 VC2012. 

In order to get it to build correctly with VS2013, you need to download the latest copy of the Boost source code, build it, and replace the version of Boost that Cinder bundles with the freshly build copy. This is because the compiled Boost libraries are out of date and will not function with VS2013. 

http://libcinder.org

http://www.boost.org

=============

This one is pretty simple; just build it and drag your mouse! 
