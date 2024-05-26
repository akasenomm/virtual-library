// Book.cpp
#include "include/Book.h"

Book::Book(string name, string author, int pagesCount, string genre)
        : name(name), author(author), pagesCount(pagesCount), genre(genre) {}

string Book::getName() const {
    return name;
}

string Book::getAuthor() const {
    return author;
}

int Book::getPagesCount() const {
    return pagesCount;
}

string Book::getGenre() const {
    return genre;
}
