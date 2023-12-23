#ifndef DATABASE_H
#define DATABASE_H

#include "person.h"
#include "user.h"
#include "admin.h"
#include "topic.h"
#include "vote.h"
#include <vector>

class Database {
public:
    static vector<Person> users;
    static int userCount;
    static int userID;

    static vector<Vote> votes;
    static int voteCount;
    static int voteID;

    static vector<Topic> topics;
    static int topicCount;
    static int topicID;

    bool isUser(const Person* person); 

};

#endif
