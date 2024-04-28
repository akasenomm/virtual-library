//
// Created by arturkas on 28/04/2024.
//

#ifndef VIRTUAL_LIBRARY_USER_H
#define VIRTUAL_LIBRARY_USER_H

#include "string"
using namespace std;

class User {
private:
    string username;
    string password;
public:

    User(string, string);

    string getUsername() {
        return username;
    }
    string getPassword() {
        return password;
    }

    void setUsername(string newUsername) {
        this->username = newUsername;
    }

    void setPassword(string newPassword) {
        this->password = newPassword;
    }
};

#endif //VIRTUAL_LIBRARY_USER_H
