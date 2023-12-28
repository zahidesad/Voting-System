#include "../header/topic.h"
#include "../header/database.h"
#include <iostream>

using namespace std;

Topic::Topic(const string &topicName, const vector<string> &topicOptions, Categories category, bool isOpen)
    : id(Database::topicID), topicName(topicName), topicOptions(topicOptions), category(category), isOpen(isOpen)
{
    ++(*this);
    Database::topics.push_back(*this);
}
Topic::Topic() {}

Topic &Topic::operator++()
{
    Database::topicID++;
    return *this;
}

unordered_map<Topic::Categories, string> Topic::categories_names = {
    {Topic::TECHNOLOGY, "TECHNOLOGY"},
    {Topic::ECONOMY, "ECONOMY"},
    {Topic::POLITICS, "POLITICS"},
    {Topic::FSMVU, "FSMVU"}};

int Topic::getOptionLength() const
{
    int totalOptions = 0;
    for (const auto &topicOption : topicOptions)
    {
        totalOptions++;
    }
    return totalOptions;
}

// Getter functions
int Topic::getId() const
{
    return id;
}

string Topic::getTopicName() const
{
    return topicName;
}

const vector<string> &Topic::getTopicOptions() const
{
    return topicOptions;
}

bool Topic::getIsOpen() const
{
    return isOpen;
}

Topic::Categories Topic::getCategory() const
{
    return category;
}

// Setter functions
void Topic::setId(int newId)
{
    id = newId;
}

void Topic::setTopicName(const string &newTopicName)
{
    topicName = newTopicName;
}

void Topic::setTopicOptions(const vector<string> &newTopicOptions)
{
    topicOptions = newTopicOptions;
}

void Topic::setIsOpen(bool newIsOpen)
{
    isOpen = newIsOpen;
}

void Topic::setCategory(Categories newCategory)
{
    category = newCategory;
}

int Topic::findVoteCountForTopic(const Topic *topic)
{
    int total = 0;

    for (const auto &vote : Database::votes)
    {
        if (vote.getTopic().getId() == topic->getId())
        {
            total++;
        }
    }
    return total;
}

int *Topic::findVoteCountForTopicOption(const Topic *topic)
{
    int *total = (int *)malloc(topic->getOptionLength() * sizeof(int));

    for (int i = 0; i < topic->getOptionLength(); i++)
    {
        total[i] = 0;
    }

    for (int i = 0; i < Database::votes.size(); i++)
    {
        if (Database::votes[i].getTopic().getId() == (topic->getId()))
        {
            total[Database::votes[i].getTopicOptionIndex()]++;
        }
    }

    return total;
}
