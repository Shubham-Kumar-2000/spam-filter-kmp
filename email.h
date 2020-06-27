#ifndef email_h
#define email_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;


class email
{

public:
	email(string , string, string );
	email(string);
	string getMessage();
	string getSubject();
	string getSender();
	vector<string> tokenizeEmail();
	int getSpamScore();
	void setMessage(string);
	void setSubject(string);
	void setSender(string);
	void setSpamScore(int);

private:
	string message;
	string subject;
	string sender;
	int spamScore;
	ifstream inputText;
	ofstream outputText;
};
email::email (string a, string b, string c)
	{
		message = a;
		subject = b;
		sender = c;
		spamScore = 0;
	}


	email::email(string fileInput)
	{
		inputText.open(fileInput.c_str());
		if(inputText.is_open())
		{
			while( getline(inputText, message));
		}
	
		subject = "test";
		sender  = "test";
		spamScore = 0;
	}

	vector<string> email::tokenizeEmail()
	{
		string buf; // Have a buffer string
		stringstream ss(message); // Insert the string into a stream

		vector<string> tokens; // Create vector to hold our words

		while (ss >> buf)
			tokens.push_back(buf);
	
		return tokens;
	}

	string email::getMessage()
	{
		return message;
	}

	string email::getSubject()
	{
		return subject;
	}

	string email::getSender()
	{
		return sender;
	}

	int email::getSpamScore()
	{
		return spamScore;
	}

	void email::setMessage(string EmailMessage)
	{
		message = EmailMessage;
	}

	void email::setSender(string SenderEmail)
	{
		sender = SenderEmail;
	}


	void email::setSubject(string EmailSubject)
	{
		subject = EmailSubject;
	}

	void email::setSpamScore(int EmailSpamScore)
	{
		spamScore = EmailSpamScore;
	}

#endif