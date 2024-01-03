#include "../header/user.h"
#include "../header/database.h"

User::User(int id, const string &name, const string &username, const string &password, const string &mail)
    : Person(id, name, username, password, mail)
{
    Database::insertUser(*this);
}

User::User() {}
