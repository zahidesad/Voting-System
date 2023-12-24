#include <iostream>
#include "../src/person.cpp"
#include "../src/admin.cpp"
#include "../src/user.cpp"
#include "../src/topic.cpp"
#include "../src/vote.cpp"
#include "../src/database.cpp"
#include "../Colors/color.cpp"

using namespace std;

int main()
{
    Database::readPerson();

    Admin admin(0, "Zahid", "zahid", "123", "zahid@gmail.com");
    User user(1, "Esad", "esad", "123", "zahid@gmail.com");

    vector<string> topicOptions = {"Option A", "Option B", "Option C"};
    Topic topic(1, "Sample Topic", topicOptions, Topic::TECHNOLOGY, true);

    int selectedOptionIndex = 1; // Örnek olarak Option B'ya oy veriyoruz
    Vote vote = createVote(1, user, topic, selectedOptionIndex);
    Vote vote1 = createVote(2, admin, topic, selectedOptionIndex);

    int testUserCount = 0;

    for (int i = 0; i < Database::users.size(); i++)
    {
        if (dynamic_cast<User *>(Database::users[i]) != nullptr)
        {
            testUserCount++;
        }
    }

    cout << "User Count: " << testUserCount << endl;
    cout << "Person Count:" << Database::users.size() << endl;
    cout << "Topic Count: " << Database::topics.size() << endl;
    cout << "Vote Count: " << Database::votes.size() << endl;

    cout << "Vote count for topic: " << topic.findVoteCountForTopic() << endl;

    for (size_t i = 0; i < topic.getOptionLength(); i++)
    {
        cout << "Vote count for Option " << i + 1 << ": " << findVoteCountForTopicOption(&topic)[i] << endl;
    }

    Person *loggedInUser = Database::login("esad", "123");

    if (loggedInUser != nullptr)
    {
        cout << "Login successful. User ID: " << loggedInUser->getId() << endl;
    }
    else
    {
        cout << "Login failed. Invalid username or password." << endl;
    }

    // Database::deletePerson(1);
    //Database::updatePersonInformation(0, "Test", "test", "123", "test@gmail.com");
    //cout << "User Count: " << testUserCount << endl;

    Database::showAllTopics();
    

    return 0;
}