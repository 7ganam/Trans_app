in this path the translation action is defined in a header file rather in a shared lib ..this is a bad programming procedure but 
it will be taken for the sake of ease of development
the final app should contain the shared library version
this shared library contains  the codes of "tinyxml" library only

in the bin file run :
g++ ../src/*.cpp  -I../include -c -fPIC
to creat the object files 

then run
gcc -shared *.o -o libtinyxml.so -I../include

the library would created in the bin folder

you can copy the lib to the test file to test it with main.cpp
to build a function "main.cpp" with the library ..include the header files of tinyxml and Translate_xml.h then run :
g++  main.cpp    -ltinyxml -L. -Wl,-rpath=.


