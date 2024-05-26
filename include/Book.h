// Book.h
#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
public:
    Book(string name, string author, int pagesCount, string genre);

    string getName() const;
    string getAuthor() const;
    int getPagesCount() const;
    string getGenre() const;

    bool operator<(const Book &other) const {
        return name < other.getName();
    };

private:
    string name;
    string author;
    int pagesCount;
    string genre;
};

#endif // BOOK_H
