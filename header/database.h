#ifndef DATABASE_H
#define DATABASE_H

#include "person.h"
#include "user.h"
#include "admin.h"
#include "topic.h"
#include "vote.h"
#include "../Colors/color.h"
#include <vector>

class Database
{
public:
    static vector<Person *> users;
    static int userCount;
    static int userID;

    static vector<Vote> votes;
    static int voteID;

    static vector<Topic> topics;
    static int topicID;

    static vector<string> categoryNames;
    static  vector<vector<string>> topicsForCategoryNames;
    static string** categoryWithTopicName;
    static Person *login(const string &username, const string &password);
    // Function about person
    static void insertPerson(Person person);
    static int readPerson();
    static int deletePerson(const int id);
    static int updatePersonInformation(const int id, const string &newName, const string &newUsername, const string &newPassword, const string &newMail);
    // Function about topic
    static void showAllTopics();
    static void deleteTopic(int topicId);
    static void updateTopicInformation(int topicId, const string &topicName, const vector<string> &topicOptions, Topic::Categories category, bool isOpen);
    static void changeOpenStatus(int topicID);
    // Function about vote
    static void voteOperation(Person *account);
    static void deleteVote(int voteID);
    static void calculateVoteRate(int Id);

    static void setAllIdNumbers();
    static void printTopicsWithCategories();
    static void initializeCategoryWithTopicName();
};

#endif
