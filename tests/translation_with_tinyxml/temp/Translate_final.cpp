#include "tinyxml.h"
#include  "tinystr.h"
#include <iostream>
#include <string>
#include "Translate_xml.h"

// this example shows how to use the function 
// int Translate_xml(std::string&  return_str,const char *Dict_file_name,std::string goal_word)
//this function translates the (goal_word) and returns the result in the (return_str) using the data in the (Dict_file_name)
//it returns -1 when failing to open the file and 1 when sucssesful.
// to run the file you have to link it staticly with the library "libTransxml.a" by running the command :
/*
g++ -static Translat_final.cpp -L. -lTransxml -o Translat_final
*/
//the static library is composed of my implementation of the translation function + the object file from the tinyxml files 

using namespace std;


int main(int argc, char* argv[])
{
 
    std::string  return_str;
    const char   *Dict_file_name = "eng-ara.xml";
    std::string goal_word=argv[1];
    
     const clock_t begin_time = clock();  
            if(Translate_xml(return_str,Dict_file_name,goal_word) == -1)
                return 1;
     std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;	

    cout << "Translated successfully." << endl;
    cout << "Got text: " << return_str << endl;
	return 0;
}


