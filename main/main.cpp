#include <iostream>
#include <string>
#include <vector>
#include "../src/person.cpp"
#include "../src/admin.cpp"
#include "../src/user.cpp"
#include "../src/topic.cpp"
#include "../src/vote.cpp"
#include "../src/database.cpp"
#include "../Colors/color.cpp"

using namespace std;

int Display();
void defaultInformation();
void deleteAllData();

int main()
{
    defaultInformation();
    Database::readAdmin();
    Database::readUser();
    Database::setAllIdNumbers();
    Display();

    return 0;
}

int Display()
{
    Person *account;
    int option;
    int isLoggedIn = 0;

    while (true)
    {
        if (isLoggedIn && (instanceof <Admin>(account)))
        {
            Color_Green();
            printf("\n--------- Welcome Admin ---------\n", account->getName());
            Color_Reset();

            int choice;
            string topicName = "";
            int optionLength = 0;
            std::vector<std::string> topicOptions;
            Topic::Categories category;

            string newTopicName;
            int newOptionLength;
            vector<string> newTopicOptions;
            bool flag;
            bool flagForUser = 0;
            Topic::Categories newCategory;
            int idVoteRate = 0;
            int idForOpenStatus = 0;
            int idForDeleteUser = 0;
            Admin *admin;
            int deleteChoice;

            Topic topic;

            cout << "\n1- Create Topic" << endl;
            cout << "2- Show All Topics" << endl;
            cout << "3- Update Topic" << endl;
            cout << "4- Delete Topic" << endl;
            cout << "5- View your vote rates" << endl;
            cout << "6- Open/close topics for voting" << endl;
            cout << "7- Delete User Account" << endl;
            cout << "8- Show Topics With Categories" << endl;
            cout << "9- Destroy The System (Not Recommended)" << endl;
            cout << "10- Logout" << endl;

            Color_White();
            cout << "\nSelect an option : ";
            Color_Reset();
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Please enter your topic name: ";
                cin >> topicName;

                cout << "Please enter your number of options: ";
                cin >> optionLength;

                for (int i = 0; i < optionLength; i++)
                {
                    string option;
                    cout << "Please enter your " << i + 1 << ". option: ";
                    cin >> option;
                    topicOptions.push_back(option);
                }

                cout << "1) TECHNOLOGY" << endl;
                cout << "2) ECONOMY" << endl;
                cout << "3) POLITICS" << endl;
                cout << "4) FSMVU" << endl;

                cout << "\nPlease choose a category for your topic: ";
                cin >> choice;
                category = static_cast<Topic::Categories>(choice - 1);

                topic = Topic(topicName, topicOptions, category, 1);

                cout << "\nTopic created successfully...\n";
                break;

            case 2:
                Database::showAllTopics();
                break;

            case 3:
                for (int i = 0; i < Database::topics.size(); i++)
                {
                    cout << endl
                         << (i + 1) << "- Name of the topic : " << Database::topics[i].getTopicName() << " / ID of Topic : " << Database::topics[i].getId();
                }
                Color_White();
                cout << "\nPlease write the ID of the topic you want to update :";
                cin >> option;
                Color_Reset();
                cout << "\nPlease enter your new topic name : ";
                cin >> newTopicName;
                cout << "Please enter your number of options: ";
                cin >> newOptionLength;

                for (int i = 0; i < newOptionLength; i++)
                {
                    string newOption;
                    cout << "Please enter your " << i + 1 << ". option: ";
                    cin >> newOption;
                    newTopicOptions.push_back(newOption);
                }

                cout << "1) TECHNOLOGY" << endl;
                cout << "2) ECONOMY" << endl;
                cout << "3) POLITICS" << endl;
                cout << "4) FSMVU" << endl;

                cout << "\nPlease choose a category for your topic: ";
                cin >> choice;
                newCategory = static_cast<Topic::Categories>(choice - 1);

                Database::updateTopicInformation(option, newTopicName, newTopicOptions, newCategory, 1);
                break;

            case 4:
                for (int i = 0; i < Database::topics.size(); i++)
                {
                    cout << endl
                         << (i + 1) << "- Name of the topic : " << Database::topics[i].getTopicName() << " / ID of Topic : " << Database::topics[i].getId();
                }
                Color_White();
                cout << "\nPlease write the ID of the topic you want to delete :";
                cin >> option;
                Color_White();
                Database::deleteTopic(option);
                break;

            case 5:
                for (int i = 0; i < Database::topics.size(); i++)
                {
                    cout << endl
                         << (i + 1) << "- Name of the topic : " << Database::topics[i].getTopicName()
                         << " / ID of Topic : " << Database::topics[i].getId() << endl;
                }
                Color_White();
                cout << "\nPlease enter the ID of the topic for which you want to view the vote rate : ";
                cin >> idVoteRate;
                Color_White();
                Database::calculateVoteRate(idVoteRate);
                break;

            case 6:
                for (int i = 0; i < Database::topics.size(); i++)
                {
                    string statusName = "Close";
                    if (Database::topics[i].getIsOpen() == 1)
                    {
                        statusName = "Open";
                    }

                    cout << endl
                         << (i + 1) << "- Name of the topic : " << Database::topics[i].getTopicName()
                         << " / ID of Topic : " << Database::topics[i].getId()
                         << " / Open Status of Topic : " << statusName;
                }

                Color_White();
                cout << "\nPlease enter the ID of the topic for which you want to change open status : ";
                cin >> idForOpenStatus;
                Color_White();
                Database::changeOpenStatus(idForOpenStatus);
                break;

            case 7:
                for (int i = 0; i < Database::users.size(); i++)
                {
                    if (instanceof <User>(Database::users[i]))
                    {
                        cout << endl
                             << i << "- Username : " << Database::users[i]->getName() << " / ID of User : " << Database::users[i]->getId();
                    }
                }

                Color_White();
                cout << "\nPlease enter the ID of the person  which you want to delete : ";
                cin >> idForDeleteUser;
                Color_Reset();

                Database::deleteUser(idForDeleteUser);
                break;

            case 8:
                Database::initializeCategoryWithTopicName();
                Database::printTopicsWithCategories();
                break;
            case 9:
                Color_Red();
                cout << "Do you really want to delete all data. This action cannot be undone." << endl;
                Color_Reset();
                cout << "1- Yes" << endl
                     << "2- No" << endl
                     << endl;

                Color_White();
                cout << "Your choice : ";
                Color_Reset();
                cin >> deleteChoice;
                admin = static_cast<Admin *>(account);
                if (deleteAllData(*admin) && deleteChoice == 1)
                {
                    // Delete all votes
                    Database::votes.clear();
                    // Delete all topics
                    Database::topics.clear();
                    // Delete all users
                    Database::users.clear();
                    std::ofstream file1("../txtFiles/user.txt", std::ofstream::out | std::ofstream::trunc);
                    // Delete admin
                    std::ofstream file2("../txtFiles/admin.txt", std::ofstream::out | std::ofstream::trunc);
                    file1.close();
                    file2.close();
                    Color_Red();
                    cout << "THE ENTIRE SYSTEM HAS BEEN DESTROYED";
                    Color_Reset();
                    isLoggedIn = 0;
                }
                break;
            case 10:
                isLoggedIn = 0;
                break;
            default:
                Color_Red();
                printf("\nInvalid option. Please select [1-8]\n");
                Color_Reset();
                while (getchar() != '\n')
                    ;
                break;
            }
        }
        else if (isLoggedIn && (instanceof <User>(account)))
        {
            int switchOption = 0;
            int categoryOption = 0;
            int topicID = 0;
            int countCategory1 = 0; // If there are no votes in this category, use them to determine
            int countCategory2 = 0; // If there are no votes in this category, use them to determine
            int countCategory3 = 0; // If there are no votes in this category, use them to determine
            int countCategory4 = 0; // If there are no votes in this category, use them to determine
            int optionIndex = 0;
            int idRateOfVotes = 0;
            bool flag = 0;
            string newName;
            string newUsername;
            string newPassword;
            string newMail;

            Color_Green();
            cout << "\n--------- Welcome " << account->getName() << " --------- " << endl;
            Color_Reset();

            cout << "\n1- Show user information" << endl;
            cout << "2- Update user information" << endl;
            cout << "3- Vote for a topic" << endl;
            cout << "4- View vote rates" << endl;
            cout << "5- Logout" << endl;

            Color_White();
            cout << "\nSelect an option : ";
            Color_Reset();
            cin >> switchOption;

            switch (switchOption)
            {
            case 1:
                cout << "\nName : " << account->getName() << endl;
                cout << "Username : " << account->getUsername() << endl;
                cout << "Password : " << account->getPassword() << endl;
                cout << "Mail : " << account->getMail() << endl;
                break;
            case 2:
                Color_White();
                cout << "\nPlease enter your new name : ";
                Color_Reset();
                cin >> newName;

                Color_White();
                cout << "Please enter your new username : ";
                Color_Reset();
                cin >> newUsername;

                Color_White();
                cout << "Please enter your new password : ";
                Color_Reset();
                cin >> newPassword;

                Color_White();
                cout << "Please enter your new mail : ";
                Color_Reset();
                cin >> newMail;

                account->setName(newName);
                account->setUsername(newUsername);
                account->setPassword(newPassword);
                account->setMail(newMail);
                break;

            case 3:
                Database::voteOperation(account);
                break;
            case 4:
                for (int i = 0; i < Database::topics.size(); i++)
                {
                    cout << endl
                         << (i + 1) << "- Name of the topic : " << Database::topics[i].getTopicName()
                         << " / ID of Topic : " << Database::topics[i].getId() << endl;
                }
                Color_White();
                cout << "\nPlease enter the ID of the topic for which you want to view the vote rate : ";
                cin >> idRateOfVotes;
                Color_White();
                Database::calculateVoteRate(idRateOfVotes);
                break;
            case 5:
                isLoggedIn = 0;
                break;
            }
        }
        else
        {
            Color_Green();
            cout << "\n--------- WELCOME TO VOTING SYSTEM ---------\n";
            Color_Reset();
            cout << "1- Login\n";
            cout << "2- Register\n";
            cout << "3- Exit\n";

            Color_White();
            cout << "\nSelect an option: ";
            Color_Reset();
            cin >> option;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

            string name;
            string username;
            string password;
            string mail;

            switch (option)
            {
            case 1:
                Color_White();
                cout << "\nEnter your username: ";
                Color_Reset();
                getline(std::cin, username);

                Color_White();
                cout << "Enter your password: ";
                Color_Reset();
                getline(std::cin, password);

                Color_Yellow();
                cout << "\nLogging in...\n\n";
                Color_Reset();
                account = Database::login(username, password);
                if (account != nullptr)
                {
                    isLoggedIn = true;
                    break;
                }
                else
                {
                    Color_Red();
                    cout << "User not found! Please try again.\n";
                    Color_Reset();
                    // continue;
                }
                break;

            case 2:
                Color_White();
                cout << "\nEnter your name: ";
                Color_Reset();
                getline(cin, name);

                Color_White();
                cout << "Enter your username: ";
                Color_Reset();
                getline(cin, username);

                Color_White();
                cout << "Enter your password: ";
                Color_Reset();
                getline(cin, password);

                Color_White();
                cout << "Enter your mail: ";
                Color_Reset();
                getline(cin, mail);

                account = new User(Database::userID++, name, username, password, mail);
                Color_Green();
                cout << "\nAccount created successfully!\n\n";
                Color_Reset();
                Database::userID++;
                isLoggedIn = true;
                break;

            case 3:
                Color_Magenta();
                cout << "\n------------ Goodbye! ------------\n";
                Color_Reset();
                return 0;

            default:
                Color_Red();
                cout << "Invalid option. Please select 1, 2, or 3.\n";
                Color_Reset();
            }
        }
    }
}

void defaultInformation()
{
    Admin *admin = new Admin(0, "Admin", "admin", "123", "admin@gmail.com");
    User *user1 = new User(1, "Emirhan", "emirhan", "123", "emirhan@gmail.com");
    User *user2 = new User(2, "Asim", "asim", "123", "asim@gmail.com");

    // About technology
    vector<string> topicOptions1 = {"Yes", "No"}; // Will Baykar Technology company grow this year?
    vector<string> topicOptions2 = {"Yes", "No"}; // Will Apple company grow this year?

    // About economy
    vector<string> topicOptions3 = {"Yes", "No"}; // Will the dollar lose value this year?
    vector<string> topicOptions4 = {"Yes", "No"}; // Will the euro lose value this year?

    // About politics
    vector<string> topicOptions5 = {"A political party", "B political party", "C political party", "D political party"}; // Who will win this year's elections?

    // About FSMVU
    vector<string> topicOptions6 = {"Yes", "No"}; // Will the rector of FSMVU change this year?

    Topic topic1("Will Baykar Technology company grow this year?", topicOptions1, Topic::TECHNOLOGY, true);
    Topic topic2("Will Apple company grow this year?", topicOptions2, Topic::TECHNOLOGY, 1);

    Topic topic3("Will the dollar lose value this year?", topicOptions3, Topic::ECONOMY, 1);
    Topic topic4("Will the euro lose value this year?", topicOptions4, Topic::ECONOMY, 1);

    Topic topic5("Who will win this year's elections?", topicOptions5, Topic::POLITICS, 1);

    Topic topic6("Will the rector of FSMVU change this year?", topicOptions6, Topic::FSMVU, 1);
}

bool deleteAllData(Admin &admin)
{
    if (!admin.deleteAllDataFlag)
    {
        admin.deleteAllDataFlag = true;
    }
    return admin.deleteAllDataFlag;
}
