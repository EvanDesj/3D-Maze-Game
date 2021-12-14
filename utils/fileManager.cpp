#include "fileManager.h"

FileManager::FileManager()
{
    return;
}

bool FileManager::saveHighScore(string level, float score)
{
    if (highScoreSaved)
    {
        return false;
    }
    highScoreSaved = true;
    unordered_map<string, float> scores = getHighScores();
    ofstream MyFile("save.txt");
    if (MyFile.fail())
    {
        return false;
    }
    scores[level] = score;
    for (auto i : scores)
    {
        string levelName = i.first;
        float levelScore = i.second;
        if (levelName == "Custom")
        {
            levelName = "c";
        }
        MyFile << levelName << "|" << levelScore << endl;
    }
    MyFile.close();
    return true;
}

unordered_map<string, float> FileManager::getHighScores()
{
    string myText;
    ifstream MyReadFile("save.txt");
    unordered_map<string, float> levelScores;
    levelScores["1"] = 0;
    levelScores["2"] = 0;
    levelScores["3"] = 0;
    levelScores["4"] = 0;
    levelScores["Custom"] = 0;
    if (!MyReadFile.fail())
    {
        while (getline(MyReadFile, myText))
        {
            string level, score;
            level = myText[0];
            if (level == "c")
            {
                level = "Custom";
            }
            score = myText.substr(2);
            levelScores[level] = stof(score);
        }
        MyReadFile.close();
    }
    return levelScores;
}

bool FileManager::loadLevel()
{
    string myText;
    ifstream MyReadFile("board.txt");
    if (MyReadFile.fail())
    {
        return false;
    }
    while (getline(MyReadFile, myText))
    {
        loadedLevel.clear();
        vector<int> localVector = {};
        for (size_t i = 0; i < myText.length(); i++)
        {
            char character = myText[i];
            if (character != '{' && character != ',' && character != '}')
            {
                localVector.push_back(character - '0');
            }
            if (character == '}')
            {
                if (localVector.size())
                {
                    loadedLevel.push_back(localVector);
                }
                localVector = {};
            }
        }
    }
    // prettyPrintLevel();
    return true;
}

void FileManager::reset()
{
    highScoreSaved = false;
    loadedLevel = {{}};
}

void FileManager::prettyPrintLevel()
{
    for (size_t i = 0; i < loadedLevel.size(); i++)
    {
        cout << "{";
        for (size_t j = 0; j < loadedLevel[i].size(); j++)
        {
            if (j == loadedLevel[i].size() - 1)
            {
                cout << loadedLevel[i][j];
            }
            else
            {
                cout << loadedLevel[i][j] << ",";
            }
        }
        if (i == loadedLevel.size() - 1)
        {
            cout << "}";
        }
        else
        {
            cout << "},";
        }
    }
}