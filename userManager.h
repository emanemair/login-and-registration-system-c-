#pragma once
#include<vector>
#include"user.h"


class UserManager {
	vector<User> users; 
	
public:

	UserManager(); 
	void addUser(const string&, const string&, const string&, const string&, const string&); 
	void addUser(User&); 
	const vector<User>* getUsers()const; 
	const User* searchUserByEmail(const string&)const;
	const User* searchUsrByUserName(const string&)const;
	bool isFoundByEmail(const string&)const; 
	bool isFoundByUserName(const string&) const; 
	bool isValidPassword(const string&)const;  
	bool isValidEmail(const string&)const; 
	bool isValidUserName(const string&)const;
	void print()const; 
	bool correctPassword(const string & , const string&) const; 
	void userRegistration(); 
	void userLogin() ;
	bool uniqueUserName(const string&)const;
	// void changePass(); 

};