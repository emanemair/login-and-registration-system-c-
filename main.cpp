#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include"user.h"
#include"userManager.h"
using namespace std; 


/* 
// Link against bcrypt.lib
#pragma comment(lib, "bcrypt.lib")
std::string hashPassword(const string& password) {
    BCRYPT_ALG_HANDLE algoHandle = nullptr;
    BCRYPT_HASH_HANDLE hashHandle = nullptr;
    DWORD hashLength = 0, resultLength = 0;
    std::string hashedPassword;

    // Open an algorithm handle for SHA-256
    if (BCryptOpenAlgorithmProvider(&algoHandle, BCRYPT_SHA256_ALGORITHM, NULL, 0) != 0) {
        std::cerr << "Error opening algorithm provider!" << std::endl;
        return "";
    }

    // Get the length of the hash
    BCryptGetProperty(algoHandle, BCRYPT_HASH_LENGTH, (PUCHAR)&hashLength, sizeof(hashLength), &resultLength, 0);

    // Create a buffer to hold the hash
    std::vector<BYTE> hashBuffer(hashLength);

    // Create a hash object
    if (BCryptCreateHash(algoHandle, &hashHandle, nullptr, 0, nullptr, 0, 0) != 0) {
        std::cerr << "Error creating hash object!" << std::endl;
        BCryptCloseAlgorithmProvider(algoHandle, 0);
        return "";
    }

    // Hash the password
    if (BCryptHashData(hashHandle, (PUCHAR)password.c_str(), static_cast<ULONG>(password.size()), 0) != 0) {
        std::cerr << "Error hashing data!" << std::endl;
        BCryptDestroyHash(hashHandle);
        BCryptCloseAlgorithmProvider(algoHandle, 0);
        return "";
    }

    // Retrieve the hash
    if (BCryptFinishHash(hashHandle, hashBuffer.data(), hashLength, 0) != 0) {
        std::cerr << "Error finishing hash!" << std::endl;
    }
    else {
        // Convert the hashed password to a hexadecimal string
        std::stringstream ss;
        for (BYTE b : hashBuffer) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
        }
        hashedPassword = ss.str();
    }

    // Clean up
    BCryptDestroyHash(hashHandle);
    BCryptCloseAlgorithmProvider(algoHandle, 0);

    return hashedPassword;
}

*/
template <typename T>
vector<T> users;


int main() {
    UserManager userManager;
    int choice;
 
    cout << "**** Welcome to the registration and login system *******\n";
    cout << "1. login or 2. registration ? \n";
    cin >> choice; 
    switch (choice)
    {
    case 1:
        userManager.userLogin();
        break; 
    case 2:
        userManager.userRegistration();
        break;
    default:
        cout<<"please select"<<endl;
        break;
    }
    return 0; 
    
}
