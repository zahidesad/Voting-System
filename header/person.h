#ifndef PERSON_H
#define PERSON_H

using namespace std;
#include <string>
#include <iostream>

class Person
{
private:
    int id;
    string name;
    string username;
    string password;
    string mail;
    int isAdmin;

    friend int checkAdmin(Person *person);
public:
    Person(int id, const string &name, const string &username, const string &password, const string &mail, const int &isAdmin);
    Person();
    virtual ~Person();
    // Getter functions
    int getId() const;
    string getName() const;
    string getUsername() const;
    string getPassword() const;
    string getMail() const;

    // Setter functions
    void setId(int newId);
    void setName(const string &newName);
    void setUsername(const string &newUsername);
    void setPassword(const string &newPassword);
    void setMail(const string &newMail);
};


#endif
