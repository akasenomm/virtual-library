//
// Created by Hanna Maria Fatkin on 13.04.2024.
//
#include "user.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void User::menu(?) const {
    cout << "\nValikud:\n";
    cout << "1. Vaata saadaval olevaid raamatuid\n";
    cout << "2. Laenuta raamat\n";
    cout << "3. Tagasta raamat\n";
    cout << "4. Logi välja\n";

    int choice;
    std::cout << "\nPalun vali tegevus (1-4): ";
    std::cin >> choice;

    std::string title;

    switch (choice) {
        case 1:
           // library.listBooks(); smth along the lines
            break;
        case 2:
            std::cout << "Sisesta raamatu pealkiri, mida soovid laenutada: ";
            std::cin >> title;
            //library.borrowBook smth smth
            break;
        case 3:
            std::cout << "Sisesta raamatu pealkiri, mida soovid tagastada: ";
            std::cin >> title;
            //library.returnBook smth smth
            break;
        case 4:
            std::cout << "Oled välja logitud"
