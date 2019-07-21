#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>

class TBE_Profile
{
	using TBE_function=std::function<bool(std::string, std::string, std::string)>;
	
	//*********************************************************
	std::map<std::string, TBE_function> items;
	TBE_function tbe_filter=nullptr;
	//*********************************************************

	
public:

	//*********************************************************
	void installFilter(TBE_function tbe_func) { tbe_filter = tbe_func; }
	void removeFilter() { tbe_filter = nullptr; }
	bool is_filter_present() { return tbe_filter!=nullptr; }
	//*********************************************************
 
	const TBE_function operator[](std::string index);
	bool registerforToken(std::string token_str, TBE_function tbe_func);
	bool removeToken(std::string token_str);

	TBE_function getTBE_func(std::string token_str);
	bool exec_func(std::string tag, std::string& value, std::string& data);
	//*********************************************************
};

class GDML_SYMBOL_PROFILE
{
	  char tag_seperator{ ',' };
	  char tag_value_seperator{ ':' };
	  char tag_open{ '[' };
	  char tag_close{ ']' };

public:
	GDML_SYMBOL_PROFILE() {}
	GDML_SYMBOL_PROFILE(const  char _tag_seperator, const  char _tag_value_seperator, const  char _tag_open, const  char _tag_close)
		:tag_seperator(_tag_seperator), tag_value_seperator(_tag_value_seperator), tag_open(_tag_open), tag_close(_tag_close){}
	//----------------------------------------
	void setTagSeperator(char _tag_seperator) { tag_seperator = _tag_seperator; }
	char getTagSeperator() { return tag_seperator; }
	//----------------------------------------
	void setTagValueSeperator(char _tag_value_seperator) { tag_value_seperator = _tag_value_seperator; }
	char getTagValueSeperator() { return tag_value_seperator; }
	//----------------------------------------
	void setOpenTag(char opentag_character) { tag_open = opentag_character; }
	char getOpenTag() { return tag_open; }
	//----------------------------------------
	void setCloseTag(char closetag_character) { tag_close = closetag_character; }
	char getCloseTag() { return tag_close; }
	//----------------------------------------

};

class GDMLParser
{
	
	GDML_SYMBOL_PROFILE syntax_profile;
public:
	GDMLParser() {}
	GDMLParser(GDML_SYMBOL_PROFILE _syntax_profile) :syntax_profile(_syntax_profile) {}
	void setSyntaxProfile(GDML_SYMBOL_PROFILE _syntax_profile) { syntax_profile = _syntax_profile; }

    int exec(const std::string& str,TBE_Profile profile);

private:

	  bool isClosed(const std::string& s1, const std::string& s2);
	  bool isClosed(std::string& str)
	{
		return str == "/";
	}
	  const std::string& trim(std::string& tag_text, char trimchar = ' ');
	  std::vector<std::string> splitIntoTokens(const std::string& tag_text, const char seperator = ' ');
	  std::pair<std::string, std::string>splitIntoToken(const std::string& text, const char seperator = ' ');
	//*********************************************************
};

