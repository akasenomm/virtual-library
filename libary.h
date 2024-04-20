//
// Created by Hanna Maria Fatkin on 13.04.2024.
//

#ifndef PROJEKT_LIBARY_H
#define PROJEKT_LIBARY_H
#include <string>
#include <vector>
#include "book.h"
#include "user.h"
using namespace std;
class Library {
public:
    // Muud meetodid...

    void borrowBook(User& user, const string& title);
    void returnBook(User& user, const string& title);

private:
    std::vector<Book> books;
};

#endif // LIBRARY_H

#endif //PROJEKT_LIBARY_H
