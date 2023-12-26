#include "../header/person.h"
#include "../header/database.h"
#include <iostream>

using namespace std;

// Constructor
Person::Person(int id, const string &name, const string &username, const string &password, const string &mail, const int &isAdmin)
    : id(id), name(name), username(username), password(password), mail(mail), isAdmin(isAdmin)
{
    Database::users.push_back(this);
    Database::insertPerson(*this);
}
Person::Person()
{
}

Person::~Person()
{
}
int checkAdmin(Person *person) // friend function
{
    if (person->isAdmin == 1 || person->getId() == 0)
    {
        person->isAdmin = 1;
        return 1;
    }
    person->isAdmin = 0;
    return 0;
}
// Getter functions
int Person::getId() const
{
    return id;
}

string Person::getName() const
{
    return name;
}

string Person::getUsername() const
{
    return username;
}

string Person::getPassword() const
{
    return password;
}

std::string Person::getMail() const
{
    return mail;
}

// Setter fonksiyonları
void Person::setId(int newId)
{
    id = newId;
}

void Person::setName(const string &newName)
{
    name = newName;
}

void Person::setUsername(const string &newUsername)
{
    username = newUsername;
}

void Person::setPassword(const string &newPassword)
{
    password = newPassword;
}

void Person::setMail(const string &newMail)
{
    mail = newMail;
}
