#include<iostream>
#include<string>
#include"user.h"
using namespace std; 



void User::setUser(const string& fname, const string& lname, const string& email, const string& userName, const string& pass) {
	this->firstName = fname; 
	this->lastName = lname; 
	this->email = email; 
	this->userName = userName; 
	this->password = pass; 
}


User::User(const string& fname, const string& lname, const string& email, const string& userName, const string& pass) {
	this->setUser(fname, lname, email, userName, pass); 
}

void User::setEmail(const string& email) {
	this->email = email; 
}

void User::setName(const string& fname, const string& lname) {
	this->firstName = fname; 
	this->lastName = lname; 
}

void User::setUserName(const string& uName) {
	this->userName = uName; 
}

void User::setPass(const string& pass) {
	this->password = pass; 
}

const User* User::getUser()const {

	return this; 
}


string User::getName()const {
	return this->firstName +" " +  this->lastName;
}


string User::getEmail()const {
	return this->email; 
}

string User::getUserName()const {
	return this->userName; 
}

string User::getPass()const {
	return this->password; 
}
bool User::isTheSameUser(const User& otherUser)const {
	return this->getEmail() == otherUser.getEmail(); 
}

void User::print()const {
	cout << this->getName() << " Account Data : \n "; 
	cout << "email: " << this->getEmail() << "\n"; 
	cout << "User- Name: " << this->userName << "\n"; 

}

bool User::correctPass(const string& pass)const {
	if (this->password == pass)
		return true; 
	return false; 
}




/*
UserManager Class Implemintation
*/

#include"userManager.h"
#include<regex>




UserManager::UserManager() {

	User::User();
}

bool UserManager::isValidPassword(const string& password)const {
	// Regex pattern for a valid password: at least 8 characters, at least one letter, and at least one symbol
	const regex pattern(R"((?=.*[a-zA-Z])(?=.*[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]).{8,})");

	// Check if the password matches the regex pattern
	return regex_match(password, pattern);
}

bool UserManager::isValidEmail(const string& email)const {

	// Define a regular expression for a typical email pattern
	const regex pattern(R"((\w+)(\.|\_)?(\w*)@(\w+)(\.(\w+))+)");

	// Return whether the email matches the regex
	return regex_match(email, pattern);
}

bool UserManager::isValidUserName(const string& userName)const {

	// Define a regex pattern for the username
	regex pattern("^[A-Za-z][A-Za-z0-9_]*$");

	// Check if the username matches the pattern
	return regex_match(userName, pattern);
}

void UserManager::addUser(const string& firstName, const string& lastName, const string& email, const string& uName, const string& pass) {
	User newUser;
	newUser.setUser(firstName, lastName, email, uName, pass);
	users.push_back(newUser);
}
bool UserManager::isFoundByUserName(const string& uName) const {
	if (!this->users.empty()) {

		if (this->isValidUserName(uName)) {
			for (auto itr = this->users.begin(); itr != this->users.end(); ++itr) {
				if (itr->getUserName() == uName) {
					return true;
				}
			}
		}

	}

	return false;
}


bool UserManager::isFoundByEmail(const string& email)const {
	if (!this->users.empty()) {

		if (this->isValidEmail(email)) {
			for (auto itr = this->users.begin(); itr != this->users.end(); ++itr) {
				if (itr->getEmail() == email) {
					return true;
				}
			}
		}

	}

	return false;
}

const User* UserManager::searchUserByEmail(const string& email) const {

	// Check if the users list is not empty
	if (this->users.empty()) {
		return nullptr;
	}

	// Validate the email format
	if (!this->isValidEmail(email)) {
		return nullptr;
	}

	// Check if a user with this email is found
	if (!this->isFoundByEmail(email)) {
		return nullptr;
	}

	// Iterate through the list of users
	for (auto itr = this->users.begin(); itr != this->users.end(); ++itr) {
		// Check if the current user's email matches the given email
		if (itr->getEmail() == email) {
			return &(*itr);  // Return a pointer to the found user object
		}
	}

	return nullptr;  // Return nullptr if no matching user is found
}


const User* UserManager::searchUsrByUserName(const string & uName) const {
	
	// Check if the users list is empty
	if (this->users.empty()) {
		return nullptr;
	}

	// Check if the username is valid
	if (!this->isValidUserName(uName)) {
		return nullptr;
	}

	// Check if the user is found by the username
	if (!this->isFoundByUserName(uName)) {
		return nullptr;
	}

	// Iterate through the users to find the matching username
	for (auto itr = this->users.begin(); itr != this->users.end(); ++itr) {
		if (itr->getUserName() == uName) {
			return &(*itr);
		}
	}

	return nullptr;
}



const vector<User>* UserManager::getUsers()const {

	if (!this->users.empty()) {
		return &this->users;
	}
	return nullptr;
}


void UserManager::print() const {
	if (!this->users.empty()) {
		for (auto itr = this->users.begin(); itr != this->users.end(); ++itr) {
			itr->print(); 
		}
	}
	else {
		cout << "No Users Fonud!\n"; 
	}
}


bool UserManager::correctPassword(const string& domain, const string& pass)const {

	if ((isValidEmail(domain)) && (this->searchUserByEmail(domain)!=nullptr)) {
		auto itr = this->searchUserByEmail(domain);
		return itr->correctPass(pass); 
	}
	if (isValidUserName(domain) && (this->searchUsrByUserName(domain) != nullptr)) {
		auto itr = this->searchUsrByUserName(domain); 
		return itr->correctPass(pass); 
	}
	return false; 
}

bool UserManager::uniqueUserName(const string& uName)const {
	if (this->users.empty()) {
		return true;
	}
	for (auto itr = this->users.begin(); itr != this->users.end(); ++itr) {
		if (itr->getUserName() == uName) {
			return false; 
		}
	}
	return true; 
}


void UserManager::addUser(User& newUser) {
	this->users.push_back(newUser);
}


void UserManager::userRegistration() {
	string fName, lName, email, uName, pass;
	
	cout << "Start creating your account\n";
	cout << "Enter your name (first name, last name):\n";
	cin >> fName >> lName;

	// Email registration
	do {
		cout << "Enter Your Email:\n";
		cin >> email;

		// Check if the user wants to exit by typing "-1"
		if (email == "-1") {
			cout << "Exiting...\n";
			return; // Exit the function entirely
		}

		// Check if the email is valid and not already registered
		if (!isValidEmail(email) || this->isFoundByEmail(email)) {
			cout << "Invalid Email, try again or type -1 to exit.\n";
		}
	} while (!isValidEmail(email) || this->isFoundByEmail(email));

	// Proceed with username creation if the user hasn't exited
	if (email != "-1") {
		do {
			cout << "Create User-Name:\n";
			cin >> uName;

			// Check if the user wants to exit by typing "-1"
			if (uName == "-1") {
				cout << "Exiting...\n";
				return; // Exit the function entirely
			}

			// Check if the username is valid and unique
			if (!isValidUserName(uName) || !uniqueUserName(uName)) {
				cout << "Invalid username. Your username must meet the following criteria:\n";
				cout << "- Must start with a letter (A-Z, a-z)\n";
				cout << "- Can contain letters (A-Z, a-z), numbers (0-9), and underscores (_)\n";
				cout << "- Cannot contain spaces or special characters.\n";
				cout << "Try again.\n";
			}
		} while (!isValidUserName(uName) || !uniqueUserName(uName));

		// Proceed with password creation if the user hasn't exited
		if (uName != "-1") {
			do {
				cout << "Create Password:\n";
				cin >> pass;

				// Check if the user wants to exit by typing "-1"
				if (pass == "-1") {
					cout << "Exiting...\n";
					return; // Exit the function entirely
				}

				// Check if the password is valid
				if (!isValidPassword(pass)) {
					cout << "Invalid password. Your password must meet the following criteria:\n";
					cout << "- At least 8 characters long\n";
					cout << "- Must contain at least one letter (a-z, A-Z)\n";
					cout << "- Must contain at least one symbol (!@#$%^&*()_+-=[]{};:'\"\\|,.<>/?).\n";
					cout << "Try again or type -1 to exit.\n";
				}
			} while (!isValidPassword(pass));
		}

		// If all inputs are valid, create the user and add them to the system
		if (pass != "-1") {
			User newUser(fName, lName, email, uName, pass);
			this->addUser(newUser);
			cout << "Account successfully created!\n";
		}
	}
	else {
		cout << "Exiting...\n";
	}
}


void UserManager::userLogin() {
	string email;

	// Loop for email input and validation
	do {
		cout << "Enter your Email:\n";
		cin >> email;

		// Exit if the user inputs "-1"
		if (email == "-1") {
			cout << "Exiting...\n";
			return; // Exit the function entirely
		}

		// Validate email format
		if (!isValidEmail(email)) {
			cout << "Invalid Email.\n";
			cout << "Try again or type -1 to exit.\n";
		}
		// Check if the email is registered in the system
		else if (!isFoundByEmail(email)) {
			cout << "No account associated with this email.\n";
			cout << "Try again or type -1 to exit.\n";
		}

	} while (!isValidEmail(email) || !isFoundByEmail(email));

	// Proceed with password input if the user hasn't exited
	if (email != "-1") {
		string pass;

		// Loop for password input and validation
		do {
			cout << "Enter your password:\n";
			cin >> pass;

			// Exit if the user inputs "-1"
			if (pass == "-1") {
				cout << "Exiting...\n";
				return; // Exit the function entirely
			}

			// Check if the password is correct for the given email
			if (!this->correctPassword(email, pass)) {
				cout << "Password incorrect. Try again.\n";
				cout << "Try again or type -1 to exit.\n";
			}

		} while (!this->correctPassword(email, pass));

		// If both email and password are correct, welcome the user
		if (pass != "-1") {
			auto user = searchUserByEmail(email);
			cout << "Welcome back, " << user->getName() << ".\n";
		}
	}
}
