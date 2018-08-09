how to creat the shared library containgn the function trans_xml
the shared library contains the function and the codes of "tinyxml" library

in the bin file run :
g++ ../src/*.cpp  -I../include -c -fPIC
to creat the object files 

then run
gcc -shared *.o -o libshared_trans.so

the library would created in the bin folder

to build a function "main.cpp" with the library ..include the header files in include folder then run
g++  main.cpp    -lshared_trans -L. -Wl,-rpath=.

you can copy the lib to the test file to test it with main.cpp

In case of edit needed in the library..change first in Result folder then apply changes to shared lib
