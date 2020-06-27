#ifndef EmailFilter_h
#define EmailFilter_h
#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
const std::string WHITESPACE = " \n\r\t\f\v";
std::string ltrim(const std::string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
	return rtrim(ltrim(s));
} 
int countWords(string str)  
{  
    int i = 0;  
    int wc = 0; // word count  
  
    // Scan all characters one by one  
    while (i<str.length())  
    {  
        // If next character is a separator, set the  
        // state as OUT  
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')  
            wc++;
  
        // If next character is not a word separator and  
        // state is OUT, then set the state as IN and  
        // increment word count  
        
        // Move to next character  
        ++i;  
    }  
  
    return wc+1;  
} 
class EmailFilter
{
public:
	EmailFilter(string );
	EmailFilter(string , int);
	string getFilter();
	int getSpamFilterValue();
	void setFilter(string);
	void setSpamFilterValue(int); 
private:
	string word;
	int spamFilterValue;

};
EmailFilter::EmailFilter(string input)
{
	word = trim(input);
	spamFilterValue = countWords(word);
}

EmailFilter::EmailFilter(string input, int spamValue)
{
	word = input;
	spamFilterValue = spamValue;
}

void EmailFilter::setFilter(string FilterString)
{
	word = FilterString;
}

void EmailFilter::setSpamFilterValue(int value)
{
	spamFilterValue = value;
}

string EmailFilter::getFilter()
{
	return word;
}

int EmailFilter::getSpamFilterValue()
{
	return spamFilterValue;
}

#endif