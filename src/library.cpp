#include "include/Library.h"
#include <iostream>
#include <algorithm>
#include "include/sqlite3.h"

void Library::addBook(Book book) {
    if (isBookInLibrary(book.getName())) {
        books[book]++;
    } else {
        books[book] = 1;
    }
}

bool Library::isBookInLibrary(std::string name) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->first.getName() == name) {
            return true;
        }
    }
    return false;
}


void Library::getGenre(std::string genre) {
    std::vector<Book> genreBooks;
    for (const auto& it : books) {
        if (it.first.getGenre() == genre) {
            genreBooks.push_back(it.first);
        }
    }
    if (genreBooks.empty()) {
        std::cout << "Selles žanris pole hetkel saadavaid raamatuid" << std::endl;
    } else {
        std::cout << "Raamatud žanris '" << genre << "':" << std::endl;
        for (auto &&Book : genreBooks) {
            std::cout << Book.getName() << std::endl;
        }
    }
}

void Library::borrowBook(std::string name, User* user) {
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    for (auto & book : books) {
        std::string bookname = book.first.getName();

        std::transform(bookname.begin(), bookname.end(), bookname.begin(), ::tolower);

        if (bookname == name) {
            if (book.second > 0) {
                book.second--;
                borrowedBooks.push_back(std::make_pair(book.first, user)); // Updated
                std::cout << "Raamatu laenutamine õnnestus!" << std::endl;
            } else {
                std::cout << "Rohkem koopiad pole." << std::endl;
            }
            return;
        }
    }
    std::cout << "Raamatut ei leitud." << std::endl;
}

void Library::showBorrowedBooks() const {
    std::cout << "Laenutatud raamatud:" << std::endl;
    for (const auto & borrowed : borrowedBooks) {
        std::cout << "Pealkiri: " << borrowed.first.getName()
                  << ", Autor: " << borrowed.first.getAuthor()
                  << ", Laenutaja: " << borrowed.second->getUsername() << std::endl; // Updated
    }
}

void Library::returnBook(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto it = std::find_if(borrowedBooks.begin(), borrowedBooks.end(), [&name](const std::pair<Book, User*>& borrowed) {
        std::string bookName = borrowed.first.getName();
        std::transform(bookName.begin(), bookName.end(), bookName.begin(), ::tolower);
        return bookName == name;
    });

    if (it != borrowedBooks.end()) {
        for (auto & book : books) {
            std::string bookName = book.first.getName();
            std::transform(bookName.begin(), bookName.end(), bookName.begin(), ::tolower);

            if (bookName == name) {
                book.second++;
                borrowedBooks.erase(it);
                std::cout << "Raamat tagastatud." << std::endl;
                return;
            }
        }
    } else {
        std::cout << "Raamatut ei leitud laenutatud raamatute hulgast." << std::endl;
    }
}

void Library::showAllBooks() const {
    for (const auto & book : books) {
        Book &x = const_cast<Book &>(book.first);
        std::cout << "Title: " << book.first.getName() << ", Count: " << book.second << std::endl;
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

    const char* sql = "SELECT Name, Author, Pages, Genre FROM Books;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int pagesCount = sqlite3_column_int(stmt, 2);
        std::string genre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        Book book(name, author, pagesCount, genre);
        addBook(book);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
