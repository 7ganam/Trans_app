#include  "tinyxml.h"
#include  "tinystr.h"
#include  <iostream>
#include  <string>
#include  "trans_xml.h"
#include  <typeinfo>

using namespace std;

/*
bool iequals(const string& a, const string& b );
int Translate_xml(std::string&  return_str, std::string& goal_word , TiXmlDocument doc , TiXmlElement* root);*/

int main(int argc, char* argv[])
{
     

     
    
    
    
    //preparation for calling   Translate_xml(return_str , input ,  doc , root) -------------------
    
                                        std::string  return_str;
                                        const char   *Dict_file_name = "eng-ara.xml";
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


/*

int Translate_xml(std::string&  return_str, std::string& goal_word , TiXmlDocument doc , TiXmlElement* root)
{//this function translates the (goal_word) and returns the result in the (return_str) using the data in the (Dict_file_name)
//  it returns 1 when finding a translation and 0 when not
    




// moving through the xml file 	-------------------------------------------
	TiXmlElement* text_elem = root->FirstChildElement("text");  
	TiXmlElement* body_elem = text_elem->FirstChildElement("body");
// -------------------------------------------------------------------------
    
// looping over ther words in the xml file----------------------------------
    int counter=0;
    
	for(TiXmlElement* entry_elem = body_elem->FirstChildElement("entry"); entry_elem != NULL; entry_elem = entry_elem->NextSiblingElement())
	{
        counter++;
       
//     moving through the entrys untill reaching the word (orth)-------------------------------------------   
        TiXmlElement* form_elem = entry_elem->FirstChildElement("form");         
        TiXmlElement* orth_elem = form_elem->FirstChildElement("orth");
//     -----------------------------------------------------------------------------------------------------
//     gettng the text in the orthe element-----------------------------------------------------------------
        TiXmlNode* orth_node = orth_elem->FirstChild();
        TiXmlText*         text = orth_node->ToText();
        const char * text_value=text->ValueTStr().c_str();
        std::string str2 = text_value;
//     ---------------------------------------------------------------------------------------------------
    
        
//     comparing between goal_word and the word in the entery and setting the return string if right--------  
        if (iequals(goal_word, str2))
        {
            TiXmlElement* sense_elem = entry_elem->FirstChildElement("sense"); 
            TiXmlElement* cit_elem = sense_elem->FirstChildElement("cit");
            TiXmlElement* quote_elem = cit_elem->FirstChildElement("quote");
// //                 this is for making sure your reachd the quote element in the xml file ..uncomment to see output
//                                 string quote_elem_Name = quote_elem->Value();
//                                 if(quote_elem_Name == "quote")
//                                 {
//                                     cout << "Got quote" << endl;
//                                 }
            
            TiXmlNode* quote_node = quote_elem->FirstChild();
            TiXmlText*        quote_text = quote_node->ToText();
            const char * quote_text_value=quote_text->ValueTStr().c_str();
            return_str = quote_text_value;
            return 1;

        }
//     ---------------------------------------------------------------------------------------------------       
	
	}
	doc.Clear();
	return 0;
    
	
    
}







bool iequals(const string& a, const string& b )
{//this is a function to compare to std::strings case insinsitvely
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}*/
