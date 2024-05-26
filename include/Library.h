#ifndef LIBRARY_H
#define LIBRARY_H

#include <map>
#include <vector>
#include <string>
#include "Book.h"
#include "User.h"

class Library {
public:
    void addBook(Book book);
    bool isBookInLibrary(std::string name);
    void getGenre(std::string genre);
    void borrowBook(std::string name, User* user);
    void showBorrowedBooks() const;
    void returnBook(std::string name);
    void showAllBooks() const;
    void addBooksFromDatabase(const std::string& databaseName);

private:
    std::map<Book, int> books;
    std::vector<std::pair<Book, User*>> borrowedBooks; // Updated
};

#endif // LIBRARY_H
