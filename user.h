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
    void selectGenreAndBorrowBook(Library* lib, string genre);

private:
    Library library;
    map<string, string> users;
    string username;
    string newUsername;
    string password;
    vector<string> borrowedBooks;
    string filename = "users.txt";
};

User::User() {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                string username = line.substr(0, pos);
                string password = line.substr(pos + 1);
                users[username] = password;
            }
        }
        file.close();
    }
}

void User::saveUsersToFile() const {
    ofstream file(filename);
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
        cout << "Kasutajanimi '" << username << "' on juba kasutusel. Palun vali uus kasutajanimi.\n";
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
        cout << "Edukas sisselogimine kasutajale " << username << ".\n";
        menu();
    } else {
        cout << "Kasutajanimi või parool on vale. Palun proovi uuesti.\n";
    }
}

void User::changePassword() {
    string newPassword;
    cout << "Sisesta uus parool: ";
    cin >> newPassword;
    password = newPassword;
    cout << "Parool on edukalt muudetud.\n";
    saveUsersToFile();
}

void User::changeUsername() {
    string newUsername;
    cout << "Sisesta uus kasutajanimi: ";
    cin >> newUsername;
    auto it = users.find(username);
    if (it != users.end()) {
        users.erase(it);
        username = newUsername;
        users[newUsername] = password;
        cout << "Kasutajanimi on edukalt muudetud.\n";
        saveUsersToFile();
    } else {
        cout << "Kasutajanime muutmine ebaõnnestus. Kasutajanimi '" << username << "' ei eksisteeri.\n";
    }
}

void User::selectGenreAndBorrowBook(Library* lib, string genre) {
    lib->getGenre(genre);
    cout << "Kas soovid midagi laenutada? (jah/ei): ";
    string answer;
    cin >> answer;
    if (answer == "jah") {
        string title;
        cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
        cin.ignore();
        getline(cin, title);
        lib->borrowBook(title);
    } else {
        cout << "Vali järgmine tegevus.\n";
    }
}

void User::menu() {
    int choice;
    vector<string> menuChoices = {
            "Vaata saadaval olevaid raamatuid",
            "Laenuta raamat",
            "Tagasta raamat",
            "Vaata laenutatud raamatuid",
            "Muuda kasutajanime",
            "Muuda kasutaja salasõna",
            "Logi välja"
    };

    string title;
    auto *lib = new Library;
    lib->addBooksFromFile("test.txt");

    do {
        cout << "\nValikud:\n";
        for (int i = 0; i < menuChoices.size(); i++) {
            cout << i+1 << ". " << menuChoices[i] << "\n";
        }

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nPalun vali Žanr (1-11): ";
                cout << "\nValikud:\n";
                cout << "1. Vaata kõiki raamatuid\n";
                cout << "2. History\n";
                cout << "3. Fiction\n";
                cout << "4. Dystopian\n";
                cout << "5. Non-fiction\n";
                cout << "6.  Romance\n";
                cout << "7.  Fantasy\n";
                cout << "8.  Adventure\n";
                cout << "9.  Epic\n";
                cout << "10.  Modernist\n";
                cout << "11.  Tragedy\n";
                int choice2;
                cin >> choice2;
                switch (choice2) {
                    case 1:
                        lib->showAllBooks();
                        break;
                    case 2:
                        selectGenreAndBorrowBook(lib, "History");
                        break;
                    case 3:
                        selectGenreAndBorrowBook(lib, "Fiction");
                        break;
                    case 4:
                        selectGenreAndBorrowBook(lib, "Dystopian");
                        break;
                    case 5:
                        selectGenreAndBorrowBook(lib, "Non-fiction");
                        break;
                    case 6:
                        selectGenreAndBorrowBook(lib, "Romance");
                        break;
                    case 7:
                        selectGenreAndBorrowBook(lib, "Fantasy");
                        break;
                    case 8:
                        selectGenreAndBorrowBook(lib, "Adventure");
                        break;
                    case 9:
                        selectGenreAndBorrowBook(lib, "Epic");
                        break;
                    case 10:
                        selectGenreAndBorrowBook(lib, "Modernist");
                        break;
                    case 11:
                        selectGenreAndBorrowBook(lib, "Tragedy");
                        break;
                }
                break;
            case 2:
                cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                cin.ignore();
                getline(cin, title);
                lib->borrowBook(title);
                break;
            case 3:
                cout << "Sisesta raamatu pealkiri, mida soovid tagastada: ";
                cin >> title;
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
                cout << "Oled välja logitud\n";
                break;
            default:
                cout << "Vigane valik. Palun proovi uuesti.\n";
                break;
        }
    } while (choice != 7);
}
#endif //PROJEKT_USER_H