#include "../header/database.h"

vector<Person> Database::users;
int Database::userCount = 0;
int Database::userID = 0;

vector<Vote> Database::votes;
int Database::voteCount = 0;
int Database::voteID = 0;

vector<Topic> Database::topics;
int Database::topicCount = 0;
int Database::topicID = 0;

// Functions
bool isUser(const Person *person)
{
    if (dynamic_cast<const User *>(person) != nullptr)
    {
        cout << "This is a User." << endl;
        return true;
    }
    else
    {
        cout << "This is not a User." << endl;
        return false;
    }
}
