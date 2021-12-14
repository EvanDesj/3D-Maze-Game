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
    // getHighScores();
    ofstream MyFile("save.txt");
    if (MyFile.fail())
    {
        return false;
    }
    MyFile << level << "|" << score << endl;
    MyFile.close();
    return true;
}

bool FileManager::getHighScores(){
    string myText;
    ifstream MyReadFile("save.txt");
    if (MyReadFile.fail())
    {
        return false;
    }
    levelScores.clear();
    while (getline(MyReadFile, myText))
    {
        std::string s = myText;
        std::string delimiter = "|";
        std::string level = s.substr(0, s.find(delimiter));
        std::string score = s.substr(2, s.find(delimiter));
        cout<<level<<","<<score<<endl;
        levelScores.insert(std::make_pair(level, std::stof(score)));
    }
    MyReadFile.close();
    return true;
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