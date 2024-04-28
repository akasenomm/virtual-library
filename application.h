//
// Created by Hanna Maria Fatkin on 13.04.2024.
//
#ifndef PROJEKT_USER_H
#define PROJEKT_USER_H
using namespace std;
#include "Library.h"
#include "user.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

class Application {
public:
    Application();
    ~Application();

    void createUser();
    void login();
    void menu();
    void saveUsersToFile() const;
    void changePassword();
    void changeUsername();
    void selectGenreAndBorrowBook(Library* lib, string genre);
    void run();

private:
    User* loggedInUser;
    Library library;
    vector<User*>users;
    string newUsername;
    vector<string> borrowedBooks;
    string filename = "users.txt";
};

#endif //PROJEKT_USER_H