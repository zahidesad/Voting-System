#include "../header/database.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <new>

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
bool instanceof (const Derived *ptr)
{
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

Person *Database::login(const std::string &username, const std::string &password)
{
    for (std::size_t i = 0; i < Database::users.size(); i++)
    {
        if (Database::users[i]->getUsername() == username && Database::users[i]->getPassword() == password)
        {
            return Database::users[i];
        }
    }
    return nullptr; // Kullanıcı bulunamadı
}

void Database::insertPerson(const Person &person)
{
    ofstream file("../txtFiles/person.txt", ios_base::app);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    file << person.getId() << '\n'
         << person.getName() << '\n'
         << person.getUsername() << '\n'
         << person.getPassword() << '\n'
         << person.getMail() << '\n';

    userCount++;

    file.close();
    cout << "User has been written to the file successfully." << endl;
}

int Database::readPerson()
{
    ifstream file("../txtFiles/person.txt");
    if (!file.is_open())
    {
        cerr << "Error while opening the file!" << endl;
        return 1;
    }

    char chunk[128];
    int lineNum = 0;
    int personCount = 0;
    Person *person = nullptr;

    while (file.getline(chunk, sizeof(chunk)))
    {
        size_t newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 5 == 0)
        {
            person = new Person;
            person->setId(std::atoi(chunk));
            lineNum++;
        }
        else if (lineNum % 5 == 1)
        {
            person->setName(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 2)
        {
            person->setUsername(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 3)
        {
            person->setPassword(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 4)
        {
            person->setMail(chunk);
            lineNum++;
            users.push_back(person);
            personCount++;
        }
    }
    userCount = personCount;
    file.close();
    return 0;
}

int Database::deletePerson(int id)
{
    flagForDeleteAndUpdate = false;
    for (int i = 0; i < Database::users.size(); i++)
    {
        if (dynamic_cast<Admin *>(Database::users[i]) != nullptr) // If person is admin don't allow delete own account;
        {
            cout << "You are admin! You can't delete your own account" << endl;
            flagForDeleteAndUpdate = true;
            return 0;
        }
    }

    if (id < 0 || id >= userCount)
    {
        cout << "Please enter a valid number!";
        return 0;
    }

    ifstream file("../txtFiles/person.txt");
    ofstream temp("../txtFiles/temp.txt");

    if (!file.is_open() || !temp.is_open())
    {
        std::cout << "Error while opening the file!";
        return 1;
    }

    Person *person = nullptr;
    vector<Person *> tempUsers;
    char chunk[128];
    int lineNum = 0;
    bool skipPerson = false;

    while (file.getline(chunk, sizeof(chunk)))
    {
        if (lineNum % 5 == 0)
        {
            person = new Person;
            person->setId(std::atoi(chunk));
            if (person->getId() == id)
            {
                skipPerson = true;
            }
            else
            {
                temp << person->getId() << "\n";
            }
            lineNum++;
        }
        else if (lineNum % 5 == 1)
        {
            person->setName(chunk);
            if (!skipPerson)
            {
                temp << person->getName() << "\n";
            }
            lineNum++;
        }
        else if (lineNum % 5 == 2)
        {
            person->setUsername(chunk);
            if (!skipPerson)
            {
                temp << person->getUsername() << "\n";
            }
            lineNum++;
        }
        else if (lineNum % 5 == 3)
        {
            person->setPassword(chunk);
            if (!skipPerson)
            {
                temp << person->getPassword() << "\n";
            }
            lineNum++;
        }
        else if (lineNum % 5 == 4)
        {
            person->setMail(chunk);
            if (!skipPerson)
            {
                temp << person->getMail() << "\n";
                tempUsers.push_back(person);
            }
            skipPerson = false;
            lineNum++;
        }
    }

    file.close();
    temp.close();

    std::remove("../txtFiles/person.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/person.txt");

    // Update users vector
    Database::users = tempUsers;
    userCount = tempUsers.size();

    std::cout << "\nUsers has been deleted successfully\n";

    return 0;
}

int Database::updatePersonInformation(const int id, const string &newName, const string &newUsername, const string &newPassword, const string &newMail)

{
    Database::deletePerson(id);
    if (!flagForDeleteAndUpdate)
    {
        Person person(id, newName, newUsername, newPassword, newMail);
    }
}

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
