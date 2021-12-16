#include "fileManager.h"

FileManager::FileManager()
{
    return;
}

bool FileManager::saveHighScore(int level, float score)
{
    if (highScoreSaved)
    {
        return false;
    }
    highScoreSaved = true;
    unordered_map<int, float> scores = getHighScores();
    ofstream MyFile("save.txt");
    if (MyFile.fail())
    {
        return false;
    }
    scores[level] = score;
    for (auto i : scores)
    {
        int levelName = i.first;
        float levelScore = i.second;
        MyFile << levelName << "|" << levelScore << endl;
    }
    MyFile.close();
    return true;
}

unordered_map<int, float> FileManager::getHighScores()
{
    string myText;
    ifstream MyReadFile("save.txt");
    unordered_map<int, float> levelScores;
    levelScores[1] = 0;
    levelScores[2] = 0;
    levelScores[3] = 0;
    levelScores[4] = 0;
    levelScores[5] = 0;
    if (!MyReadFile.fail())
    {
        while (getline(MyReadFile, myText))
        {
            int level;
            string score;
            level = stoi(string(1, (myText[0])));
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
    // prettyPrintLevel(loadedLevel);
    return true;
}

void FileManager::reset()
{
    highScoreSaved = false;
    loadedLevel = {{}};
}

void prettyPrintLevel(vector<vector<int>> level)
{
    for (size_t i = 0; i < level.size(); i++)
    {
        cout << "{";
        for (size_t j = 0; j < level[i].size(); j++)
        {
            if (j == level[i].size() - 1)
            {
                cout << level[i][j];
            }
            else
            {
                cout << level[i][j] << ",";
            }
        }
        if (i == level.size() - 1)
        {
            cout << "}";
        }
        else
        {
            cout << "},";
        }
    }
    cout << endl;
}