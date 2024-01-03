#include "../header/database.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>

vector<Person *> Database::users;
int Database::userCount = 0;
int Database::userID = 0;

vector<Vote> Database::votes;
int Database::voteID = 0;

vector<Topic> Database::topics;
int Database::topicID = 0;

bool flagForDeleteAndUpdate = false;

// Functions
template <typename Base, typename Derived>
static bool instanceof (const Derived *ptr)
{
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

Person *Database::login(const string &username, const string &password)
{
    for (int i = 0; i < Database::users.size(); i++)
    {
        if (Database::users[i]->getUsername() == username && Database::users[i]->getPassword() == password)
        {
            return Database::users[i];
        }
    }
    return nullptr;
}

// Function about admin
void Database::insertAdmin(Admin admin)
{
    ofstream file("../txtFiles/admin.txt", ios_base::app);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    file << admin.getId() << '\n'
         << admin.getName() << '\n'
         << admin.getUsername() << '\n'
         << admin.getPassword() << '\n'
         << admin.getMail() << '\n';

    userCount++;

    file.close();
    cout << "Admin has been written to the file successfully." << endl;
}

int Database::readAdmin()
{
    ifstream file("../txtFiles/admin.txt");
    if (!file.is_open())
    {
        cerr << "Error while opening the file!" << endl;
        return 1;
    }

    char chunk[128];
    int lineNum = 0;
    int personCount = 0;
    Admin *admin = nullptr;

    while (file.getline(chunk, sizeof(chunk)))
    {
        int newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 5 == 0)
        {
            admin = new Admin;
            admin->setId(atoi(chunk));
            lineNum++;
        }
        else if (lineNum % 5 == 1)
        {
            admin->setName(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 2)
        {
            admin->setUsername(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 3)
        {
            admin->setPassword(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 4)
        {
            admin->setMail(chunk);
            lineNum++;
            Database::users.push_back(admin);
            personCount++;
        }
    }
    userCount = personCount;
    file.close();
    return 0;
}

// Function about user
void Database::insertUser(User user)
{
    ofstream file("../txtFiles/user.txt", ios_base::app);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    file << user.getId() << '\n'
         << user.getName() << '\n'
         << user.getUsername() << '\n'
         << user.getPassword() << '\n'
         << user.getMail() << '\n';

    userCount++;

    file.close();
    cout << "User has been written to the file successfully." << endl;
}

int Database::readUser()
{
    ifstream file("../txtFiles/user.txt");
    if (!file.is_open())
    {
        cerr << "Error while opening the file!" << endl;
        return 1;
    }

    char chunk[128];
    int lineNum = 0;
    int personCount = 0;
    User *user = nullptr;

    while (file.getline(chunk, sizeof(chunk)))
    {
        int newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 5 == 0)
        {
            user = new User;
            user->setId(atoi(chunk));
            lineNum++;
        }
        else if (lineNum % 5 == 1)
        {
            user->setName(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 2)
        {
            user->setUsername(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 3)
        {
            user->setPassword(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 4)
        {
            user->setMail(chunk);
            lineNum++;
            Database::users.push_back(user);
            personCount++;
        }
    }
    userCount = personCount;
    file.close();
    return 0;
}

int Database::deleteUser(int id)
{
    if (id <= 0 || id >= userID)
    {
        cout << "Please enter a valid number!";
        return 0;
    }

    ifstream file("../txtFiles/user.txt");
    ofstream temp("../txtFiles/temp.txt");

    if (!file.is_open() || !temp.is_open())
    {
        cout << "Error while opening the file!";
        return 1;
    }

    User *user = nullptr;
    vector<Person *> tempUsers;
    tempUsers.push_back(Database::users[0]);
    char chunk[128];
    int lineNum = 0;
    bool skipPerson = false;

    while (file.getline(chunk, sizeof(chunk)))
    {
        if (lineNum % 5 == 0)
        {
            user = new User;
            user->setId(atoi(chunk));
            if (user->getId() == id)
            {
                skipPerson = true;
                for (auto it = votes.begin(); it != votes.end();)
                {
                    if (it->getVoter().getId() == id)
                    {
                        it = votes.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
            else
            {
                temp << user->getId() << "\n";
            }
            lineNum++;
        }
        else if (lineNum % 5 == 1)
        {
            user->setName(chunk);
            if (!skipPerson)
            {
                temp << user->getName() << "\n";
            }
            lineNum++;
        }
        else if (lineNum % 5 == 2)
        {
            user->setUsername(chunk);
            if (!skipPerson)
            {
                temp << user->getUsername() << "\n";
            }
            lineNum++;
        }
        else if (lineNum % 5 == 3)
        {
            user->setPassword(chunk);
            if (!skipPerson)
            {
                temp << user->getPassword() << "\n";
            }
            lineNum++;
        }
        else if (lineNum % 5 == 4)
        {
            user->setMail(chunk);
            if (!skipPerson)
            {
                temp << user->getMail() << "\n";
                tempUsers.push_back(user);
            }
            skipPerson = false;
            lineNum++;
        }
    }

    file.close();
    temp.close();

    std::remove("../txtFiles/user.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/user.txt");

    // Update users vector
    Database::users = tempUsers;
    userCount = tempUsers.size();

    cout << "\nUsers has been deleted successfully\n";

    return 0;
}

int Database::updateUserInformation(const int id, const string &newName, const string &newUsername, const string &newPassword, const string &newMail)

{
    if (id < 0 || id >= userID)
    {
        Color_Red();
        printf("Please enter a valid number!");
        Color_Reset();
        return 0;
    }

    Database::deleteUser(id);
    if (!flagForDeleteAndUpdate)
    {
        User *user = new User(id, newName, newUsername, newPassword, newMail);
    }
}

// Function about topic
void Database::showAllTopics()
{
    int choice = 0;
    int countCategory1 = 0;
    int countCategory2 = 0;
    int countCategory3 = 0;
    int countCategory4 = 0;

    cout << "\n1- TECHNOLOGY\n";
    cout << "2- ECONOMY\n";
    cout << "3- POLITICS\n";
    cout << "4- FSMVU\n";
    Color_White();
    cout << "\nPlease choose which category of topics you want to view : ";
    Color_Reset();
    cin >> choice;

    switch (choice)
    {
    case 1:
        Color_Green();
        cout << "\n--------------- TECHNOLOGY ---------------\n\n";
        Color_Reset();
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (topics[i].getCategory() == 0)
            {
                countCategory1++;
                cout << "ID of the topic : " << topics[i].getId() << '\n';
                cout << "Name of the topic : " << topics[i].getTopicName() << '\n';
                cout << "Number of option of the topic : " << topics[i].getOptionLength() << '\n';
                cout << "Category of the topic : " << Topic::categories_names[topics[i].getCategory()] << '\n';
                for (int j = 0; j < topics[i].getOptionLength(); j++)
                {
                    cout << j + 1 << ". Option of the topic : " << topics[i].getTopicOptions()[j] << '\n';
                }
                Color_Blue();
                cout << "-------------------------------\n";
                Color_Reset();
            }
        }
        if (countCategory1 == 0)
        {
            Color_Red();
            cout << "\nYou don't have a topic in this category\n";
            Color_Reset();
        }
        return;
    case 2:
        Color_Green();
        cout << "\n--------------- ECONOMY ---------------\n\n";
        Color_Reset();
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (topics[i].getCategory() == 1)
            {
                countCategory2++;
                cout << "ID of the topic : " << topics[i].getId() << '\n';
                cout << "Name of the topic : " << topics[i].getTopicName() << '\n';
                cout << "Number of option of the topic : " << topics[i].getOptionLength() << '\n';
                cout << "Category of the topic : " << Topic::categories_names[topics[i].getCategory()] << '\n';
                for (int j = 0; j < topics[i].getOptionLength(); j++)
                {
                    cout << j + 1 << ". Option of the topic : " << topics[i].getTopicOptions()[j] << '\n';
                }
                Color_Blue();
                cout << "-------------------------------\n";
                Color_Reset();
            }
        }
        if (countCategory2 == 0)
        {
            Color_Red();
            cout << "\nYou don't have a topic in this category\n";
            Color_Reset();
        }
        return;
    case 3:
        Color_Green();
        cout << "\n--------------- POLITICS ---------------\n\n";
        Color_Reset();
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (topics[i].getCategory() == 2)
            {
                countCategory3++;
                cout << "ID of the topic : " << topics[i].getId() << '\n';
                cout << "Name of the topic : " << topics[i].getTopicName() << '\n';
                cout << "Number of option of the topic : " << topics[i].getOptionLength() << '\n';
                cout << "Category of the topic : " << Topic::categories_names[topics[i].getCategory()] << '\n';
                for (int j = 0; j < topics[i].getOptionLength(); j++)
                {
                    cout << j + 1 << ". Option of the topic : " << topics[i].getTopicOptions()[j] << '\n';
                }
                Color_Blue();
                cout << "-------------------------------\n";
                Color_Reset();
            }
        }
        if (countCategory3 == 0)
        {
            Color_Red();
            cout << "\nYou don't have a topic in this category\n";
            Color_Reset();
        }
        return;

    case 4:
        Color_Green();
        cout << "\n--------------- FSMVU ---------------\n\n";
        Color_Reset();
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (topics[i].getCategory() == 3)
            {
                countCategory4++;
                cout << "ID of the topic : " << topics[i].getId() << '\n';
                cout << "Name of the topic : " << topics[i].getTopicName() << '\n';
                cout << "Number of option of the topic : " << topics[i].getOptionLength() << '\n';
                cout << "Category of the topic : " << Topic::categories_names[topics[i].getCategory()] << '\n';
                for (int j = 0; j < topics[i].getOptionLength(); j++)
                {
                    std::cout << j + 1 << ". Option of the topic : " << topics[i].getTopicOptions()[j] << '\n';
                }
                Color_Blue();
                cout << "-------------------------------\n";
                Color_Reset();
            }
        }
        if (countCategory4 == 0)
        {
            Color_Red();
            cout << "\nYou don't have a topic in this category\n";
            Color_Reset();
        }
        return;
    default:
        Color_Red();
        cout << "Invalid option. Please select [1-4]\n";
        Color_Reset();
        while (cin.get() != '\n')
            ;
        break;
    }
}

void Database::deleteTopic(int topicId)
{
    // Find the index of the topic in the vector
    auto iterator = find_if(topics.begin(), topics.end(), [topicId](const Topic &topic)
                            { return topic.getId() == topicId; });

    if (iterator != topics.end())
    {
        // Erase the topic from the vector
        topics.erase(iterator);

        // Remove votes related to the deleted topic
        votes.erase(remove_if(votes.begin(), votes.end(), [topicId](const Vote &vote)
                              { return vote.getTopic().getId() == topicId; }),
                    votes.end());
        Color_Green();
        cout << "Topic has been deleted successfully.\n";
        Color_Reset();
    }
    else
    {
        Color_Red();
        cout << "Topic with ID " << topicId << " not found.\n";
        Color_Reset();
    }
}

void Database::updateTopicInformation(int updatedTopicId, const string &topicName, const vector<string> &topicOptions, Topic::Categories category, bool isOpen)
{
    // Find the index of the topic in the vector
    auto it = find_if(topics.begin(), topics.end(), [updatedTopicId](const Topic &topic)
                      { return topic.getId() == updatedTopicId; });

    if (it != topics.end())
    {
        deleteTopic(updatedTopicId);
        // Create a new Topic object with updated information
        Topic updatedTopic(topicName, topicOptions, category, isOpen);

        Color_Green();
        cout << "Topic has been updated successfully.\n";
        Color_Reset();
    }
    else
    {
        Color_Red();
        cout << "Topic not found.\n";
        Color_Reset();
    }
}

void Database::changeOpenStatus(int topicID)
{
    auto it = find_if(Database::topics.begin(), Database::topics.end(), [topicID](const Topic &topic)
                      { return topic.getId() == topicID; });

    if (it != Database::topics.end())
    {
        it->setIsOpen(!(it->getIsOpen()));
        Color_Green();
        cout << "Topic openStatus changed successfully.\n";
        Color_Reset();
    }
    else
    {
        Color_Red();
        cout << "Topic not found.\n";
        Color_Reset();
    }
}

// Function about vote
void Database::voteOperation(Person *account)
{
    int categoryOption = 0;
    int topicId = 0;
    int countCategory1 = 0;
    int countCategory2 = 0;
    int countCategory3 = 0;
    int countCategory4 = 0;
    int optionIndex = 0;
    bool flag = false;

    cout << "\n1- TECHNOLOGY\n";
    cout << "2- ECONOMY\n";
    cout << "3- POLITICS\n";
    cout << "4- FSMVU\n";
    Color_White();
    cout << "\nPlease choose which category of topics you want to vote : ";
    Color_Reset();
    cin >> categoryOption;

    switch (categoryOption)
    {
    case 1:
        Color_Green();
        cout << "\n--------------- TECHNOLOGY ---------------\n\n";
        Color_Reset();
        flag = false;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getCategory() == Topic::Categories::TECHNOLOGY && Database::topics[i].getIsOpen() == 1)
            {
                countCategory1++;
                cout << "Name of the topic : " << Database::topics[i].getTopicName() << " / ID of the topic : " << Database::topics[i].getId() << "\n";
                Color_Blue();
                cout << "------------------------------------------------------\n";
                Color_Reset();
            }
        }
        if (countCategory1 == 0)
        {
            Color_Red();
            cout << "\nYou don't have a topic in this category\n";
            Color_Reset();
            break;
        }
        Color_White();
        cout << "\nPlease enter the ID of the topic you want to vote on : ";
        Color_Reset();
        cin >> topicId;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getId() == topicId && Database::topics[i].getCategory() == Topic::Categories::TECHNOLOGY)
            {
                flag = true;
                for (int j = 0; j < Database::topics[i].getOptionLength(); j++)
                {
                    cout << j + 1 << ". Option of the topic : " << Database::topics[i].getTopicOptions()[j] << "\n";
                }
            }
        }
        if (!flag)
        {
            Color_Red();
            cout << "\nPlease enter valid ID!\n";
            Color_Reset();
            break;
        }
        Color_White();
        cout << "\nPlease enter which option you want to vote for : ";
        Color_Reset();
        cin >> optionIndex;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getId() == topicId && Database::topics[i].getCategory() == Topic::Categories::TECHNOLOGY)
            {
                createVote(Database::voteID, *account, Database::topics[i], optionIndex - 1);
                break;
            }
        }
        break;
    case 2:
        Color_Green();
        cout << "\n--------------- ECONOMY ---------------\n\n";
        Color_Reset();
        flag = false;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getCategory() == Topic::Categories::ECONOMY && Database::topics[i].getIsOpen() == 1)
            {
                countCategory2++;
                cout << "Name of the topic : " << Database::topics[i].getTopicName() << " / ID of the topic : " << Database::topics[i].getId() << "\n";
                Color_Blue();
                cout << "------------------------------------------------------\n";
                Color_Reset();
            }
        }
        if (countCategory2 == 0)
        {
            Color_Red();
            cout << "\nYou don't have a topic in this category\n";
            Color_Reset();
            break;
        }
        Color_White();
        cout << "\nPlease enter the ID of the topic you want to vote on : ";
        Color_Reset();
        cin >> topicId;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getId() == topicId && Database::topics[i].getCategory() == Topic::Categories::ECONOMY)
            {
                flag = true;
                for (int j = 0; j < Database::topics[i].getOptionLength(); j++)
                {
                    cout << j + 1 << ". Option of the topic : " << Database::topics[i].getTopicOptions()[j] << "\n";
                }
            }
        }
        if (!flag)
        {
            Color_Red();
            cout << "\nPlease enter valid ID!\n";
            Color_Reset();
            break;
        }
        Color_White();
        cout << "\nPlease enter which option you want to vote for : ";
        Color_Reset();
        cin >> optionIndex;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getId() == topicId && Database::topics[i].getCategory() == Topic::Categories::ECONOMY)
            {
                createVote(Database::voteID, *account, Database::topics[i], optionIndex - 1);
                break;
            }
        }
        break;

    case 3:
        Color_Green();
        cout << "\n--------------- POLITICS ---------------\n\n";
        Color_Reset();
        flag = false;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getCategory() == Topic::Categories::POLITICS && Database::topics[i].getIsOpen() == 1)
            {
                countCategory3++;
                cout << "Name of the topic : " << Database::topics[i].getTopicName() << " / ID of the topic : " << Database::topics[i].getId() << "\n";
                Color_Blue();
                cout << "------------------------------------------------------\n";
                Color_Reset();
            }
        }
        if (countCategory3 == 0)
        {
            Color_Red();
            cout << "\nYou don't have a topic in this category\n";
            Color_Reset();
            break;
        }
        Color_White();
        cout << "\nPlease enter the ID of the topic you want to vote on : ";
        Color_Reset();
        cin >> topicId;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getId() == topicId && Database::topics[i].getCategory() == Topic::Categories::POLITICS)
            {
                flag = true;
                for (int j = 0; j < Database::topics[i].getOptionLength(); j++)
                {
                    cout << j + 1 << ". Option of the topic : " << Database::topics[i].getTopicOptions()[j] << "\n";
                }
            }
        }
        if (!flag)
        {
            Color_Red();
            cout << "\nPlease enter valid ID!\n";
            Color_Reset();
            break;
        }
        Color_White();
        cout << "\nPlease enter which option you want to vote for : ";
        Color_Reset();
        cin >> optionIndex;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getId() == topicId && Database::topics[i].getCategory() == Topic::Categories::POLITICS)
            {
                createVote(Database::voteID, *account, Database::topics[i], optionIndex - 1);
                break;
            }
        }
        break;

    case 4:
        Color_Green();
        cout << "\n--------------- FSMVU ---------------\n\n";
        Color_Reset();
        flag = false;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getCategory() == Topic::Categories::FSMVU && Database::topics[i].getIsOpen() == 1)
            {
                countCategory4++;
                cout << "Name of the topic : " << Database::topics[i].getTopicName() << " / ID of the topic : " << Database::topics[i].getId() << "\n";
                Color_Blue();
                cout << "------------------------------------------------------\n";
                Color_Reset();
            }
        }
        if (countCategory4 == 0)
        {
            Color_Red();
            cout << "\nYou don't have a topic in this category\n";
            Color_Reset();
            break;
        }
        Color_White();
        cout << "\nPlease enter the ID of the topic you want to vote on : ";
        Color_Reset();
        cin >> topicId;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getId() == topicId && Database::topics[i].getCategory() == Topic::Categories::FSMVU)
            {
                flag = true;
                for (int j = 0; j < Database::topics[i].getOptionLength(); j++)
                {
                    cout << j + 1 << ". Option of the topic : " << Database::topics[i].getTopicOptions()[j] << "\n";
                }
            }
        }
        if (!flag)
        {
            Color_Red();
            cout << "\nPlease enter valid ID!\n";
            Color_Reset();
            break;
        }
        Color_White();
        cout << "\nPlease enter which option you want to vote for : ";
        Color_Reset();
        cin >> optionIndex;
        for (int i = 0; i < Database::topics.size(); i++)
        {
            if (Database::topics[i].getId() == topicId && Database::topics[i].getCategory() == Topic::Categories::FSMVU)
            {
                createVote(Database::voteID, *account, Database::topics[i], optionIndex - 1);
                break;
            }
        }
        break;

    default:
        Color_Red();
        cout << "\nInvalid option. Please select [1-4]\n";
        Color_Reset();
        break;
    }
}

void Database::deleteVote(int voteID)
{
    auto it = remove_if(votes.begin(), votes.end(), [voteID](const Vote &vote)
                        { return vote.getId() == voteID; });

    if (it != votes.end())
    {
        votes.erase(it, votes.end());
        Color_Green();
        cout << "Vote deleted successfully.\n";
        Color_Reset();
    }
    else
    {
        Color_Green();
        cout << "Vote not found.\n";
        Color_Reset();
    }
}

void Database::calculateVoteRate(int Id)
{
    int numberOfVote = 0;
    int voteCountForTopic = 0;

    for (int i = 0; i < Database::topics.size(); i++)
    {
        if (Database::topics[i].getId() == Id)
        {
            voteCountForTopic = Topic::findVoteCountForTopic(&(Database::topics[i]));

            for (int j = 0; j < Database::topics[i].getOptionLength(); j++)
            {
                numberOfVote = Database::topics[i].findVoteCountForTopicOption(&Database::topics[i])[j];

                if (voteCountForTopic != 0)
                {
                    cout << (j + 1) << ") " << Database::topics[i].getTopicOptions()[j] << " --> Vote Count/Rate : " << numberOfVote
                         << " (" << static_cast<float>(numberOfVote) / voteCountForTopic * 100 << "%)" << endl;
                }
                else
                {
                    cout << (j + 1) << ") " << Database::topics[i].getTopicOptions()[j] << " --> Vote Count/Rate : " << numberOfVote
                         << " (0.00%)" << endl;
                }
            }
        }
    }
}

void Database::setAllIdNumbers()
{
    // For user
    int maxForUser = Database::users[0]->getId();
    for (int i = 0; i < Database::users.size(); i++)
    {
        if (maxForUser < Database::users[i]->getId())
        {
            maxForUser = Database::users[i]->getId();
        }
    }
    Database::userID = maxForUser + 1;
}

// I have to use double pointer for my project. Aftr this part is very very unnecessary
vector<string> Database::categoryNames = {Topic::categories_names[Topic::TECHNOLOGY],
                                          Topic::categories_names[Topic::ECONOMY], Topic::categories_names[Topic::POLITICS],
                                          Topic::categories_names[Topic::FSMVU]};
vector<vector<string>> Database::topicsForCategoryNames(Database::categoryNames.size());
string **Database::categoryWithTopicName = new string *[Database::categoryNames.size()];
void Database::initializeCategoryWithTopicName()
{
    for (int i = 0; i < Database::categoryNames.size(); i++)
    {
        Database::categoryWithTopicName[i] = new string[Database::topics.size()];
    }
}

void Database::printTopicsWithCategories()
{
    for (int i = 0; i < Database::topics.size(); i++)
    {
        Topic::Categories topicCategory = Database::topics[i].getCategory();

        if (topicCategory == Topic::TECHNOLOGY)
        {
            categoryWithTopicName[Topic::TECHNOLOGY][i] = Database::topics[i].getTopicName();
        }
        else if (topicCategory == Topic::ECONOMY)
        {
            categoryWithTopicName[Topic::ECONOMY][i] = Database::topics[i].getTopicName();
        }
        else if (topicCategory == Topic::POLITICS)
        {
            categoryWithTopicName[Topic::POLITICS][i] = Database::topics[i].getTopicName();
        }
        else if (topicCategory == Topic::FSMVU)
        {
            categoryWithTopicName[Topic::FSMVU][i] = Database::topics[i].getTopicName();
        }
    }

    // Test: Print Categor Names
    for (int i = 0; i < categoryNames.size(); i++)
    {
        Color_Green();
        cout << "\n--------------- " << categoryNames[i] << "---------------\n"
             << endl;
        Color_Reset();
        for (size_t j = 0; j < Database::topics.size(); ++j)
        {
            if (!categoryWithTopicName[i][j].empty())
            {
                Color_White();
                cout << "  Topic Name : " << categoryWithTopicName[i][j] << endl;
                Color_Reset();
            }
        }
    }
}
