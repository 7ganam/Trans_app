#include "Translate_xml.h"
#include <string>
#include "tinyxml.h"
#include <iostream>

bool iequals(const std::string& a, const std::string& b )
{//this is a function to compare to std::strings case insinsitvely
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}



int Translate_xml(std::string&  return_str,const char *Dict_file_name,std::string goal_word)
{//this function translates the (goal_word) and returns the result in the (return_str) using the data in the (Dict_file_name)
 //it returns -1 when failing to open the file and 1 when sucssesful.
    
    
//open the file and make sure it's opened ..else return -1-----------------
	TiXmlDocument doc;
	if(!doc.LoadFile(Dict_file_name))
	{
		std::cerr << doc.ErrorDesc() << std::endl;
		return -1;
	}
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{
		std::cerr << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		return -1;
	}
//-------------------------------------------------------------------------


//moving through the xml file 	-------------------------------------------
	TiXmlElement* text_elem = root->FirstChildElement("text");   
	TiXmlElement* body_elem = text_elem->FirstChildElement("body");
//-------------------------------------------------------------------------

    
//looping over ther words in the xml file----------------------------------
    int counter=0;
	for(TiXmlElement* entry_elem = body_elem->FirstChildElement("entry"); entry_elem != NULL; entry_elem = entry_elem->NextSiblingElement())
	{
        counter++;
       
    //moving through the entrys untill reaching the word (orth)-------------------------------------------   
        TiXmlElement* form_elem = entry_elem->FirstChildElement("form");         
        TiXmlElement* orth_elem = form_elem->FirstChildElement("orth");
    //-----------------------------------------------------------------------------------------------------
    
    //gettng the text in the orthe element-----------------------------------------------------------------
        TiXmlNode* orth_node = orth_elem->FirstChild();
        TiXmlText*         text = orth_node->ToText();
        const char * text_value=text->ValueTStr().c_str();
        std::string str2 = text_value;
    //---------------------------------------------------------------------------------------------------
    
        
    //comparing between goal_word and the word in the entery and setting the return string if right--------  
        if (iequals(goal_word, str2))
        {
            TiXmlElement* sense_elem = entry_elem->FirstChildElement("sense"); 
            TiXmlElement* cit_elem = sense_elem->FirstChildElement("cit");
            TiXmlElement* quote_elem = cit_elem->FirstChildElement("quote");
                ////this is for making sure your reachd the quote element in the xml file ..uncomment to see output
                //                 string quote_elem_Name = quote_elem->Value();
                //                 if(quote_elem_Name == "quote")
                //                 {
                //                     cout << "Got quote" << endl;
                //                 }
            
            TiXmlNode* quote_node = quote_elem->FirstChild();
            TiXmlText*        quote_text = quote_node->ToText();
            const char * quote_text_value=quote_text->ValueTStr().c_str();
            return_str = quote_text_value;
            
        }
    //---------------------------------------------------------------------------------------------------       
	
	}
	
    doc.Clear();
	return 1;
}
 
