// Library.h
#ifndef LIBRARY_H
#define LIBRARY_H

#include <unordered_map>
#include <map>
#include "Book.h"

using namespace std;

class Library {
public:
    Library();
    ~Library();

    void addBook(Book book);
    void removeBook(string name);
    bool isBookInLibrary(string name);
    void printBookInfo(string name);
    void borrowBook(string name);
    void returnBook(string name);
    void showAllBooks() const;
    void addBooksFromFile(string filename);
    void getGenre(string name);
    void showBorrowedBooks() const;
private:
    map<Book, int> books;
    vector<Book> borrowedBooks;
};

#endif // LIBRARY_H

