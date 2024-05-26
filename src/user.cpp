#include "include/User.h"
#include <iostream>

User::User(std::string username, std::string password)
        : username(username), password(password) {}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

void User::setUsername(const std::string& newUsername) {
    username = newUsername;
}

void User::setPassword(const std::string& newPassword) {
    password = newPassword;
}

bool User::createUser(const std::string& username, const std::string& password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("librarydb", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    const char* sqlInsertUser = "INSERT INTO Users (Username, Password) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, sqlInsertUser, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error in inserting data: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}

User* User::loginUser(const std::string& username, const std::string& password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("librarydb", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    const char* sqlSelectUser = "SELECT Password FROM Users WHERE Username = ?;";
    rc = sqlite3_prepare_v2(db, sqlSelectUser, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::string dbPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (dbPassword == password) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return new User(username, password);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return nullptr;
}

bool User::updateUserUsername(const std::string& oldUsername, const std::string& newUsername) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("librarydb", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    const char* sqlUpdateUsername = "UPDATE Users SET Username = ? WHERE Username = ?;";
    rc = sqlite3_prepare_v2(db, sqlUpdateUsername, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, newUsername.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, oldUsername.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error in updating data: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}

bool User::updateUserPassword(const std::string& username, const std::string& newPassword) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("librarydb", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    const char* sqlUpdatePassword = "UPDATE Users SET Password = ? WHERE Username = ?;";
    rc = sqlite3_prepare_v2(db, sqlUpdatePassword, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error in updating data: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}
