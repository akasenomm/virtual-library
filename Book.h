// Book.h
#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
public:
    Book(string name, string author, int pagesCount, string genre);
    ~Book();

    string getName() const;
    string getAuthor();
    int getPagesCount();
    string getGenre() const;

    bool operator<(const Book &other) const {
        return name < other.getName();  // Compare books based on their names
    };

private:
    string name;
    string author;
    int pagesCount;
    string genre;
};

#endif // BOOK_H
