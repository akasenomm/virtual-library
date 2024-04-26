// Library.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Library.h"

Library::Library() {}
Library::~Library() {}

void Library::addBook(Book book) {
    if (isBookInLibrary(book.getName())) {
        books[book]++;
    } else {
        books[book] = 1;
    }
}

void Library::removeBook(string name) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->first.getName() == name) {
            books.erase(it);
            break;
        }
    }
}

bool Library::isBookInLibrary(string name) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->first.getName() == name) {
            return true;
        }
    }
    return false;
}

void Library::printBookInfo(string name) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->first.getName() == name) {
            Book bookInfo = it->first;
            cout << "Name: " << bookInfo.getName() << endl;
            cout << "Author: " << bookInfo.getAuthor() << endl;
            cout << "Pages Count: " << bookInfo.getPagesCount() << endl;
            cout << "Genre: " << bookInfo.getGenre() << endl;
            cout << "Quantity: " << it->second << endl;
            break;
        }
    }
}

void Library::borrowBook(string name) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->first.getName() == name) {
            if (it->second > 0) {
                it->second--;
                cout << "Book borrowed successfully." << endl;
            } else {
                cout << "No copies left to borrow." << endl;
            }
            break;
        }
    }
}

void Library::returnBook(string name) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->first.getName() == name) {
            it->second++;
            cout << "Book returned successfully." << endl;
            break;
        }
    }
}

void Library::showAllBooks() const {
    for (const auto & book : books) {
        Book &x = const_cast<Book &>(book.first);
        cout << "Title: " << book.first.getName() << ", Count: " << book.second << endl;
    }
}

void Library::addBooksFromFile(string filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, author, genre;
        int pagesCount;
        getline(ss, name, ',');
        getline(ss, author, ',');
        ss >> pagesCount;
        getline(ss, genre, ',');
        Book book(name, author, pagesCount, genre);
        addBook(book);
    }
    file.close();
}

