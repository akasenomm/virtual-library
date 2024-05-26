#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include "include/Book.h"
#include "include/Application.h"
#include "include/sqlite3.h"

bool operator==(const Book& a, const Book& b) {
    return a.getName() == b.getName() && a.getAuthor() == b.getAuthor() && a.getPagesCount() == b.getPagesCount() && a.getGenre() == b.getGenre();
}

struct BookHasher {
    std::size_t operator()(const Book& b) const {
        return std::hash<std::string>()(b.getName()) ^ std::hash<std::string>()(b.getAuthor());
    }
};

void createAndPopulateDatabase(const std::vector<Book>& books) {
    sqlite3* db;
    char* errMsg = nullptr;
    int rc;

    rc = sqlite3_open("librarydb", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sqlCreateBooks = "CREATE TABLE IF NOT EXISTS Books ("
                                 "Name TEXT NOT NULL, "
                                 "Author TEXT NOT NULL, "
                                 "Pages INT NOT NULL, "
                                 "Genre TEXT NOT NULL, "
                                 "Count INT NOT NULL);";

    const char* sqlCreateUsers = "CREATE TABLE IF NOT EXISTS Users ("
                                 "Username TEXT PRIMARY KEY, "
                                 "Password TEXT NOT NULL);";

    rc = sqlite3_exec(db, sqlCreateBooks, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error in creating Books table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sqlCreateUsers, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error in creating Users table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }

    const char* sqlInsertBooks = "INSERT INTO Books (Name, Author, Pages, Genre, Count) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmtBooks;
    rc = sqlite3_prepare_v2(db, sqlInsertBooks, -1, &stmtBooks, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    int count = 0;
    for (const auto& book : books) {
        count++;
        sqlite3_bind_text(stmtBooks, 1, book.getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmtBooks, 2, book.getAuthor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmtBooks, 3, book.getPagesCount());
        sqlite3_bind_text(stmtBooks, 4, book.getGenre().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmtBooks, 5, count);

        rc = sqlite3_step(stmtBooks);
        if (rc != SQLITE_DONE) {
            std::cerr << "SQL error in inserting data: " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        sqlite3_reset(stmtBooks);
    }

    sqlite3_finalize(stmtBooks);
    sqlite3_close(db);
}


std::vector<Book> parseBooks(const std::string& data) {
    std::istringstream ss(data);
    std::string line;
    std::unordered_set<Book, BookHasher> uniqueBooks;

    while (std::getline(ss, line)) {
        std::istringstream lineStream(line);
        std::string name, author, pagesStr, genre;
        std::getline(lineStream, name, ',');
        std::getline(lineStream, author, ',');
        std::getline(lineStream, pagesStr, ',');
        std::getline(lineStream, genre, ',');

        int pages = std::stoi(pagesStr);
        Book book = {name, author, pages, genre};
        uniqueBooks.insert(book);
    }

    return std::vector<Book>(uniqueBooks.begin(), uniqueBooks.end());
}

int main() {
    std::string data = "The Great Gatsby,F. Scott Fitzgerald,180,Fiction\n"
                       "A Brief History of Time,Stephen Hawking,256,Non-fiction\n"
                       "To Kill a Mockingbird,Harper Lee,281,Fiction\n"
                       "1984,George Orwell,328,Dystopian\n"
                       "The Art of War,Sun Tzu,110,History\n"
                       "Pride and Prejudice,Jane Austen,279,Romance\n"
                       "The Catcher in the Rye,J.D. Salinger,277,Fiction\n"
                       "The Hobbit,J.R.R. Tolkien,310,Fantasy\n"
                       "Moby Dick,Herman Melville,635,Adventure\n"
                       "War and Peace,Leo Tolstoy,1225,History\n"
                       "The Odyssey,Homer,500,Epic\n"
                       "Ulysses,James Joyce,730,Modernist\n"
                       "Don Quixote,Miguel de Cervantes,1023,Adventure\n"
                       "The Divine Comedy,Dante Alighieri,798,Epic\n"
                       "Hamlet,William Shakespeare,242,Tragedy\n"
                       "The Great Gatsby,F. Scott Fitzgerald,180,Fiction\n"
                       "A Brief History of Time,Stephen Hawking,256,Non-fiction\n"
                       "To Kill a Mockingbird,Harper Lee,281,Fiction\n"
                       "The Art of War,Sun Tzu,110,History\n"
                       "1984,George Orwell,328,Dystopian\n"
                       "Pride and Prejudice,Jane Austen,279,Romance\n"
                       "The Catcher in the Rye,J.D. Salinger,277,Fiction\n"
                       "The Hobbit,J.R.R. Tolkien,310,Fantasy\n"
                       "Moby Dick,Herman Melville,635,Adventure\n"
                       "War and Peace,Leo Tolstoy,1225,History\n";

    std::vector<Book> books = parseBooks(data);
    createAndPopulateDatabase(books);

    std::cout << "Tere tulemast virtuaalsesse raamatukokku!\n";
    Application application;
    application.run();

    return 0;
}
