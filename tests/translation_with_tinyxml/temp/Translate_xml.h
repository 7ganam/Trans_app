#include <string>
#include "tinyxml.h"
#include <iostream>

#ifndef Translat_XML
#define Translat_XML
 
bool iequals(const std::string& a, const std::string& b );
int Translate_xml(std::string&  return_str,const char *Dict_file_name,std::string goal_word);
 
 
#endif
