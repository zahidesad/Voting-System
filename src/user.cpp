#include "../header/user.h"

User::User(int id, const string &name, const string &username, const string &password, const string &mail)
    : Person(id, name, username, password, mail) {}

User::User() {}

