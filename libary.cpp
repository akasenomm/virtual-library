//
// Created by Hanna Maria Fatkin on 13.04.2024.
//
#include "libary.h"
#include <string>
#include <vector>
void Library::borrowBook(User& user, const std::string& title){
        book->setBorrowed(true);
        cout << "Raamat '" << title << "' on laenutatud kasutajale '" << user.getUsername() << "'.\n";
};
void Library::returnBook(User& user, const std::string& title){
        book->setBorrowed(false);
        cout << "Raamat '" << title << "' on tagastatud.\n";
};