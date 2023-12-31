#ifndef TOPIC_H
#define TOPIC_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Topic
{
public:
    enum Categories
    {
        TECHNOLOGY,
        ECONOMY,
        POLITICS,
        FSMVU // My university name
    };

    Topic(const string &topicName, const vector<string> &topicOptions, Categories category, bool isOpen);
    Topic();

    static unordered_map<Categories, string> categories_names;
    Topic &operator++();
    // Getter functions
    int getId() const;
    string getTopicName() const;
    const vector<string> &getTopicOptions() const;
    bool getIsOpen() const;
    Categories getCategory() const;
    int getOptionLength() const;

    // Setter functions
    void setId(int newId);
    void setTopicName(const string &newTopicName);
    void setTopicOptions(const vector<string> &newTopicOptions);
    void setIsOpen(bool newIsOpen);
    void setCategory(Categories newCategory);

    static int findVoteCountForTopic(const Topic *topic);
    static int *findVoteCountForTopicOption(const Topic *topic);

private:
    int id;
    string topicName;
    vector<string> topicOptions;
    bool isOpen;
    Categories category;
};

#endif
