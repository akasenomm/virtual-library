//
// Created by Hanna Maria Fatkin on 13.04.2024.
//

#ifndef PROJEKT_USER_H
#define PROJEKT_USER_H
using namespace std;
#include "string"
#include <iostream>
#include <vector>
#include <string>

class User {
public:
    User(const string& username, const string& password);

private:
    vector<User> users;
    string username;
    string password;
};

void User::createUser(){
string username, password;
cout << "Palun sisesta kasutajanimi: ";
cin >> username;

// Kontrollime, kas kasutajanimi on juba kasutusel
for (const auto& user : users) {
if (user.getUsername() == username) {
cout << "Kasutajanimi '" << username << "' on juba kasutusel. Palun vali uus kasutajanimi.\n";
return;
}
}

cout << "Palun sisesta parool: ";
cin >> password;

users.push_back({username, password});
cout << "Kasutaja '" << username << "' on loodud.\n";
}

void User::currentUserLogin() {
    std::string username, password;
    std::cout << "Sisesta kasutajanimi: ";
    std::cin >> username;
    std::cout << "Sisesta parool: ";
    std::cin >> password;

    for (auto &user: users) {
        if (user.checkCredentials(username, password)) {
            std::cout << "Edukas sisselogimine kasutajale " << username << ".\n";
            currentUser = &user; // Määrab praeguse kasutaja
            return;
        }
    }

    std::cout << "Kasutajanimi või parool on vale. Palun proovi uuesti.\n";
}

#endif //PROJEKT_USER_H
