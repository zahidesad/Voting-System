#ifndef USER_H
#define USER_H

#include "person.h"

class User : public Person
{
public:
    User(int id, const string &name, const string &username, const string &password, const string &mail);
    User();
    virtual ~User() override {}
    friend void printVotedTopic(User user);
};

#endif
