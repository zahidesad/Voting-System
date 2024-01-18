#include "../header/user.h"
#include "../header/database.h"

User::User(int id, const string &name, const string &username, const string &password, const string &mail)
    : Person(id, name, username, password, mail)
{
    Database::insertUser(*this);
}

User::User() {}

void printVotedTopic(User user)
{
    for (int i = 0; i < Database::votes.size(); i++)
    {
        if (Database::votes[i].getVoter().getId() == user.getId())
        {
            cout << i + 1 << ") " << Database::votes[i].getTopic().getTopicName() << endl;
        }
    }
}
