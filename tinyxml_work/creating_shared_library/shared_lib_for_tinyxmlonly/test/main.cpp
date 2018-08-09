#include  "tinyxml.h"
#include  "tinystr.h"
#include  "Translate_xml.h"

#include  <iostream>
#include  <string>
using namespace std;

// this file shows how to use the function   "Translate_xml" defined in the header file "Translate_xml.h"
// you have to link with the shared library libtinyxml.so 
// you have to copy the preparation block first before using it 
// to build run 
//  g++  main.cpp -ltinyxml -L. -Wl,-rpath=. 
// 



int main(int argc, char* argv[])
{
 
    //preparation block for calling   Translate_xml(return_str , input ,  doc , root) -------------------
    
                                        std::string  return_str;
                                        const char   *Dict_file_name = "eng-ara.xml";
                                        std::string goal_word="mountain";
                                        TiXmlDocument doc;
                                        TiXmlElement* root;
                                        //opening file
                                        if(!doc.LoadFile(Dict_file_name))
                                        {  
                                            cerr << doc.ErrorDesc() << endl;  
                                            cout<<"failed to open file"<<endl;
                                            return 0; 
                                        }
                                        root = doc.FirstChildElement();
                                        if(root == NULL)
                                        {
                                            cerr << "Failed to load file: No root element." << endl;
                                            doc.Clear();
                                            return 0; 
                                        }
    //---------------------------------------------------------------------------------------------
    
    while(1)
    {
        std::string input;
        cout<<"etner word : ";
        cin>>input;
        
const clock_t begin_time = clock();  
        if( Translate_xml(return_str , input ,  doc , root) )
            cout << "Got text: " << return_str << endl;           
        else
            cout << "notfoun"<<endl;
std::cout <<"time cost: " <<float( clock () - begin_time ) /  CLOCKS_PER_SEC<<endl;	

        
    }

    
	return 0;
}

