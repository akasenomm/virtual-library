#ifndef USER_H
#define USER_H

#include <string>
#include "sqlite3.h"

class User {
public:
    User(std::string username, std::string password);
    static bool createUser(const std::string& username, const std::string& password);
    static User* loginUser(const std::string& username, const std::string& password);
    static bool updateUserUsername(const std::string& oldUsername, const std::string& newUsername);
    static bool updateUserPassword(const std::string& username, const std::string& newPassword);
    std::string getUsername() const;
    std::string getPassword() const;
    void setUsername(const std::string& newUsername);
    void setPassword(const std::string& newPassword);

private:
    std::string username;
    std::string password;
};

#endif // USER_H
