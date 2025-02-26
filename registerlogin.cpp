/*
3. Simple Login & Registration System
Purpose:
• Practice basic file handling, simple data storage, and string comparisons.

Approach & Steps:

Requirements:
– Allow a user to register (create a username/password) and then log in.
– Save credentials in a plain text file.

Design:
– Create two functions: one for registration and one for login.
– Store data in a simple format (e.g. “username password” on each line).

Implementation:
– Use std::ofstream to append new user data during registration.
– Use std::ifstream to read and verify credentials during login. – Use basic string comparisons to check if input matches stored credentials.

Testing:
– Try registering several users and testing login with correct and incorrect credentials.

Concepts Covered:
• File I/O (reading and writing text files)
• Basic string manipulation and comparison
• User input and control flow
• Simple error handling
*/



#include <iostream>
#include <limits>
#include <string>
#include <fstream>

void mainMenu();
void registerUser();
void loginUser();

class AuthSystem{

    private:
        std::string filename;
        void clearInputStream(){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    public:
        AuthSystem(const std::string &file):filename(file){}
        void mainMenu(){
            std::cout<<"******* Login and Registration System ******\n";
            std::cout<<"1. Register\n";
            std::cout<<"2. Login\n";
            std::cout<<"3. Exit\n";
            std::cout<<"Enter your choice \n";
        }
        void registerUser(){
            clearInputStream();
            std::string username;
            std::string password;
            std::cout<<"Enter username ";
            std::getline(std::cin,username);
            std::ifstream readFile(filename);
            std::string existingUser;
            std::string existingPass;
            bool userExists = false;
            while(readFile>>existingUser>>existingPass){
                if(existingUser == username){
                    userExists = true;
                    break;
                }
                
            }
            readFile.close();
            if(userExists){
                std::cerr<<"Error, User already exists, Try again with different username \n";
                return;
            }
            std::cout<<"Enter Password: ";
            std::getline(std::cin,password);
            std::ofstream writeFile(filename,std::ios::app);
            if(!writeFile){
                std::cerr<<"Error, could not open file \n";
                return;
            }
            writeFile<<username<<" "<<password;
            writeFile.close();
            std::cout<<"Registration Successfull, You are ready to rock\n";
        }
        void loginUser(){
            clearInputStream();
            std::string username;
            std::string password;
            std::cout<<"Enter username : ";
            std::getline(std::cin,username);
            std::cout<<"Enter password: :";
            std::getline(std::cin,password);

            std::ifstream readFile(filename);
            if(!readFile){
                std::cerr<<"Error, No users Registered\n";
            }
            std::string storeuser;
            std::string storepass;
            bool loginSuccess = false;
            while(readFile>>storeuser>>storepass){
                if(storeuser == username && storepass==password){
                    loginSuccess = true;
                    break;
                }
            }
            readFile.close();
            if(loginSuccess){
                std::cout<<"Login Successfull, Being your work\n";
            }
            else{
                std::cout<<"Invalid Username or Password\n";
            }
        }
};

int main(){
    AuthSystem auth("users.txt");
    char choice; 
    while(true){
        auth.mainMenu();
        std::cin>>choice;
        switch(choice){
            case '1':
                auth.registerUser();
                break;
            case '2':
                auth.loginUser();
                break;
            case '3':
                std::cout<<"GOODBYEE\n";
                return 0;
            default:
            std::cout<<"Invalid Response please choose 1,2,3,\n";
            break;

        }
    }
    return 0;
}






























