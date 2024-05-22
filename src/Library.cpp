// Library.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "include/Library.h"
#include "include/sqlite3.h"

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
                borrowedBooks.push_back(book.first);
                cout << "Raamatu laenutamine õnnestus!" << endl;
            } else {
                cout << "Rohkem koopiad pole." << endl;
            }
            break;
        }
    }
}
void Library::showBorrowedBooks() const {
    cout << "Laenutatud raamatud:" << endl;
    for (const auto & book : borrowedBooks) {
        cout << "Pealkiri: " << book.getName() << ", Autor: " << book.getAuthor() << endl;
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

void Library::addBooksFromDatabase(const std::string& databaseName) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    // Open the database
    rc = sqlite3_open(databaseName.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Create SQL query to select all books
    const char* sql = "SELECT Name, Author, Pages, Genre FROM Books;";

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Execute the SQL query and process the results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int pagesCount = sqlite3_column_int(stmt, 2);
        std::string genre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        // Create a book object and add it to the library
        Book book(name, author, pagesCount, genre);
        addBook(book);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

