#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"

class Admin : public Person {
public:
    Admin(int id, const string& name, const string& username, const string& password, const string& mail);
    Admin();
   
};

#endif
