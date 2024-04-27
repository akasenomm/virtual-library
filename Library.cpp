// Library.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
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
void Library::getGenre(string genre) {
    vector<Book> genreBooks;
    for (const auto& it : books) {
        if (it.first.getGenre() == genre) {
            genreBooks.push_back(it.first);
        }
    }
    if (genreBooks.empty()) {
        cout << "Selles žanris pole hetkel saadavaid raamatuid" << endl;
    } else {
        cout << "Raamatud žanris '" << genre << "':" << endl;
        for (auto &&Book : genreBooks) {
            cout << Book.getName() << endl;
        }
    }
}

void Library::borrowBook(string name) {
    for (auto & book : books) {
        const string &bookname = book.first.getName();
        if ( bookname == name) {
            if (book.second > 0) {
                book.second--;
                cout << "Raamatu laenutamine õnnestus!" << endl;
            } else {
                cout << "Rohkem koopiad pole." << endl;
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
        ss.ignore(2, ',');  // Ignore the comma and the space after pagesCount
        getline(ss, genre);  // Read the rest of the line into genre
        Book book(name, author, pagesCount, genre);
        addBook(book);
    }
    file.close();
}


