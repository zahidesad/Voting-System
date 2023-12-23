#include <iostream>
#include "../src/person.cpp"
#include "../src/admin.cpp"
#include "../src/user.cpp"
#include "../src/topic.cpp"
#include "../src/vote.cpp"
#include "../src/database.cpp"

using namespace std;

int main()
{
    Admin admin(0, "Zahid", "zahid", "123", "zahid@gmail.com");
    User user(1, "Zahid", "zahid", "123", "zahid@gmail.com");

    vector<string> topicOptions = {"Option A", "Option B", "Option C"};
    Topic topic(1, "Sample Topic", topicOptions, Topic::TECHNOLOGY, true);

    int selectedOptionIndex = 1; // Örnek olarak Option B'ya oy veriyoruz
    Vote vote = createVote(1, user, topic, selectedOptionIndex);
    Vote vote1 = createVote(2, admin, topic, selectedOptionIndex);

    /*int testUserCount = 0;

    for (int i = 0; i < Database::users.size(); i++)
    {
        if (isUser(&Database::users[i]) == true)
        {
            testUserCount++;
        }
    }

    cout << "User Count: " << testUserCount << endl;*/
    int count = 0;

    for (int i = 0; i < Database::users.size(); i++)
    {
        count++;
    }
    
    cout << "Topic Count: " << Database::topicCount << endl;
    cout << "Vote Count: " << Database::voteCount << endl;

    cout << "Vote count for topic: " << topic.findVoteCountForTopic() << endl;

    for (size_t i = 0; i < topic.getOptionLength(); i++)
    {
        cout << "Vote count for Option " << i + 1 << ": " << findVoteCountForTopicOption(&topic)[i] << endl;
    }

    return 0;
}