#ifndef VOTE_H
#define VOTE_H

#include "../header/person.h"
#include "../header/topic.h"

class Vote
{
private:
    int id;
    Person voter;
    Topic topic;
    int topicOptionIndex;

public:
    Vote(int id, Person voter, Topic topic, int topicOptionIndex);
    Vote();

    //Getter functions
    int getId() const;
    Person getVoter() const;
    Topic getTopic() const;
    int getTopicOptionIndex() const;

    // Setter functions
    void setId(int newId);
    void setVoter(const Person &newVoter);
    void setTopic(const Topic &newTopic);
    void setTopicOptionIndex(int newIndex);
};

Vote createVote(int id, Person voter, Topic topic, int topicOptionIndex);

#endif
