#include "../header/admin.h"

Admin::Admin(int id, const string &name, const string &username, const string &password, const string &mail, const int &isAdmin)
    : Person(id, name, username, password, mail, 1)
{
}

Admin::Admin() {}
