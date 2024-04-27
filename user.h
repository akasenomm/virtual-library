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
    void menu();
    void saveUsersToFile() const;
    void changePassword();
    void changeUsername();

private:
    Library library;
    map<std::string, std::string> users;
    string username;
    string newUsername;
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
void User::saveUsersToFile() const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : users) {
            file << entry.first << ' ' << entry.second << '\n';
        }
        file.close();
    }
}
User::~User() {
    saveUsersToFile();
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

void User::changePassword() {
    std::string newPassword;
    std::cout << "Sisesta uus parool: ";
    std::cin >> newPassword;
    password = newPassword;
    std::cout << "Parool on edukalt muudetud.\n";
    saveUsersToFile();
}

void User::changeUsername() {
    std::string newUsername;
    std::cout << "Sisesta uus kasutajanimi: ";
    std::cin >> newUsername;
    auto it = users.find(username);
    if (it != users.end()) {
        users.erase(it);
        username = newUsername;
        users[newUsername] = password;
        std::cout << "Kasutajanimi on edukalt muudetud.\n";
        saveUsersToFile();
    } else {
        std::cout << "Kasutajanime muutmine ebaõnnestus. Kasutajanimi '" << username << "' ei eksisteeri.\n";
    }
}

void User::menu() {
    int choice;
    std::string title;
    auto *lib = new Library;
    lib->addBooksFromFile("test.txt");

    do {
        std::cout << "\nValikud:\n";
        std::cout << "1. Vaata saadaval olevaid raamatuid\n";
        std::cout << "2. Laenuta raamat\n";
        std::cout << "3. Tagasta raamat\n";
        std::cout << "4. Vaata laenutatud raamatuid\n";
        std::cout << "5. Muuda kasutajanime\n";
        std::cout << "6. Muuda kasutaja salasõna\n";
        std::cout << "7. Logi välja\n";

        std::cout << "\nPalun vali tegevus (1-7): ";
        std::cin >> choice;


        switch (choice) {
            case 1:
                std::cout << "\nPalun vali Žanr (1-11): ";
                std::cout << "\nValikud:\n";
                std::cout << "1. Vaata kõiki raamatuid\n";
                std::cout << "2. History\n";
                std::cout << "3. Fiction\n";
                std::cout << "4. Dystopian\n";
                std::cout << "5. Non-fiction\n";
                std::cout << "6.  Romance\n";
                std::cout << "7.  Fantasy\n";
                std::cout << "8.  Adventure\n";
                std::cout << "9.  Epic\n";
                std::cout << "10.  Modernist\n";
                std::cout << "11.  Tragedy\n";
                int choice2;
                std::cin >> choice2;
                switch (choice2) {
                    case 1:
                        lib->showAllBooks();
                        break;
                    case 2: {
                        string genre = "History";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            //tglt võiks ka kontrollida kas sisestati korrektne nimi!
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 3: {
                        string genre = "Fiction";
                        lib->getGenre(genre);
                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 4: {
                        string genre = "Dystopian";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 5: {
                        string genre = "Non-fiction";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 6: {
                        string genre = "Romance";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 7: {
                        string genre = "Fantasy";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 8: {
                        string genre = "Adventure";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 9: {
                        string genre = "Epic";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 10: {
                        string genre = "Modernist";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }
                    case 11: {
                        string genre = "Tragedy";
                        lib->getGenre(genre);

                        std::cout << "Kas soovid midagi laenutada? (jah/ei): ";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "jah") {
                            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            lib->borrowBook(title);
                        } else {
                            std::cout << "Vali järgmine tegevus.\n";
                        }
                        break;
                    }

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
                lib->showBorrowedBooks();
                break;
            case 5:
                changeUsername();
                break;
            case 6:
                changePassword();
                break;
            case 7:
                std::cout << "Oled välja logitud\n";
                break;
            default:
                std::cout << "Vigane valik. Palun proovi uuesti.\n";
                break;
        }
    } while (choice != 7);

}
#endif //PROJEKT_USER_H