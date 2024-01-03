#include "../header/admin.h"
#include "../header/database.h"

Admin::Admin(int id, const string &name, const string &username, const string &password, const string &mail)
    : Person(id, name, username, password, mail)
{
    Database::insertAdmin(*this);
}

Admin::Admin() {}
