#include "../header/user.h"

User::User(int id, const string &name, const string &username, const string &password, const string &mail, const int &isAdmin)
    : Person(id, name, username, password, mail,0) {}

User::User() {}

