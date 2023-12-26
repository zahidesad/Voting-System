#include "../header/vote.h"
#include "../header/database.h"
#include <iostream>

Vote::Vote(int id, Person voter, Topic topic, int topicOptionIndex)
    : id(Database::voteID), voter(voter), topic(topic), topicOptionIndex(topicOptionIndex) {}
Vote vote() {}

Vote createVote(int id, Person voter, Topic topic, int topicOptionIndex)
{
    for (const auto &existingVote : Database::votes)
    {
        if ((existingVote.getTopic().getId() == topic.getId()) && (existingVote.getVoter().getId() == voter.getId()))
        {   
            Color_Red();
            cout << "\nYou have already voted for this topic!\n";
            Color_Reset();
            return Vote(-1, Person(), Topic(), -1); // Return an empty vote with id -1
        }
    }

    if (topicOptionIndex >= 0 && topicOptionIndex <= topic.getOptionLength() - 1)
    {
        Vote vote(id, voter, topic, topicOptionIndex);
        Database::votes.push_back(vote);
        Database::voteID++;
        Color_Green();
        cout << "\nYou have voted successfully.\n";
        Color_Reset();
        return vote;
    }
    else
    {
        cout << "\nPlease write valid input!\n";
        return Vote(-1, Person(), Topic(), -1); // Return an empty vote with id -1
    }
}

// Getter fonksiyonları
int Vote::getId() const
{
    return id;
}

Person Vote::getVoter() const
{
    return voter;
}

Topic Vote::getTopic() const
{
    return topic;
}

int Vote::getTopicOptionIndex() const
{
    return topicOptionIndex;
}

// Setter fonksiyonları
void Vote::setId(int newId)
{
    id = newId;
}

void Vote::setVoter(const Person &newVoter)
{
    voter = newVoter;
}

void Vote::setTopic(const Topic &newTopic)
{
    topic = newTopic;
}

void Vote::setTopicOptionIndex(int newIndex)
{
    topicOptionIndex = newIndex;
}
