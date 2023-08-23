Library is from [SimpleTelnetClient GitHub](https://github.com/kmansoo/SimpleTelnetClient).

# Prerequiste

You must install [Boost](https://www.boost.org/doc/libs/1_83_0/more/getting_started/windows.html) before compiling the code.

Follow point **5.1** to build boost.

You must have a folder named bin.v2 in your Boost root folder at the end.

# Configure the Visual Studio project

Open the Visual Studio solution. Open project properties.

## Link to include directory

In "C/C++ > General > Additional Include Directories", add the path to your Boost root.

## Link to lib directory

Create a directory named dependency and put in it the following file :

- libboost_chrono-vc143-mt-gd-x64-1_82.lib
- libboost_thread-vc143-mt-gd-x64-1_82.lib

They can be respectively found in *"boost root/bin.v2/libs/chrono/build/msvc-14.3/debug/link-static/threading-multi"* and *"boost root/bin.v2/libs/thread/build/msvc-14.3/debug/link-static/threadapi-win32/threading-multi"*

Back in project properties, under "Linker > General > Additional Library Directories", add the path to the newly created dependency directory.

# Usage

To execute the program, type in a terminal : **.\simpletelnetclient.exe ip port**.

If *ip* and *port* are not defined, default are:
- IP: 127.0.0.1
- port: 9105

That correspond to the K-ROSET virtual controller.

Then, the program will loop asking you a position (X, Y, Z, O, A, T) and move the robot to it.