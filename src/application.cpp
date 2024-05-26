#include "include/Application.h"
#include <iostream>
#include <vector>
#include "include/Library.h"

//
// Created by arturkas on 28/04/2024.
//

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
                exit(EXIT_SUCCESS); // Terminate the program
            default:
                cout << "Vigane valik. Palun vali uuesti.\n";
                break;
        }
    }
}

void Application::createUser(){
    string username, password;
    cout << "Palun sisesta kasutajanimi: ";
    cin >> username;

    cout << "Palun sisesta parool: ";
    cin >> password;

    User newUser(username, password);
    if (newUser.createUser(username, password)) {
        cout << "Kasutaja '" << username << "' on loodud.\n";
    } else {
        cout << "Kasutajanimi '" << username << "' on juba kasutusel. Palun vali uus kasutajanimi\n";
    }
}

void Application::login() {
    string username, password;
    cout << "Sisesta kasutajanimi: ";
    cin >> username;
    cout << "Sisesta parool: ";
    cin >> password;

    loggedInUser = User::loginUser(username, password);

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
        loggedInUser->setPassword(newPassword);
        User::updateUserPassword(loggedInUser->getUsername(), newPassword);
        cout << "Parool on edukalt muudetud.\n";
    } else {
        cout << "Logi esmalt sisse.\n";
    }
}

void Application::changeUsername() {
    string newUsername;
    cout << "Sisesta uus kasutajanimi: ";
    cin >> newUsername;
    if (loggedInUser != nullptr) {
        string oldUsername = loggedInUser->getUsername();
        loggedInUser->setUsername(newUsername);
        if (User::updateUserUsername(oldUsername, newUsername)) {
            cout << "Kasutajanimi on edukalt muudetud.\n";
        } else {
            cout << "Kasutajanime muutmine ebaõnnestus. Uus kasutajanimi võib olla juba kasutusel.\n";
        }
    } else {
        cout << "Logi esmalt sisse.\n";
    }
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
        lib->borrowBook(title, loggedInUser);
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
    lib->addBooksFromDatabase("librarydb");

    do {
        cout << "\nValikud:\n";
        for (int i = 0; i < menuChoices.size(); i++) {
            cout << i + 1 << ". " << menuChoices[i] << "\n";
        }

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nPalun vali Žanr (1-" << genreChoices.size() << "): ";
                cout << "\nValikud:\n";
                for (int i = 0; i < genreChoices.size(); i++) {
                    cout << i + 1 << ". " << genreChoices[i] << "\n";
                }
                int genreChoice;
                cin >> genreChoice;
                if (genreChoice >= 1 && genreChoice <= genreChoices.size()) {
                    if (genreChoice == 1) {
                        lib->showAllBooks();
                    } else {
                        selectGenreAndBorrowBook(lib, genreChoices[genreChoice - 1]);
                    }
                } else {
                    cout << "Vigane valik. Palun proovi uuesti.\n";
                }
                break;
            case 2:
                cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
                cin.ignore();
                getline(cin, title);
                lib->borrowBook(title, loggedInUser);
                break;
            case 3:
                cout << "Sisesta raamatu pealkiri, mida soovid tagastada: ";
                cin.ignore();
                getline(cin, title);
                lib->returnBook(title);
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