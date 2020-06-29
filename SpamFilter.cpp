#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "email.h"
#include "EmailFilter.h"
#include <string>
#include<windows.h>
using namespace std;

void create_pi_table( string pattern, int l2, int *pi)
{
    int length =0;
    pi[0]= 0;
    int i =1;
    while(i < l2)
    {
        if (pattern[i] == pattern[length])
        {
            length ++;
            pi[i] = length;
            i++;
        }
        else
        {
            if (length!=0)
            {
                length = pi[length - 1];
            }
            else
            {
                pi[i]=0;
                i++;
            }
        }
    }
}

int KMP (string original, string pattern)
{
	int count = 0;
    int l1 = original.length();
    int l2 = pattern.length();
    int pi[l2];

    create_pi_table(pattern, l2, pi);

    int i=0, j=0 ;
    while(i < l1)
    {
        if (pattern[j] == original[i])
        {
            i++;
            j++;
        }
        if (j == l2)
        {
            count++;
            j= pi[j-1];
        }

        else if (i < l1 && pattern[j] != original[i])
        {
            if(j !=0)
                j = pi[j-1];
            else
                i = i+1;
        }
    }
	return count;
}

void intro(string str){
	int i=0;
	cout<<"                                         ";
	while (i<str.length())
	{
		cout<<str[i];
		Sleep(100);
		i++;
	}
	Sleep(500);
	while (i>0)
	{
		cout<<"\b \b";
		Sleep(100);
		i--;
	}
}
int main()
{
	intro("WELCOME TO SPAM FILTER");
	char choice;
	cout<<"\nDo you want to give email as a file?[Y/N] : ";
	cin>>choice;
	
	//An email object is created from a text a file
	email testing;
	if(tolower(choice)=='y')
	{
		cout<<"Enter file's relative path : ";
		string path;
		cin>>path;
		testing=(new email(path));
		
	}

	else{
		string subject,sender,message;
		cout<<"Enter Sender : ";
		cin>>sender;
		cin.clear();
		cin.ignore();
		cout<<"Enter Subject : ";
		getline(cin,subject);
		cout<<"Enter message : ";
		getline(cin,message);
		testing=(new email(message,subject,sender));
	}

	//This will create the input stream for the spamwords text file
	ifstream spamwordsTextFileInput;

	// THis is output stream that will output the score for the email
	ofstream outputText;

	//This is a string with all the spam words
	string spamWordsList;

	// This vector will hold all the filters
	vector<EmailFilter> filters;

	//The email is tokenized by white spaces
	vector<string> tokenEmail = testing.tokenizeEmail();

	//Here the list of spam words from the text file is opened from the text file
	string path;
	cout<<"Enter relative path to spam words list : ";
	cin>>path;
	spamwordsTextFileInput.open(path.c_str());
	if(spamwordsTextFileInput.is_open())
	{
		while( getline(spamwordsTextFileInput, spamWordsList)){
			filters.push_back(EmailFilter(spamWordsList));
		}
	}
	else
	{
		cout<<"ERR :\tUnable to open given path.\n\nIf you dont have your own custom spam word list then you can download it from :\nhttps://github.com/Shubham-Kumar-2000/spam-filter-kmp/blob/master/spamWords.txt";
		return 0;
	}
	

	//Spam words are tokenized and put into spamtokens vector
	string buf; 
	stringstream ss(spamWordsList); 
	vector<string> Spamtokens; 
	while (ss >> buf)
		Spamtokens.push_back(buf);

	//spam tokens are put into vector of spam filters
	// for(vector<string>::iterator spamWords = Spamtokens.begin(); spamWords != Spamtokens.end(); ++spamWords)
	// {
	// 	filters.push_back(EmailFilter(*spamWords));
	// }

	//Here the email searched and compared with the spam filters
	// for(int i = 0; i < tokenEmail.size(); i++)
	// {
	// 	for(int j = 0; j < filters.size(); j++)
	// 	{
	// 		EmailFilter currentFilter = filters.at(j);
	// 		if(tokenEmail.at(i) == currentFilter.getFilter())
	// 		{
	// 			testing.setSpamScore(testing.getSpamScore() + currentFilter.getSpamFilterValue());
	// 		}
	// 	}
	// }
	// int sss=0;
	for(int j = 0; j < filters.size(); j++)
	{
		EmailFilter currentFilter = filters.at(j);
		testing.setSpamScore(testing.getSpamScore()+ KMP(testing.getMessage(),currentFilter.getFilter()) * currentFilter.getSpamFilterValue());
	}
	
	cout << "Email Message: ";
	cout << testing.getMessage();
	cout << "\n";
	cout << "\n";
	cout << "Number of words : ";
	cout << tokenEmail.size();
	cout << "\n";
	cout << "Spam score (Number of words Considered Spam): " ;

	cout << testing.getSpamScore();
	cout << "\n";

	double spamRatio = (double)testing.getSpamScore()/(double)tokenEmail.size();

	cout << "Spam Ratio: ";
	cout << spamRatio;
	cout << "\n";
	if (spamRatio > .15)
	{
		cout << "The spam ratio for this email is greater than .15, hence this email is spam \n";
	}
	
	else
	{
		cout << " This Email had a spam ratio of less than .15, hence this email is not spam \n"; 
	}
}


