//
// Created by Hanna Maria Fatkin on 13.04.2024.
//

#ifndef PROJEKT_USER_H
#define PROJEKT_USER_H
using namespace std;
#include "Library.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

class User {
public:
    User();
    ~User();

    void createUser();
    void login();
    void menu() const;

private:
    Library library;
    map<std::string, std::string> users; //Map kasutajanimede ja passide jaoks
    string username;
    string password;
    vector<std::string> borrowedBooks;
    string filename = "users.txt";
};

User::User() {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(' ');
            if (pos != std::string::npos) {
                std::string username = line.substr(0, pos);
                std::string password = line.substr(pos + 1);
                users[username] = password;
            }
        }
        file.close();
    }
}
User::~User() {
    // Kui objekt hävitatakse, salvesta kasutajanimed ja paroolid faili
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : users) {
            file << entry.first << ' ' << entry.second << '\n';
        }
        file.close();
    }
}
void User::createUser(){
    string username, password;
    cout << "Palun sisesta kasutajanimi: ";
    cin >> username;

    // Kontrollime, kas kasutajanimi on juba kasutusel
    if (users.find(username) != users.end()) {
        std::cout << "Kasutajanimi '" << username << "' on juba kasutusel. Palun vali uus kasutajanimi.\n";
        return;
        }

    cout << "Palun sisesta parool: ";
    cin >> password;
    users[username] = password;
    cout << "Kasutaja '" << username << "' on loodud.\n";
}

void User::login() {
    string username, password;
    cout << "Sisesta kasutajanimi: ";
    cin >> username;
    cout << "Sisesta parool: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        std::cout << "Edukas sisselogimine kasutajale " << username << ".\n";
        menu();
    } else {
        std::cout << "Kasutajanimi või parool on vale. Palun proovi uuesti.\n";
    }
}
void User::menu() const {
    std::cout << "\nValikud:\n";
    std::cout << "1. Vaata saadaval olevaid raamatuid\n";
    std::cout << "2. Laenuta raamat\n";
    std::cout << "3. Tagasta raamat\n";
    std::cout << "4. Logi välja\n";

    int choice;
    std::cout << "\nPalun vali tegevus (1-4): ";
    std::cin >> choice;

    std::string title;

    auto* lib = new Library;
    lib->addBooksFromFile("test.txt");
    switch (choice) {
        case 1:
            std::cout << "\nPalun vali Žanr (1-4): ";
            std::cout << "\nValikud:\n";
            std::cout << "1. Vaata kõiki raamatuid\n";
            std::cout << "2. History\n";
            std::cout << "3. Fiction\n";
            std::cout << "4. Nonfiction\n";
            int choice2;
            std::cin >> choice2;
            switch (choice2) {
                case 1:
                    lib->showAllBooks();
                    break;
                case 2: {
                    string genre = "history";
                    lib->getGenre(genre);
                    break;
                }
                case 3:
                    string genre2 = "fiction";
                    lib->getGenre(genre2);
                    break;
            }
            break;
        case 2:
            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            lib->borrowBook(title);
            break;
        case 3:
            std::cout << "Sisesta raamatu pealkiri, mida soovid tagastada: ";
            std::cin >> title;
            lib->removeBook(title);
            break;
        case 4:
            std::cout << "Oled välja logitud\n";
            break;
        default:
            std::cout << "Vigane valik. Palun proovi uuesti.\n";
            break;
    }
}

#endif //PROJEKT_USER_H
