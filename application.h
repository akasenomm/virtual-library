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
void Application::run() {
    while (true) {
        cout << "\nValikud:\n";
        cout << "1. Logi sisse\n";
        cout << "2. Loo uus kasutaja\n";
        cout << "3. Välju\n";

        int choice;

        cout << "\nPalun vali tegevus (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                createUser();
                break;
            case 3:
                cout << "Täname kasutamast virtuaalset raamatukogu. Head aega!\n";
                break;
            default:
                cout << "Vigane valik. Palun vali uuesti.\n";
                break;
        }
    }
}

Application::Application() {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                string username = line.substr(0, pos);
                string password = line.substr(pos + 1);
                users.push_back(new User(username, password));
            }
        }
        file.close();
    }
}

void Application::saveUsersToFile() const {
    ofstream file(filename);
    if (file.is_open()) {
        for ( User* user : users) {
            file << user->getUsername() << ' ' << user->getPassword() << '\n';
        }
    }
}

Application::~Application() {
    saveUsersToFile();
}

void Application::createUser(){
    string username, password;
    cout << "Palun sisesta kasutajanimi: ";
    cin >> username;

    // Kontrollime, kas kasutajanimi on juba kasutusel
    for (auto &&user : users) {
        if (user->getUsername() == username) {
            cout << "Kasutajanimi '" << username << "' on juba kasutusel. Palun vali uus kasutajanimi.\n";
            return;
        }
    }

    cout << "Palun sisesta parool: ";
    cin >> password;
    users.push_back(new User(username, password));
    cout << "Kasutaja '" << username << "' on loodud.\n";
    saveUsersToFile();
}

void Application::login() {
    string username, password;
    cout << "Sisesta kasutajanimi: ";
    cin >> username;
    cout << "Sisesta parool: ";
    cin >> password;

    for (User* user : users) {
        if (user->getUsername() == username && user->getPassword() == password) {
            loggedInUser = user;
            break;
        }
    }

    if (loggedInUser != nullptr) {
        cout << "Edukas sisselogimine kasutajale " << username << ".\n";
        menu();
    } else {
        cout << "Kasutajanimi või parool on vale. Palun proovi uuesti.\n";
    }
}

void Application::changePassword() {
    string newPassword;
    cout << "Sisesta uus parool: ";
    cin >> newPassword;
    if (loggedInUser != nullptr) {
        loggedInUser->setPassword( newPassword);
    } else {
        cout << "Login first" << "\n";
    }
    saveUsersToFile();
}

void Application::changeUsername() {
    string newUsername;
    cout << "Sisesta uus kasutajanimi: ";
    cin >> newUsername;
    if (loggedInUser != nullptr) {
        loggedInUser->setUsername(newUsername);
        cout << "Nimi muudetud" << "\n";
    } else {
        cout << "Log in first" << "\n";
    }
    saveUsersToFile();
}

void Application::selectGenreAndBorrowBook(Library* lib, string genre) {
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

void Application::menu() {
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

    vector<string> genreChoices = {
            "Vaata kõiki raamatuid",
            "History",
            "Fiction",
            "Dystopian",
            "Non-fiction",
            "Romance",
            "Fantasy",
            "Adventure",
            "Epic",
            "Modernist",
            "Tragedy"
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
                cout << "\nPalun vali Žanr (1-" << genreChoices.size() << "): ";
                cout << "\nValikud:\n";
                for (int i = 0; i < genreChoices.size(); i++) {
                    cout << i+1 << ". " << genreChoices[i] << "\n";
                }
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