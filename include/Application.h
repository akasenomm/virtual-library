//
// Created by Hanna Maria Fatkin on 13.04.2024.
//
#ifndef PROJEKT_USER_H
#define PROJEKT_USER_H
#include "Library.h"
#include "User.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

class Application {
public:
    void createUser();
    void login();
    void menu();
    void changePassword();
    void changeUsername();
    void selectGenreAndBorrowBook(Library* lib, string genre);
    void run();

private:
    User* loggedInUser = nullptr;
    Library library;
    vector<User*>users;
    string newUsername;
    vector<string> borrowedBooks;
    string filename = "users.txt";
};

#endif //PROJEKT_USER_H