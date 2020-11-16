#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

//Change for full path
const std::string PASSWORDS = "pass.txt";

bool authenticate(std::string username, std::string password, std::string file);
bool checkDuplicateUsername(std::string username, std::string file);
int hash(std::string x)
std::string convertToLine(std::string username, std::string passwordHash);
void addUser(std::string username, std::string passwordHash);
void append(std::string file, std::string message);
void newUser();

int main(){
    newUser();
    return 0;
}

bool authenticate(std::string username, std::string password, std::string file){
    std::string comp = convertToLine(username, password);
    std::fstream doc;
    doc.open(file, std::ios::in);
    std::string line;
    while(getline(doc, line)){
        if(line == comp){
            std::cout << "Welcome" << std::endl;
            doc.close();
            return true;
        }
    }
    std::cout << "Username or password incorrect" << std::endl;
    return false;
}

std::string convertToLine(std::string username, std::string password){
    return std::to_string(hash(username)) + " " + std::to_string(hash(password));
}

void addUser(std::string username, std::string password){
    append(PASSWORDS, convertToLine(username, password));
}

bool checkDuplicateUsername(std::string username, std::string file){
    std::string x = std::to_string(hash(username));
    std::fstream doc;
    doc.open(file, std::ios::in);
    std::string line;
    while(getline(doc, line)){
        if(line.substr(0, x.size()) == x){
            doc.close();
            return true;
        }
    }
    return false;
}

int hash(std::string x){
    std::hash<char*> ptr_hash;
    std::hash<std::string> str_hash;
    return(str_hash(x));
    return 0;
}

void append(std::string file, std::string message){
    std::ofstream doc;
    doc.open(file, std::ios_base::app);
    doc << message;
    doc << "\n";
    doc.close();
}

void newUser(){
    std::string username;
    std::string password;
    std::cout << "Enter in a username: "; std::cin >> username;
    std::cout << "Enter in a password: "; std::cin >> password;
    if(checkDuplicateUsername(username, PASSWORDS)){
        std::cout << "That username is taken." << std::endl;
        newUser();
    }else{
        addUser(username, password);
    }
}
