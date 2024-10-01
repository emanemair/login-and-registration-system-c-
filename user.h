#pragma once

#include<string>
#include<iostream>
using namespace std; 

class User {

	string  firstName; 
	string lastName;
	string email; 
	string userName; 
	string password; 

public: 
	User(const string& = "", const string& = "",const string& = "",const  string& = "",const string& = ""); 
	void setUser(const string&, const string&, const string&, const string&, const string&);
	void setName(const string&, const string&); 
	void setEmail(const string&); 
	void setUserName(const string&); 
	void setPass(const string&); 
	void print()const; 
	string getName()const; 
	string getEmail()const;
	string getUserName()const; 
	string getPass()const; 
	bool isTheSameUser(const User&)const; 
	const User* getUser()const; 
	bool correctPass(const string&)const ;

};