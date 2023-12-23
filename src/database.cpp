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